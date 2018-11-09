#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "CokeCanDelegateInit.h"

void CokeCanPrint(COKE_CAN_DELEGATE *self, const char *str)
{
	printf("%s", str);
}

void CokeCanPrintln(COKE_CAN_DELEGATE *self, const char *str)
{
	printf("%s\n", str);
}

void CokeCanInput(COKE_CAN_DELEGATE *self, char *buf, int size)
{
	int len;

	fgets(buf, size, stdin);
	len = strlen(buf);
	if (len > 0 && buf[len - 1] == '\n')
		buf[--len] = '\0';
}

void CokeCanDelegate_Init(COKE_CAN_DELEGATE *fn)
{
	fn->print = CokeCanPrint;
	fn->println = CokeCanPrintln;
	fn->input = CokeCanInput;
}
