#include <stdio.h>
#include <stdlib.h>

#include "CokeCanDelegateInit.h"

void CokeCanPrint(COKE_CAN_DELEGATE *delegate, const char *str)
{
	printf("%s\n", str);
}

void CokeCanInput(COKE_CAN_DELEGATE *delegate, char *buf, int size)
{
	fgets(buf, size, stdin);
}

void CokeCanDelegate_Init(COKE_CAN_DELEGATE *delegate)
{
	delegate->print = CokeCanPrint;
	delegate->input = CokeCanInput;
}
