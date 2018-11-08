#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "WebRequestExample.h"

int WebRequestExample(ICE_CUBE_DELEGATE *fn)
{
	char msg[4096];
	WEB_REQUEST_HEADER header;
	WEB_REQUEST request;
	WEB_RESPONSE *response;

	memset(&header, 0, sizeof(header));
	header.name = "Accept";
	header.value = "application/json";

	memset(&request, 0, sizeof(request));
	request.method = "GET";
	request.url = "https://cn.bing.com";
	request.header = &header;
	request.body.size = 11;
	request.body.content = "Fuzzy Bunny";

	response = fn->webRequest(fn, &request);
	if (response)
	{
		WEB_RESPONSE_HEADER *header;

		sprintf(msg, "[STATUS CODE] %d", response->statusCode);
		fn->print(fn, msg);

		for (header = response->header; header; header = header->next)
		{
			sprintf(msg, "[HEADER] %s: %s", header->name, header->value);
			fn->print(fn, msg);
		}

		fn->releaseWebResponse(fn, response);
		return 0;
	}
	else
	{
		fn->print(fn, "Unable to perform web request.");
		return -1;
	}
}
