#include <stdio.h>
#include <stdlib.h>

#include "MenuMain.h"
#include "SelectMenu.h"

typedef struct IceMenuParams
{
	SELECT_MENU_PARAMS base;
	COKE_CAN *can;
} ICE_MENU_PARAMS;

typedef struct IceCubeMenuParams
{
	SELECT_MENU_PARAMS base;
	COKE_CAN *can;
	int iceIndex;
} ICE_CUBE_MENU_PARAMS;

const char* IceMenuEntryAtIndex(ICE_MENU_PARAMS *self, int index)
{
	return CokeCan_IceName(self->can, index);
}

int ShowIceMenu(COKE_CAN *can)
{
	ICE_MENU_PARAMS params;

	params.base.numberOfEntries = CokeCan_NumberOfIce(can);
	params.base.entryAtIndex = (SELECT_MENU_ENTRY_AT_INDEX)IceMenuEntryAtIndex;
	params.base.titleText = "Available Groups";
	params.base.exitText = "Exit";
	params.can = can;

	return SelectMenu((SELECT_MENU_PARAMS*)&params);
}

const char* IceCubeMenuEntryAtIndex(ICE_CUBE_MENU_PARAMS *self, int index)
{
	return CokeCan_IceCubeName(self->can, self->iceIndex, index);
}

int ShowIceCubeMenu(COKE_CAN *can, int iceIndex)
{
	ICE_CUBE_MENU_PARAMS params;

	params.base.numberOfEntries = CokeCan_NumberOfIceCubes(can, iceIndex);
	params.base.entryAtIndex = (SELECT_MENU_ENTRY_AT_INDEX)IceCubeMenuEntryAtIndex;
	params.base.titleText = "Available Functions";
	params.base.exitText = "Previous Menu";
	params.can = can;
	params.iceIndex = iceIndex;

	return SelectMenu((SELECT_MENU_PARAMS*)&params);
}

void Pause(void)
{
	char buf[1000];
	fgets(buf, 1000, stdin);
}

void ClearScreen(void)
{
	int i;

	for (i = 0; i < 100; i++)
		printf("\n");
}

void RunMenu(COKE_CAN *can)
{
	int ice;
	int iceCube;

	while (1)
	{
		ClearScreen();
		ice = ShowIceMenu(can);
		if (ice < 0)
			break;

		ClearScreen();
		iceCube = ShowIceCubeMenu(can, ice);
		if (iceCube < 0)
			continue;

		ClearScreen();
		printf("Run function %s...\n", CokeCan_IceCubeName(can, ice, iceCube));
		CokeCan_RunIceCube(can, ice, iceCube);

		printf("\n");
		printf("Run complete. Press ENTER to continue...\n");
		Pause();
	}
}
