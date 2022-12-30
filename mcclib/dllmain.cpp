#include "mcclib-private-pch.h"

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <detours.h>

bool enable_rich_presence;

BOOL __declspec(dllexport) WINAPI DllMain(HINSTANCE hinst, DWORD dwReason, LPVOID reserved)
{
	static constexpr char k_settings_path[MAX_PATH] = ".\\HMSettings.ini";

	if (!DetourIsHelperProcess())
	{
		if (dwReason == DLL_PROCESS_ATTACH)
		{
			DetourRestoreAfterWith();

			enable_rich_presence = !!GetPrivateProfileIntA("Discord", "EnableRichPresence", 1, k_settings_path);
			apply_all_hooks(false);
			steam_game_status_create();
			xlive_game_status_create();
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
			xlive_game_status_dispose();
			steam_game_status_dispose();
			apply_all_hooks(true);

			WritePrivateProfileStringA("Discord", "EnableRichPresence", enable_rich_presence ? "1" : "0", k_settings_path);
		}
	}

	return TRUE;
}
