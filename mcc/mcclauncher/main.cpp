#include "mcclauncher_private_pch.h"
#include <thread>

void run_game_launcher(s_game_launch_parameters* launch_parameters)
{
	c_halomods_ul_interface app;
	app.run();
	*launch_parameters = app.launch_parameters;
}

void add_halomods_dll_search_path()
{
	c_static_wchar_string<MAX_PATH> dll_directory;
	wchar_t current_directory[MAX_PATH] = {};

	GetCurrentDirectoryW(MAX_PATH, current_directory);
	dll_directory.print(L"%s\\halomods", current_directory);
	SetDllDirectoryW(dll_directory.get_string());
}

void reset_dll_search_paths()
{
	SetDllDirectoryW(nullptr);
}

int WINAPI WinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	PSTR pCmdLine,
	int nCmdShow)
{
	add_halomods_dll_search_path();

	bool blocking = !(strstr(pCmdLine, "-non-blocking") != nullptr);
	int return_code = EXIT_SUCCESS;

	s_game_launch_parameters launch_parameters;
	std::thread game_launcher_thread(run_game_launcher, &launch_parameters);
	game_launcher_thread.join();

	reset_dll_search_paths();
	
	if (!launch_parameters.cancelled)
	{
		if (launch_parameters.extensions_enabled)
		{
#if UE4_INTEGRATION
			return_code = launch_executable("mcc\\binaries\\win64\\MCC-Win64-Shipping.exe", pCmdLine, nullptr, "mcclib.dll", blocking);
#else
			return_code = launch_executable("halomods\\interface.exe", pCmdLine, nullptr, nullptr, blocking);
#endif
		}
		else
		{
			return_code = launch_executable("_mcclauncher.exe", pCmdLine, nullptr, nullptr, blocking);
		}
	}
	
	return return_code;
}
