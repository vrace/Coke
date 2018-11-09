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

void ShowComponent(ICE_CUBE_DELEGATE *fn, INI_FILE *ini, const SHOW_COKE_DATA *data, const char *component)
{
	const char *val;

	fn->print(fn, data->showAs);
	fn->print(fn, " ");
	fn->print(fn, component);
	fn->print(fn, ": ");

	val = fn->iniFileValue(fn, ini, data->section, component);
	if (val)
	{
		fn->println(fn, val);
	}
	else
	{
		fn->println(fn, "Not Present");
	}
}

void ShowSettings(ICE_CUBE_DELEGATE *fn, INI_FILE *ini, int i)
{
	const SHOW_COKE_DATA *data;

	data = &DATA[i];
	ShowComponent(fn, ini, data, "coke");
	ShowComponent(fn, ini, data, "tea");
}

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
		ShowSettings(fn, ini, i);

	fn->iniFileRelease(fn, ini);

	return 0;
}
