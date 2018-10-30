#include <stdio.h>
#include <stdlib.h>

#include "../CokeCan/CokeCan.h"
#include "CokeCanDelegateInit.h"
#include "MenuMain.h"
#include "ShortcutMain.h"

int main(int argc, char *argv[])
{
	COKE_CAN_DELEGATE delegate;
	COKE_CAN *can;
	int res = 0;

	if (argc != 1 && argc != 2)
	{
		printf("Usage: Coke [shortcut]\n");
		return -1;
	}

	CokeCanDelegate_Init(&delegate);
	can = CokeCan_Init(&delegate);
	if (!can)
	{
		printf("Init coke can failed.\n");
		return 1;
	}

	CokeCan_LoadIceCubes(can);

	if (argc == 1)
	{
		RunMenu(can);
	}
	else
	{
		res = RunShortcut(can, argv[1]);
	}

	CokeCan_Free(can);

	return res;
}
