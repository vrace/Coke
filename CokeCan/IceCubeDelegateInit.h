#ifndef ICE_CUBE_DELEGATE_INIT_H
#define ICE_CUBE_DELEGATE_INIT_H

#include "IceCubeDelegate.h"
#include "CokeCan.h"

typedef struct IceCubeDelegateImpl
{
	ICE_CUBE_DELEGATE base;
	COKE_CAN_DELEGATE *delegate;
} ICE_CUBE_DELEGATE_IMPL;

void IceCubeDelegate_Init(ICE_CUBE_DELEGATE_IMPL *impl, COKE_CAN_DELEGATE *delegate);

#endif
