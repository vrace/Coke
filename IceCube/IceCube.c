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

struct ShowCokeData
{
	const char *showAs;
	const char *section;
};

void ShowCokeSettings(ICE_CUBE_DELEGATE *fn)
{
	struct IniFile *ini;
	char buf[4096];
	int i;
	struct ShowCokeData data[] =
	{
		{ "Default", "" },
		{ "Spring", "Spring" },
		{ "Summer", "Summer" },
		{ "Fall", "Fall" },
		{ "Winter", "Winter" },
	};

	ini = fn->iniFileLoad(fn, "settings.ini");
	if (!ini)
	{
		fn->print(fn, "Unable to load settings.");
		return;
	}

	for (i = 0; i < sizeof(data) / sizeof(struct ShowCokeData); i++)
	{
		sprintf(buf, "%s Coke: %s", data[i].showAs, fn->iniFileValue(fn, ini, data[i].section, "coke"));
		fn->print(fn, buf);
	}

	fn->iniFileRelease(fn, ini);
}

void WebRequestDemo(ICE_CUBE_DELEGATE *fn)
{
	char msg[4096];
	WEB_REQUEST_HEADER header;
	WEB_REQUEST request;
	WEB_RESPONSE *response;

	header.name = "Accept";
	header.value = "application/json";
	header.next = NULL;

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
	}
	else
	{
		fn->print(fn, "Unable to perform web request.");
	}
}

int ICE_CUBE_API IceCube_RunIceCube(int index, ICE_CUBE_DELEGATE *fn)
{
	if (index != 0)
		return -1;

	fn->print(fn, "Run Example Ice Cube!");

	ShowCokeSettings(fn);
	WebRequestDemo(fn);

	return 0;
}
