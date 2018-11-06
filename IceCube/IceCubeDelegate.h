/* AUTO SYNCHRONIZED, DO NOT EDIT */ 
 
#ifndef ICE_CUBE_DELEGATE_H
#define ICE_CUBE_DELEGATE_H

#define ICE_CUBE_VERSION_MAJOR 0
#define ICE_CUBE_VERSION_MINOR 1

#include "WebRequest.h"

#ifdef __cplusplus
extern "C" {
#endif

	struct IceCubeDelegate;

	typedef void(*PRINT_FUNC)(struct IceCubeDelegate *delegate, const char *str);
	typedef void(*INPUT_FUNC)(struct IceCubeDelegate *delegate, char *buf, int size);
	typedef WEB_RESPONSE*(*WEB_REQUEST_FUNC)(struct IceCubeDelegate *delegate, WEB_REQUEST *request);
	typedef void(*RELEASE_WEB_RESPONSE_FUNC)(struct IceCubeDelegate *delegate, WEB_RESPONSE *response);

	typedef struct IceCubeDelegate
	{
		PRINT_FUNC print;
		INPUT_FUNC input;
		WEB_REQUEST_FUNC webRequest;
		RELEASE_WEB_RESPONSE_FUNC releaseWebResponse;
	} ICE_CUBE_DELEGATE;

#ifdef __cplusplus
}
#endif

#endif
