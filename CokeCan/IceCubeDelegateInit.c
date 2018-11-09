#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "IceCubeDelegateInit.h"
#include "WebRequestImpl.h"
#include "IniFile.h"

#define NUMBER_BUF_MAX 100

void IceCubePrint(ICE_CUBE_DELEGATE *self, const char *str)
{
	ICE_CUBE_DELEGATE_IMPL *impl = (ICE_CUBE_DELEGATE_IMPL*)self;
	COKE_CAN_DELEGATE *delegate = impl->delegate;
	delegate->print(delegate, str);
}

void IceCubePrintln(ICE_CUBE_DELEGATE *self, const char *str)
{
	ICE_CUBE_DELEGATE_IMPL *impl = (ICE_CUBE_DELEGATE_IMPL*)self;
	COKE_CAN_DELEGATE *delegate = impl->delegate;
	delegate->println(delegate, str);
}

void IceCubePrintInt(ICE_CUBE_DELEGATE *self, long val)
{
	char buf[NUMBER_BUF_MAX];
	sprintf(buf, "%d", val);
	IceCubePrint(self, buf);
}

void IceCubePrintNumber(ICE_CUBE_DELEGATE *self, double val)
{
	char buf[NUMBER_BUF_MAX];
	sprintf(buf, "%g", val);
	IceCubePrint(self, buf);
}

void IceCubeInput(ICE_CUBE_DELEGATE *self, char *buf, int size)
{
	ICE_CUBE_DELEGATE_IMPL *impl = (ICE_CUBE_DELEGATE_IMPL*)self;
	COKE_CAN_DELEGATE *delegate = impl->delegate;
	delegate->input(delegate, buf, size);
}

void IceCubeInitWebRequestHeader(ICE_CUBE_DELEGATE *self, WEB_REQUEST_HEADER *header)
{
	memset(header, 0, sizeof(WEB_REQUEST_HEADER));
}

void IceCubeInitWebRequest(ICE_CUBE_DELEGATE *self, WEB_REQUEST *request)
{
	memset(request, 0, sizeof(WEB_REQUEST));
}

WEB_RESPONSE* IceCubeWebRequest(ICE_CUBE_DELEGATE *self, WEB_REQUEST *request)
{
	return PerformWebRequest(request);
}

void IceCubeReleaseWebResponse(ICE_CUBE_DELEGATE *self, WEB_RESPONSE *response)
{
	ReleaseWebResponse(response);
}

INI_FILE* LoadIniFile(ICE_CUBE_DELEGATE *self, const char *file)
{
	return IniFile_Load(file);
}

void ReleaseIniFile(ICE_CUBE_DELEGATE *self, INI_FILE *file)
{
	IniFile_Release(file);
}

const char* ReadIniFileValue(ICE_CUBE_DELEGATE *self, INI_FILE *file, const char *section, const char *key)
{
	return IniFile_Value(file, section, key);
}

void IceCubeDelegate_Init(ICE_CUBE_DELEGATE_IMPL *impl, COKE_CAN_DELEGATE *delegate)
{
	impl->delegate = delegate;

	impl->base.print = IceCubePrint;
	impl->base.println = IceCubePrintln;
	impl->base.printInt = IceCubePrintInt;
	impl->base.printNumber = IceCubePrintNumber;
	impl->base.input = IceCubeInput;

	impl->base.initWebRequestHeader = IceCubeInitWebRequestHeader;
	impl->base.initWebRequest = IceCubeInitWebRequest;
	impl->base.webRequest = IceCubeWebRequest;
	impl->base.releaseWebResponse = IceCubeReleaseWebResponse;

	impl->base.iniFileLoad = LoadIniFile;
	impl->base.iniFileRelease = ReleaseIniFile;
	impl->base.iniFileValue = ReadIniFileValue;
}
