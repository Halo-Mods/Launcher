#include "mcclib_private_pch.h"

bool enable_rich_presence = true;

BOOL __declspec(dllexport) WINAPI DllMain(HINSTANCE hinst, DWORD dwReason, LPVOID reserved)
{
	//static constexpr char k_settings_path[MAX_PATH] = ".\\HMSettings.ini";

	if (!DetourIsHelperProcess())
	{
		if (dwReason == DLL_PROCESS_ATTACH)
		{
			DetourRestoreAfterWith();

			apply_hooks_for_module("MCC-Win64-Shipping.exe", false);
			apply_game_references_for_module("MCC-Win64-Shipping.exe");

			steam_game_status_create();
			if (enable_rich_presence)
			{
				discord_game_status_create();
			}
		}
		else if (dwReason == DLL_PROCESS_DETACH)
		{
			if (enable_rich_presence)
			{
				discord_game_status_dispose();
			}
			steam_game_status_dispose();

			apply_hooks_for_module("MCC-Win64-Shipping.exe", true);
		}
	}

	return TRUE;
}
