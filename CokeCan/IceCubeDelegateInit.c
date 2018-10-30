#include "IceCubeDelegateInit.h"

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

void IceCubeDelegate_Init(ICE_CUBE_DELEGATE_IMPL *impl, COKE_CAN_DELEGATE *delegate)
{
	impl->delegate = delegate;
	impl->base.print = IceCubePrint;
	impl->base.input = IceCubeInput;
}
