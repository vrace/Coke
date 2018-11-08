#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "IniFileExample.h"

#define SHOW_LINE_MAX 1000

typedef struct ShowCokeData
{
	const char *showAs;
	const char *section;
} SHOW_COKE_DATA;

static const SHOW_COKE_DATA DATA[] =
{
	{ "Default", "" },
	{ "Spring", "Spring" },
	{ "Summer", "Summer" },
	{ "Fall", "Fall" },
	{ "Winter", "Winter" },
};

int IniFileExample(ICE_CUBE_DELEGATE *fn)
{
	struct IniFile *ini;
	char buf[SHOW_LINE_MAX];
	int i;

	ini = fn->iniFileLoad(fn, "ExampleResource/settings.ini");
	if (!ini)
	{
		fn->print(fn, "Unable to load settings.");
		return -1;
	}

	for (i = 0; i < sizeof(DATA) / sizeof(SHOW_COKE_DATA); i++)
	{
		int bufLen;
		int avail;
		const char *val;

		sprintf(buf, "%s Coke: ", DATA[i].showAs);
		bufLen = strlen(buf);
		avail = SHOW_LINE_MAX - bufLen - 1;
		if (avail < 0)
			avail = 0;
		
		val = fn->iniFileValue(fn, ini, DATA[i].section, "coke");
		if (val)
		{
			int valLen = strlen(val);
			if (valLen > avail)
				valLen = avail;

			memcpy(buf + bufLen, val, valLen);
			buf[bufLen + valLen] = '\0';
		}
		else
		{
			strcat(buf, "Not Present");
		}

		fn->print(fn, buf);
	}

	fn->iniFileRelease(fn, ini);
	return 0;
}
