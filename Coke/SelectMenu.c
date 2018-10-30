#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "SelectMenu.h"

int SelectOption(int *result)
{
	char buf[100];
	char *ep;

	fgets(buf, 100, stdin);
	ep = &buf[strlen(buf) - 1];
	if (*ep == '\n')
		*ep = '\0';
	*result = (int)strtol(buf, &ep, 0);

	return *ep;
}

int SelectMenu(SELECT_MENU_PARAMS *params)
{
	int i;

	if (params->titleText)
		printf("%s\n\n", params->titleText);

	for (i = 0; i < params->numberOfEntries; i++)
		printf("%d - %s\n", i + 1, params->entryAtIndex(params, i));
	printf("0 - %s\n", params->exitText);
	printf("\n");
	printf("Select an option: ");

	while (1)
	{
		int res = SelectOption(&i);
		if (res == 0 && i >= 0 && i <= params->numberOfEntries)
			break;
		printf("Invalid option. Select again: ");
	}

	return i - 1;
}
