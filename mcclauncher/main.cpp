#include "mcclauncher_private_pch.h"

int WINAPI WinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	PSTR pCmdLine,
	int nCmdShow)
{
	c_halomods_ul_interface app;
	app.run();

	s_game_launch_parameters* launch_parameters = &app.launch_parameters;
	int return_code = launch_executable("mcc\\binaries\\win64\\MCC-Win64-Shipping.exe", pCmdLine, nullptr, launch_parameters->extensions_enabled ? "mcclib.dll" : nullptr);
	return return_code;
}
