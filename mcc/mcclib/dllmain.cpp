#include "mcclib_private_pch.h"

BOOL __declspec(dllexport) WINAPI DllMain(HINSTANCE hinst, DWORD dwReason, LPVOID reserved)
{
	if (!DetourIsHelperProcess())
	{
		if (dwReason == DLL_PROCESS_ATTACH)
		{
			DetourRestoreAfterWith();
			game_library_hooks_initialize();
		}
		else if (dwReason == DLL_PROCESS_DETACH)
		{
			game_library_hooks_dispose();
		}
	}

	return TRUE;
}
