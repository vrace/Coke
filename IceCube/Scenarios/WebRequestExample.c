#include "WebRequestExample.h"

int WebRequestExample(ICE_CUBE_DELEGATE *fn)
{
	WEB_REQUEST_HEADER header;
	WEB_REQUEST request;
	WEB_RESPONSE *response;

	fn->initWebRequestHeader(fn, &header);
	header.name = "Accept";
	header.value = "application/json";

	fn->initWebRequest(fn, &request);
	request.method = "GET";
	request.url = "https://cn.bing.com";
	request.header = &header;
	request.body.size = 11;
	request.body.content = "Fuzzy Bunny";

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
