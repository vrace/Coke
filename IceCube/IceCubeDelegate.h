/* AUTO SYNCHRONIZED, DO NOT EDIT */ 
 
#ifndef ICE_CUBE_DELEGATE_H
#define ICE_CUBE_DELEGATE_H

#define ICE_CUBE_VERSION_MAJOR 0
#define ICE_CUBE_VERSION_MINOR 3

#include "WebRequest.h"

#ifdef __cplusplus
extern "C" {
#endif

	struct IceCubeDelegate;
	typedef struct IniFile INI_FILE;

	typedef void(*PRINT_FUNC)(struct IceCubeDelegate *delegate, const char *str);
	typedef void(*INPUT_FUNC)(struct IceCubeDelegate *delegate, char *buf, int size);
	typedef WEB_RESPONSE*(*WEB_REQUEST_FUNC)(struct IceCubeDelegate *delegate, WEB_REQUEST *request);
	typedef void(*RELEASE_WEB_RESPONSE_FUNC)(struct IceCubeDelegate *delegate, WEB_RESPONSE *response);
	typedef struct IniFile*(*INI_FILE_LOAD_FUNC)(struct IceCubeDelegate *delegate, const char *file);
	typedef void(*INI_FILE_RELEASE_FUNC)(struct IceCubeDelegate *delegate, struct IniFile *file);
	typedef const char*(*INI_FILE_VALUE_FUNC)(struct IceCubeDelegate *delegate, struct IniFile *file, const char *section, const char *key);

	typedef struct IceCubeDelegate
	{
		PRINT_FUNC print;
		INPUT_FUNC input;
		WEB_REQUEST_FUNC webRequest;
		RELEASE_WEB_RESPONSE_FUNC releaseWebResponse;
		INI_FILE_LOAD_FUNC iniFileLoad;
		INI_FILE_RELEASE_FUNC iniFileRelease;
		INI_FILE_VALUE_FUNC iniFileValue;
	} ICE_CUBE_DELEGATE;

#ifdef __cplusplus
}
#endif

#endif
