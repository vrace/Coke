#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#include "ShortcutMain.h"

int ValidateShortcut(const char *shortcut)
{
	int i;
	int len;
	int separator = 0;

	len = strlen(shortcut);
	for (i = 0; i < len; i++)
	{
		char ch = shortcut[i];
		
		if (isalpha(ch))
			continue;

		if (isdigit(ch))
			continue;

		if (ch == ':' && separator == 0)
		{
			separator = 1;
			continue;
		}

		return -1;
	}

	return separator == 1 ? 0 : -1;
}

int MatchName(const char *longName, const char *shortName)
{
	while (*longName && *shortName)
	{
		if (!isalpha(*longName) && !isdigit(*longName))
		{
			longName++;
			continue;
		}

		if (*longName != *shortName)
			return -1;

		longName++;
		shortName++;
	}

	if (!*longName && (!*shortName || *shortName == ':'))
		return 0;

	return -1;
}

int MatchIce(COKE_CAN *can, const char *shortcut)
{
	int i;
	int count;

	count = CokeCan_NumberOfIce(can);
	for (i = 0; i < count; i++)
	{
		if (MatchName(CokeCan_IceName(can, i), shortcut) == 0)
			return i;
	}

	return -1;
}

int MatchIceCube(COKE_CAN *can, int ice, const char *shortcut)
{
	int i;
	int count;

	for (; *shortcut; shortcut++)
	{
		if (*shortcut == ':')
		{
			shortcut++;
			break;
		}
	}

	count = CokeCan_NumberOfIceCubes(can, ice);
	for (i = 0; i < count; i++)
	{
		if (MatchName(CokeCan_IceCubeName(can, ice, i), shortcut) == 0)
			return i;
	}

	return -1;
}

int RunShortcut(COKE_CAN *can, const char *shortcut)
{
	int ice;
	int cube;

	if (ValidateShortcut(shortcut) != 0)
	{
		printf("Invalid function syntax - %s\n", shortcut);
		return -1;
	}

	ice = MatchIce(can, shortcut);
	if (ice >= 0)
	{
		cube = MatchIceCube(can, ice, shortcut);
		if (cube >= 0)
		{
			return CokeCan_RunIceCube(can, ice, cube);
		}
	}

	printf("Function was not found - %s\n", shortcut);
	return -1;
}
