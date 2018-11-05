#include "IceCube.h"
#include "IceCubeDelegate.h"

void ICE_CUBE_API IceCube_Version(int *major, int *minor)
{
	*major = ICE_CUBE_VERSION_MAJOR;
	*minor = ICE_CUBE_VERSION_MINOR;
}
