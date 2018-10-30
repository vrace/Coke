#include "Ice.h"

typedef struct IceLoadElement
{
	FARPROC *func;
	const char *name;
} ICE_LOAD_ELEMENT;

int Ice_Load(ICE *ice, LPCTSTR filename)
{
	int i;
	HMODULE module;

	ICE_LOAD_ELEMENT loadElements[] =
	{
		{ (FARPROC*)&ice->version, "IceCube_Version" },
		{ (FARPROC*)&ice->iceName, "IceCube_IceName" },
		{ (FARPROC*)&ice->numberOfIceCubes, "IceCube_NumberOfIceCubes" },
		{ (FARPROC*)&ice->nameOfIceCube, "IceCube_NameOfIceCube" },
		{ (FARPROC*)&ice->runIceCube, "IceCube_RunIceCube" },
	};

	module = LoadLibrary(filename);
	if (module == INVALID_HANDLE_VALUE)
		return -1;

	ice->module = module;

	for (i = 0; i < sizeof(loadElements) / sizeof(ICE_LOAD_ELEMENT); i++)
	{
		ICE_LOAD_ELEMENT *it = &loadElements[i];
		*it->func = GetProcAddress(module, it->name);
		if (!*it->func)
			return i + 1;
	}

	return 0;
}

void Ice_Release(ICE *ice)
{
	FreeLibrary(ice->module);
}
