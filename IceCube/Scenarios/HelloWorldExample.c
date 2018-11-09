#include "HelloWorldExample.h"

#define BUF_SIZE_MAX 1000

int HelloWorldExample(ICE_CUBE_DELEGATE *fn)
{
	char buf[BUF_SIZE_MAX];

	fn->print(fn, "The answer to the Ultimate Question of Life, the Universe, and Everything: ");
	fn->printInt(fn, 42);
	fn->println(fn, "");

	fn->print(fn, "PI = ");
	fn->printNumber(fn, 3.14159);
	fn->println(fn, "");

	fn->println(fn, "Enter name:");
	fn->input(fn, buf, BUF_SIZE_MAX);
	fn->print(fn, "Hello ");
	fn->print(fn, buf);
	fn->println(fn, "!");
	
	return 0;
}
