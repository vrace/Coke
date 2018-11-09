#include <stdio.h>
#include <stdlib.h>

#include "IceCube.h"
#include "IceCubeDelegate.h"
#include "Scenarios/HelloWorldExample.h"
#include "Scenarios/IniFileExample.h"
#include "Scenarios/WebRequestExample.h"
#include "Scenarios/WebRequestByFileExample.h"

typedef int(*ICE_CUBE_FUNC)(ICE_CUBE_DELEGATE *fn);

typedef struct IceCubeScenario
{
	const char *name;
	ICE_CUBE_FUNC func;
} ICE_CUBE_SCENARIO;

static const ICE_CUBE_SCENARIO SCENARIOS[] = {
	{ "Hello World", HelloWorldExample },
	{ "INI File",  IniFileExample },
	{ "Web Request",  WebRequestExample },
	{ "Web Request By File", WebRequestByFileExample },
};

int ICE_CUBE_API IceCube_NumberOfIceCubes(void)
{
	return sizeof(SCENARIOS) / sizeof(ICE_CUBE_SCENARIO);
}

const char* ICE_CUBE_API IceCube_NameOfIceCube(int index)
{
	const char *name = NULL;

	if (index >= 0 && index < IceCube_NumberOfIceCubes())
		name = SCENARIOS[index].name;

	return name;
}

int ICE_CUBE_API IceCube_RunIceCube(int index, ICE_CUBE_DELEGATE *fn)
{
	int res = -1;

	if (index >= 0 && index < IceCube_NumberOfIceCubes())
		res = SCENARIOS[index].func(fn);

	return res;
}
