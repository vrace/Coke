#include <Windows.h>
#include <stdio.h>
#include <stdlib.h>
#include "CokeCan.h"
#include "Ice.h"
#include "IceCubeDelegateInit.h"

typedef struct IceChain
{
	ICE ice;
	struct IceChain *next;
} ICE_CHAIN;

struct CokeCan
{
	ICE_CHAIN *firstIce;
	ICE_CUBE_DELEGATE_IMPL iceCubeDelegate;
};

COKE_CAN* COKE_CAN_API CokeCan_Init(COKE_CAN_DELEGATE *delegate)
{
	COKE_CAN *cokeCan = malloc(sizeof(COKE_CAN));
	
	cokeCan->firstIce = NULL;
	IceCubeDelegate_Init(&cokeCan->iceCubeDelegate, delegate);

	return cokeCan;
}

void COKE_CAN_API CokeCan_Free(COKE_CAN *cokeCan)
{
	ICE_CHAIN *iceChain;
	
	for (iceChain = cokeCan->firstIce; iceChain;)
	{
		ICE_CHAIN *next = iceChain->next;
		Ice_Release(&iceChain->ice);
		free(iceChain);
		iceChain = next;
	}

	free(cokeCan);
}

int CokeCan_CheckIceVersion(ICE *ice)
{
	int major;
	int minor;

	ice->version(&major, &minor);

	if (major != COKE_CAN_VERSION_MAJOR)
		return 1;

	if (minor > COKE_CAN_VERSION_MINOR)
		return 2;

	return 0;
}

void COKE_CAN_API CokeCan_LoadIceCubes(COKE_CAN *cokeCan)
{
	WIN32_FIND_DATA wfd;
	HANDLE hf;

	hf = FindFirstFile(TEXT("*.ice"), &wfd);
	while (hf != INVALID_HANDLE_VALUE)
	{
		if (!(wfd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
		{
			ICE_CHAIN *chain = malloc(sizeof(ICE_CHAIN));
			chain->next = NULL;

			if (Ice_Load(&chain->ice, wfd.cFileName) == 0 && CokeCan_CheckIceVersion(&chain->ice) == 0)
			{
				ICE_CHAIN **dest;

				for (dest = &cokeCan->firstIce; *dest; dest = &(*dest)->next);
				*dest = chain;
			}
			else
			{
				free(chain);
			}
		}

		if (!FindNextFile(hf, &wfd))
		{
			FindClose(hf);
			hf = INVALID_HANDLE_VALUE;
		}
	}
}

int COKE_CAN_API CokeCan_NumberOfIce(COKE_CAN *cokeCan)
{
	int count = 0;
	ICE_CHAIN *chain;
	
	for (chain = cokeCan->firstIce; chain; chain = chain->next)
		count++;

	return count;
}

ICE_CHAIN* CokeCan_FindIce(COKE_CAN *cokeCan, int iceIndex)
{
	ICE_CHAIN *chain;

	if (iceIndex < 0)
		return NULL;

	for (chain = cokeCan->firstIce; chain && iceIndex > 0; iceIndex--)
		chain = chain->next;

	return chain;
}

const char* COKE_CAN_API CokeCan_IceName(COKE_CAN *cokeCan, int iceIndex)
{
	ICE_CHAIN *chain;
	chain = CokeCan_FindIce(cokeCan, iceIndex);
	return chain ? chain->ice.iceName() : NULL;
}

int COKE_CAN_API CokeCan_NumberOfIceCubes(COKE_CAN *cokeCan, int iceIndex)
{
	ICE_CHAIN *chain;
	chain = CokeCan_FindIce(cokeCan, iceIndex);
	return chain ? chain->ice.numberOfIceCubes() : 0;
}

const char* COKE_CAN_API CokeCan_IceCubeName(COKE_CAN *cokeCan, int iceIndex, int cubeIndex)
{
	ICE_CHAIN *chain;
	chain = CokeCan_FindIce(cokeCan, iceIndex);
	return chain ? chain->ice.nameOfIceCube(cubeIndex) : NULL;
}

int COKE_CAN_API CokeCan_RunIceCube(COKE_CAN *cokeCan, int iceIndex, int cubeIndex)
{
	ICE_CHAIN *chain;
	chain = CokeCan_FindIce(cokeCan, iceIndex);
	return chain ? chain->ice.runIceCube(cubeIndex, &cokeCan->iceCubeDelegate.base) : -1;
}
