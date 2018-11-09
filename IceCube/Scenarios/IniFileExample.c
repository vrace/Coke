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
	{ "Autumn", "Autumn" },
	{ "Winter", "Winter" },
};

int IniFileExample(ICE_CUBE_DELEGATE *fn)
{
	struct IniFile *ini;
	int i;

	ini = fn->iniFileLoad(fn, "Example/settings.ini");
	if (!ini)
	{
		fn->print(fn, "Unable to load settings.");
		return -1;
	}

	for (i = 0; i < sizeof(DATA) / sizeof(SHOW_COKE_DATA); i++)
	{
		const char *val;

		fn->print(fn, DATA[i].showAs);
		fn->print(fn, " Coke: ");

		val = fn->iniFileValue(fn, ini, DATA[i].section, "coke");
		if (val)
		{
			fn->println(fn, val);
		}
		else
		{
			fn->println(fn, "Not Present");
		}
	}

	fn->iniFileRelease(fn, ini);

	return 0;
}
