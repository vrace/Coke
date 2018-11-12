#ifndef FORMAT_TEXT_H
#define FORMAT_TEXT_H

typedef struct FormatTextDelegate FORMAT_TEXT_DELEGATE;

typedef int(*FEED_CHAR_FUNC)(FORMAT_TEXT_DELEGATE *delegate);
typedef void(*PUT_CHAR_FUNC)(FORMAT_TEXT_DELEGATE *delegate, char ch);
typedef const char*(*VALUE_FOR_SYMBOL_FUNC)(FORMAT_TEXT_DELEGATE *delegate, const char *symbol);

struct FormatTextDelegate
{
	FEED_CHAR_FUNC feed;
	PUT_CHAR_FUNC put;
	VALUE_FOR_SYMBOL_FUNC valueForSymbol;
};

#endif
