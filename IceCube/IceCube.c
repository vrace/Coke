#include <stdio.h>
#include <stdlib.h>

#include "IceCube.h"
#include "IceCubeDelegate.h"

int ICE_CUBE_API IceCube_NumberOfIceCubes(void)
{
	return 1;
}

const char* ICE_CUBE_API IceCube_NameOfIceCube(int index)
{
	if (index != 0)
		return NULL;

	return "Example Ice Cube";
}

int ICE_CUBE_API IceCube_RunIceCube(int index, ICE_CUBE_DELEGATE *fn)
{
	char msg[4096];

	if (index != 0)
		return -1;

	fn->print(fn, "Run Example Ice Cube!");

	WEB_REQUEST_HEADER header;
	header.name = "Accept";
	header.value = "application/json";
	header.next = NULL;

	WEB_REQUEST request;
	request.method = "GET";
	request.url = "https://cn.bing.com";
	request.header = &header;
	request.body.size = 11;
	request.body.content = "Fuzzy Bunny";

	WEB_RESPONSE *response = fn->webRequest(fn, &request);
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
	}
	else
	{
		fn->print(fn, "Unable to perform web request.");
	}

	return 0;
}
