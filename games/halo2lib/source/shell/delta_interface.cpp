#include "halo2lib_private_pch.h"

const char* __cdecl gamelib_get_target_dll_filename()
{
	return "halo2.dll";
}

bool __cdecl gamelib_initialize(void* game_module)
{
	return apply_hooks(false);
}

bool __cdecl gamelib_dispose(void* game_module)
{
	return apply_hooks(true);
}

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

BOOL __declspec(dllexport) WINAPI DllMain(HINSTANCE hinst, DWORD dwReason, LPVOID reserved)
{
	BOOL success = FALSE;

	if (dwReason == DLL_PROCESS_ATTACH)
	{
		success = (BOOL)gamelib_initialize(hinst);
	}
	else if (dwReason == DLL_PROCESS_DETACH)
	{
		success = (BOOL)gamelib_dispose(hinst);
	}

	return TRUE;
}
