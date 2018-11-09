#ifndef ICE_CUBE_DELEGATE_H
#define ICE_CUBE_DELEGATE_H

#define ICE_CUBE_VERSION_MAJOR 1
#define ICE_CUBE_VERSION_MINOR 0

#include "WebRequest.h"

#ifdef __cplusplus
extern "C" {
#endif

	typedef struct IceCubeDelegate ICE_CUBE_DELEGATE;
	typedef struct IniFile INI_FILE;

	typedef void(*PRINT_FUNC)(ICE_CUBE_DELEGATE *self, const char *str);
	typedef void(*PRINT_INT_FUNC)(ICE_CUBE_DELEGATE *self, long val);
	typedef void(*PRINT_NUMBER_FUNC)(ICE_CUBE_DELEGATE *self, double val);
	typedef void(*INPUT_FUNC)(ICE_CUBE_DELEGATE *self, char *buf, int size);

	typedef void(*WEB_REQUEST_HEADER_INIT_FUNC)(ICE_CUBE_DELEGATE *self, WEB_REQUEST_HEADER *header);
	typedef void(*WEB_REQUEST_INIT_FUNC)(ICE_CUBE_DELEGATE *self, WEB_REQUEST *request);
	typedef WEB_RESPONSE*(*WEB_REQUEST_FUNC)(ICE_CUBE_DELEGATE *self, WEB_REQUEST *request);
	typedef void(*RELEASE_WEB_RESPONSE_FUNC)(ICE_CUBE_DELEGATE *self, WEB_RESPONSE *response);

	typedef INI_FILE*(*INI_FILE_LOAD_FUNC)(ICE_CUBE_DELEGATE *self, const char *file);
	typedef void(*INI_FILE_RELEASE_FUNC)(ICE_CUBE_DELEGATE *self, INI_FILE *file);
	typedef const char*(*INI_FILE_VALUE_FUNC)(ICE_CUBE_DELEGATE *self, INI_FILE *file, const char *section, const char *key);

	typedef struct IceCubeDelegate
	{
		PRINT_FUNC print;
		PRINT_FUNC println;
		PRINT_INT_FUNC printInt;
		PRINT_NUMBER_FUNC printNumber;
		INPUT_FUNC input;

		WEB_REQUEST_HEADER_INIT_FUNC initWebRequestHeader;
		WEB_REQUEST_INIT_FUNC initWebRequest;
		WEB_REQUEST_FUNC webRequest;
		RELEASE_WEB_RESPONSE_FUNC releaseWebResponse;

		INI_FILE_LOAD_FUNC iniFileLoad;
		INI_FILE_RELEASE_FUNC iniFileRelease;
		INI_FILE_VALUE_FUNC iniFileValue;
	};

#ifdef __cplusplus
}
#endif

#endif
