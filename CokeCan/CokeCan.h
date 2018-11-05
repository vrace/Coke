#ifndef COKE_CAN_H
#define COKE_CAN_H

#define COKE_CAN_API __stdcall

#ifdef __cplusplus
extern "C" {
#endif

	struct CokeCanDelegate;

	typedef void(*COKE_CAN_PRINT_FUNC)(struct CokeCanDelegate *delegate, const char *str);
	typedef void(*COKE_CAN_INPUT_FUNC)(struct CokeCanDelegate *delegate, char *buf, int size);

	typedef struct CokeCanDelegate
	{
		COKE_CAN_PRINT_FUNC print;
		COKE_CAN_INPUT_FUNC input;
	} COKE_CAN_DELEGATE;

	typedef struct CokeCan COKE_CAN;
	typedef int (*ENUM_ICE_FUNC)(const char *iceName);
	typedef int (*ENUM_CUBE_FUNC)(const char *cubeName);

	COKE_CAN* COKE_CAN_API CokeCan_Init(COKE_CAN_DELEGATE *delegate);
	void COKE_CAN_API CokeCan_Free(COKE_CAN *cokeCan);

	void COKE_CAN_API CokeCan_LoadIceCubes(COKE_CAN *cokeCan);

	int COKE_CAN_API CokeCan_NumberOfIce(COKE_CAN *cokeCan);
	const char* COKE_CAN_API CokeCan_IceName(COKE_CAN *cokeCan, int iceIndex);

	int COKE_CAN_API CokeCan_NumberOfIceCubes(COKE_CAN *cokeCan, int iceIndex);
	const char* COKE_CAN_API CokeCan_IceCubeName(COKE_CAN *cokeCan, int iceIndex, int cubeIndex);

	int COKE_CAN_API CokeCan_RunIceCube(COKE_CAN *cokeCan, int iceIndex, int cubeIndex);

#ifdef __cplusplus
}
#endif

#endif
