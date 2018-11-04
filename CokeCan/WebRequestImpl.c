#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "WebRequestImpl.h"

static const char REQUEST_HEADERS_FILE[] = "request_headers.txt";
static const char REQUEST_BODY_FILE[] = "request_body.txt";
static const char RESPONSE_HEADERS_FILE[] = "response_headers.txt";
static const char RESPONSE_BODY_FILE[] = "response_body.txt";
static const char CURL_EXEC[] = "curl_exec.bat";

int WriteHeaders(WEB_REQUEST *request)
{
	FILE *fp;
	int count = 0;
	WEB_REQUEST_HEADER *header;

	if (!request->header)
		return 0;

	fp = fopen(REQUEST_HEADERS_FILE, "w");
	if (fp)
	{
		for (header = request->header; header; header = header->next)
		{
			count++;
			fprintf(fp, "%s: %s\n", header->name, header->value);
		}

		fclose(fp);
	}

	return count;
}

long WriteBody(WEB_REQUEST *request)
{
	FILE *fp;
	WEB_REQUEST_BODY *body = &request->body;

	if (body->size <= 0 || !body->content)
		return 0;

	fp = fopen(REQUEST_BODY_FILE, "wb");
	if (!fp)
		return 0;

	fwrite(body->content, 1, body->size, fp);
	fclose(fp);

	return body->size;
}

int PrepareRequest(WEB_REQUEST *request)
{
	FILE *fp;

	fp = fopen(CURL_EXEC, "w");
	if (!fp)
		return 0;

	fprintf(fp, "@echo off\n");
	fprintf(fp, "curl -s -k -X %s ", request->method);
	if (WriteHeaders(request) > 0)
		fprintf(fp, "-H @%s ", REQUEST_HEADERS_FILE);
	fprintf(fp, "-D %s ", RESPONSE_HEADERS_FILE);
	if (WriteBody(request) > 0)
		fprintf(fp, "--data-binary @%s ", REQUEST_BODY_FILE);
	fprintf(fp, "%s > %s\n", request->url, RESPONSE_BODY_FILE);

	fclose(fp);

	return 0;
}

int ExtractStatusCode(const char *line)
{
	if (strstr(line, "HTTP") != line)
		return 0;

	for (; *line && *line != ' '; line++);
	return atoi(line);
}

WEB_RESPONSE_HEADER* ExtractHeader(const char *line)
{
	char *delim;
	int len;

	delim = strchr(line, ':');
	if (!delim)
		return NULL;

	WEB_RESPONSE_HEADER *header = malloc(sizeof(WEB_RESPONSE_HEADER));

	len = delim - line;
	header->name = malloc(len + 1);
	strncpy(header->name, line, len);
	header->name[len] = '\0';

	for (delim++; *delim && isspace(*delim); delim++);
	len = strlen(delim);
	header->value = malloc(len + 1);
	strcpy(header->value, delim);
	if (len > 0 && header->value[len - 1] == '\n')
		header->value[len - 1] = '\0';

	header->next = NULL;

	return header;
}

void LoadResponseHeaders(WEB_RESPONSE *response)
{
	FILE *fp;
	char line[4096];
	WEB_RESPONSE_HEADER **next;

	response->statusCode = 0;
	response->header = NULL;

	fp = fopen(RESPONSE_HEADERS_FILE, "r");
	if (!fp)
		return;

	if (fgets(line, 4096, fp))
		response->statusCode = ExtractStatusCode(line);

	next = &response->header;
	for (; *next; next = &(*next)->next);

	while (fgets(line, 4096, fp))
	{
		WEB_RESPONSE_HEADER *header = ExtractHeader(line);
		if (header)
		{
			*next = header;
			next = &header->next;
		}
	}

	fclose(fp);
}

void LoadResponseBody(WEB_RESPONSE_BODY *response)
{
	FILE *fp;

	response->size = 0;
	response->content = NULL;
	
	fp = fopen(RESPONSE_BODY_FILE, "rb");
	if (!fp)
		return;

	fseek(fp, 0, SEEK_END);
	response->size = ftell(fp);
	fseek(fp, 0, SEEK_SET);

	response->content = malloc(response->size);
	fread(response->content, 1, response->size, fp);
	fclose(fp);
}

WEB_RESPONSE* LoadResponse(void)
{
	WEB_RESPONSE *response = malloc(sizeof(WEB_RESPONSE));

	LoadResponseHeaders(response);
	LoadResponseBody(&response->body);

	unlink(REQUEST_HEADERS_FILE);
	unlink(REQUEST_BODY_FILE);
	unlink(RESPONSE_HEADERS_FILE);
	unlink(RESPONSE_BODY_FILE);

	return response;
}

WEB_RESPONSE* PerformWebRequest(WEB_REQUEST *request)
{
	int res;

	if (!request->method || !request->url)
		return NULL;

	res = PrepareRequest(request);
	if (res != 0)
		return NULL;

	if (system(CURL_EXEC) == 0)
		return LoadResponse();

	return NULL;
}

void ReleaseWebResponse(WEB_RESPONSE *response)
{
	WEB_RESPONSE_HEADER *header;
	for (header = response->header; header;)
	{
		WEB_RESPONSE_HEADER *next = header->next;
		free(header);
		header = next;
	}

	if (response->body.content)
		free(response->body.content);

	free(response);
}
