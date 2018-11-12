#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "HelloWorldExample.h"
#include "../FormatText.h"

#define BUF_SIZE_MAX 1000

typedef struct FormatTextDemo
{
	FORMAT_TEXT_DELEGATE base;
	ICE_CUBE_DELEGATE *fn;
	const char *src;
	int size;
	int cursor;
} FORMAT_TEXT_DEMO;

int FeedFunc(FORMAT_TEXT_DEMO *self)
{
	if (self->cursor >= self->size)
		return EOF;

	return self->src[self->cursor++];
}

void PutFunc(FORMAT_TEXT_DEMO *self, char ch)
{
	char buf[2];

	buf[0] = ch;
	buf[1] = '\0';

	self->fn->print(self->fn, buf);
}

const char* ValueForSymbolFunc(FORMAT_TEXT_DEMO *self, const char *symbol)
{
	if (strcmp(symbol, "ANIMAL") == 0)
		return "fox";

	if (strcmp(symbol, "TARGET") == 0)
		return "dog";

	return NULL;
}

void FormatTextExample(ICE_CUBE_DELEGATE *fn)
{
	FORMAT_TEXT_DEMO demo;

	memset(&demo, 0, sizeof(demo));
	demo.base.feed = (FEED_CHAR_FUNC)FeedFunc;
	demo.base.put = (PUT_CHAR_FUNC)PutFunc;
	demo.base.valueForSymbol = (VALUE_FOR_SYMBOL_FUNC)ValueForSymbolFunc;
	demo.fn = fn;
	demo.src = "The quick brown %ANIMAL% jumps over the lazy %TARGET%\nThis function is 100%% working!\nNot closed symbol %NOT_CLOSED";
	demo.size = strlen(demo.src);
	demo.cursor = 0;

	fn->formatText(fn, (FORMAT_TEXT_DELEGATE*)&demo);
	fn->println(fn, "");
}

int HelloWorldExample(ICE_CUBE_DELEGATE *fn)
{
	char buf[BUF_SIZE_MAX];

	fn->print(fn, "The answer to the Ultimate Question of Life, the Universe, and Everything: ");
	fn->printInt(fn, 42);
	fn->println(fn, "");

	fn->print(fn, "PI = ");
	fn->printNumber(fn, 3.14159);
	fn->println(fn, "");

	FormatTextExample(fn);

	fn->println(fn, "Enter name:");
	fn->input(fn, buf, BUF_SIZE_MAX);
	fn->print(fn, "Hello ");
	fn->print(fn, buf);
	fn->println(fn, "!");
	
	return 0;
}
