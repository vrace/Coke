#include "WebRequestByFileExample.h"

int WebRequestByFileExample(ICE_CUBE_DELEGATE *fn)
{
	WEB_REQUEST request;
	WEB_RESPONSE *response;

	fn->initWebRequest(fn, &request);
	request.method = "GET";
	request.url = "https://cn.bing.com";
	request.headersFile = "Example/RequestHeaders.txt";
	request.bodyFile = "Example/RequestBody.txt";

	response = fn->webRequest(fn, &request);
	if (response)
	{
		WEB_RESPONSE_HEADER *header;

		fn->print(fn, "[STATUS CODE] ");
		fn->printInt(fn, response->statusCode);
		fn->println(fn, "");

		for (header = response->header; header; header = header->next)
		{
			fn->print(fn, "[HEADER] ");
			fn->print(fn, header->name);
			fn->print(fn, ":");
			fn->print(fn, header->value);
			fn->println(fn, "");
		}

		fn->releaseWebResponse(fn, response);
		return 0;
	}
	else
	{
		fn->println(fn, "Unable to perform web request.");
		return -1;
	}
}
