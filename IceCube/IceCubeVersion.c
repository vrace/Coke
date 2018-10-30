#include "IceCube.h"

#define REQUIRE_VERSION_MAJOR 0
#define REQUIRE_VERSION_MINOR 0

void ICE_CUBE_API IceCube_Version(int *major, int *minor)
{
	*major = REQUIRE_VERSION_MAJOR;
	*minor = REQUIRE_VERSION_MINOR;
}
