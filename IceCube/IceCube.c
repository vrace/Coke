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

int ICE_CUBE_API IceCube_RunIceCube(int index, ICE_CUBE_DELEGATE *delegate)
{
	if (index != 0)
		return -1;

	delegate->print(delegate, "Run Example Ice Cube!");
	return 0;
}
