#ifndef WEB_REQUEST_H
#define WEB_REQUEST_H

typedef struct WebRequestHeader
{
	const char *name;
	const char *value;
	struct WebRequestHeader *next;
} WEB_REQUEST_HEADER, WEB_RESPONSE_HEADER;

typedef struct WebRequestBody
{
	long size;
	const char *content;
} WEB_REQUEST_BODY, WEB_RESPONSE_BODY;

typedef struct WebRequest
{
	const char *method;
	const char *url;
	WEB_REQUEST_HEADER *header;
	WEB_REQUEST_BODY body;
	const char *headersFile;
	const char *bodyFile;
} WEB_REQUEST;

typedef struct WebResponse
{
	int statusCode;
	WEB_RESPONSE_HEADER *header;
	WEB_RESPONSE_BODY body;
} WEB_RESPONSE;

#endif
