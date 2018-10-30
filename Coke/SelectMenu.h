#ifndef SELECT_MENU_H
#define SELECT_MENU_H

struct SelectMenuParams;

typedef const char*(*SELECT_MENU_ENTRY_AT_INDEX)(struct SelectMenuParams *self, int index);

typedef struct SelectMenuParams
{
	int numberOfEntries;
	SELECT_MENU_ENTRY_AT_INDEX entryAtIndex;
	const char *titleText;
	const char *exitText;
} SELECT_MENU_PARAMS;

int SelectMenu(SELECT_MENU_PARAMS *params);

#endif
