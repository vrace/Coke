#ifndef ICE_H
#define ICE_H

#include <Windows.h>
#include "IceCubeDelegate.h"

#define ICE_CUBE_API __stdcall

typedef void(ICE_CUBE_API *ICE_CUBE_API_VERSION)(int *major, int *minor);
typedef const char*(ICE_CUBE_API *ICE_CUBE_API_ICE_NAME)(void);
typedef int(ICE_CUBE_API *ICE_CUBE_API_NUMBER_OF_ICE_CUBES)(void);
typedef const char*(ICE_CUBE_API *ICE_CUBE_API_NAME_OF_ICE_CUBE)(int index);
typedef int(ICE_CUBE_API *ICE_CUBE_API_RUN_ICE_CUBE)(int index, ICE_CUBE_DELEGATE *delegate);

typedef struct Ice
{
	HMODULE module;

	ICE_CUBE_API_VERSION version;
	ICE_CUBE_API_ICE_NAME iceName;
	ICE_CUBE_API_NUMBER_OF_ICE_CUBES numberOfIceCubes;
	ICE_CUBE_API_NAME_OF_ICE_CUBE nameOfIceCube;
	ICE_CUBE_API_RUN_ICE_CUBE runIceCube;
} ICE;

int Ice_Load(ICE *ice, LPCTSTR filename);
void Ice_Release(ICE *ice);

#endif
