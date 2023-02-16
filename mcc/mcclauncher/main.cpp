#include "mcclauncher_private_pch.h"
#include <thread>

void run_game_launcher(s_game_launch_parameters* launch_parameters)
{
	c_halomods_ul_interface app;
	app.run();
	*launch_parameters = app.launch_parameters;
}

int WINAPI WinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	PSTR pCmdLine,
	int nCmdShow)
{
	s_game_launch_parameters launch_parameters;
	std::thread game_launcher_thread(run_game_launcher, &launch_parameters);
	game_launcher_thread.join();

	int return_code = EXIT_SUCCESS;
	
	if (!launch_parameters.cancelled)
	{
		return_code = launch_executable("mcc\\binaries\\win64\\MCC-Win64-Shipping.exe", pCmdLine, nullptr, launch_parameters.extensions_enabled ? "mcclib.dll" : nullptr);
	}
	
	return return_code;
}
