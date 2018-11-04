#include "IceCubeDelegateInit.h"
#include "WebRequestImpl.h"

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

void IceCubeDelegate_Init(ICE_CUBE_DELEGATE_IMPL *impl, COKE_CAN_DELEGATE *delegate)
{
	impl->delegate = delegate;

	impl->base.print = IceCubePrint;
	impl->base.input = IceCubeInput;
	impl->base.webRequest = IceCubeWebRequest;
	impl->base.releaseWebResponse = IceCubeReleaseWebResponse;
}
