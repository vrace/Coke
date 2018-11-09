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
	const char *header = NULL;
	const char *body = NULL;

	fp = fopen(CURL_EXEC, "w");
	if (!fp)
		return 0;

	header = request->headersFile;
	if (!header && WriteHeaders(request) > 0)
		header = REQUEST_HEADERS_FILE;

	body = request->bodyFile;
	if (!body && WriteBody(request) > 0)
		body = REQUEST_BODY_FILE;

	fprintf(fp, "@echo off\n");
	fprintf(fp, "curl -s -k -X %s ", request->method);
	if (header)
		fprintf(fp, "-H @%s ", header);
	fprintf(fp, "-D %s ", RESPONSE_HEADERS_FILE);
	if (body)
		fprintf(fp, "--data-binary @%s ", body);
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

WEB_RESPONSE_HEADER* ExtractHeader(char *line)
{
	char *delim;
	int len;

	delim = strchr(line, ':');
	if (!delim)
		return NULL;

	WEB_RESPONSE_HEADER *header = malloc(sizeof(WEB_RESPONSE_HEADER));

	*delim = '\0';
	header->name = _strdup(line);

	for (delim++; *delim && isspace(*delim); delim++);
	len = strlen(delim);
	if (delim > 0 && delim[len - 1] == '\n')
		delim[--len] = '\0';
	header->value = _strdup(delim);

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
	char *content;

	response->size = 0;
	response->content = NULL;
	
	fp = fopen(RESPONSE_BODY_FILE, "rb");
	if (!fp)
		return;

	fseek(fp, 0, SEEK_END);
	response->size = ftell(fp);
	fseek(fp, 0, SEEK_SET);

	content = malloc(response->size);
	fread(content, 1, response->size, fp);
	fclose(fp);
	response->content = content;
}

WEB_RESPONSE* LoadResponse(void)
{
	WEB_RESPONSE *response = malloc(sizeof(WEB_RESPONSE));

	LoadResponseHeaders(response);
	LoadResponseBody(&response->body);

	_unlink(REQUEST_HEADERS_FILE);
	_unlink(REQUEST_BODY_FILE);
	_unlink(RESPONSE_HEADERS_FILE);
	_unlink(RESPONSE_BODY_FILE);
	_unlink(CURL_EXEC);

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
		free((char*)response->body.content);

	free(response);
}
