#include "IceCubeDelegateInit.h"
#include "WebRequestImpl.h"
#include "IniFile.h"

void IceCubePrint(ICE_CUBE_DELEGATE *self, const char *str)
{
	ICE_CUBE_DELEGATE_IMPL *impl = (ICE_CUBE_DELEGATE_IMPL*)self;
	COKE_CAN_DELEGATE *delegate = impl->delegate;
	delegate->print(delegate, str);
}

void IceCubeInput(ICE_CUBE_DELEGATE *self, char *buf, int size)
{
	ICE_CUBE_DELEGATE_IMPL *impl = (ICE_CUBE_DELEGATE_IMPL*)self;
	COKE_CAN_DELEGATE *delegate = impl->delegate;
	delegate->input(delegate, buf, size);
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
	impl->base.input = IceCubeInput;
	impl->base.webRequest = IceCubeWebRequest;
	impl->base.releaseWebResponse = IceCubeReleaseWebResponse;
	impl->base.iniFileLoad = LoadIniFile;
	impl->base.iniFileRelease = ReleaseIniFile;
	impl->base.iniFileValue = ReadIniFileValue;
}
