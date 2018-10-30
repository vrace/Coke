#ifndef ICE_CUBE_DELEGATE_H
#define ICE_CUBE_DELEGATE_H

#ifdef __cplusplus
extern "C" {
#endif

	struct IceCubeDelegate;

	typedef void(*PRINT_FUNC)(struct IceCubeDelegate *delegate, const char *str);
	typedef void(*INPUT_FUNC)(struct IceCubeDelegate *delegate, char *buf, int size);

	typedef struct IceCubeDelegate
	{
		PRINT_FUNC print;
		INPUT_FUNC input;
	} ICE_CUBE_DELEGATE;

#ifdef __cplusplus
}
#endif

#endif
