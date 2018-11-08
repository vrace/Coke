#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "HelloWorldExample.h"

#define BUF_SIZE_MAX 1000

int HelloWorldExample(ICE_CUBE_DELEGATE *fn)
{
	int len;
	int avail;
	char buf[BUF_SIZE_MAX];

	strcpy(buf, "Hello ");
	len = strlen(buf);
	avail = BUF_SIZE_MAX - len - 1;

	fn->print(fn, "Enter name:");
	fn->input(fn, buf + len, avail);
	strcat(buf, "!");
	fn->print(fn, buf);
	
	return 0;
}
