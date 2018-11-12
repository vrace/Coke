#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "FormatTextImpl.h"

#define FORMAT_STATE_CHAR 0
#define FORMAT_STATE_SYMBOL 1

typedef struct FormatTextState
{
	int state;
	char *symbol;
	int used;
	int capacity;
} FORMAT_TEXT_STATE;

typedef void(*FORMAT_STATE_PROC)(FORMAT_TEXT_DELEGATE *delegate, FORMAT_TEXT_STATE *state, char ch);

void FormatStateProc_Char(FORMAT_TEXT_DELEGATE *delegate, FORMAT_TEXT_STATE *state, char ch)
{
	if (ch == '%')
	{
		state->state = FORMAT_STATE_SYMBOL;
	}
	else
	{
		delegate->put(delegate, ch);
	}
}

void FormatStateProc_Symbol(FORMAT_TEXT_DELEGATE *delegate, FORMAT_TEXT_STATE *state, char ch)
{
	if (ch != '%')
	{
		if (state->capacity == 0)
		{
			state->capacity = 100;
			state->symbol = malloc(state->capacity + 1);
		}

		if (state->used >= state->capacity)
		{
			state->capacity = state->capacity * 2 + state->capacity / 2;
			state->symbol = realloc(state->symbol, state->capacity + 1);
		}

		state->symbol[state->used++] = ch;
	}
	else
	{
		if (state->used == 0)
		{
			delegate->put(delegate, '%');
		}
		else
		{
			const char *value;

			state->symbol[state->used] = '\0';
			value = delegate->valueForSymbol(delegate, state->symbol);
			
			if (!value)
				value = "(null)";

			for (; *value; delegate->put(delegate, *value++));

			state->used = 0;
		}

		state->state = FORMAT_STATE_CHAR;
	}
}

static const FORMAT_STATE_PROC FORMAT_STATE_PROC_MAP[] =
{
	FormatStateProc_Char,
	FormatStateProc_Symbol,
};

void FormatText(FORMAT_TEXT_DELEGATE *delegate)
{
	FORMAT_TEXT_STATE state;
	int ch;

	memset(&state, 0, sizeof(state));
	while ((ch = delegate->feed(delegate)) != EOF)
		FORMAT_STATE_PROC_MAP[state.state](delegate, &state, ch);

	if (state.used > 0)
	{
		int i;

		delegate->put(delegate, '%');
		for (i = 0; i < state.used; i++)
			delegate->put(delegate, state.symbol[i]);
	}

	free(state.symbol);
}
