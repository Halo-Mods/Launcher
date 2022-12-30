#include "launcher-private-pch.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR pCmdLine, int nCmdShow)
{
	int return_code = EXIT_SUCCESS;
	e_interface_choice choice = _interface_choice_launch_invalid;

	const char* enabled = strstr(pCmdLine, "-enabled");
	if (enabled != nullptr)
	{
		choice = _interface_choice_launch_modded;
	}
	else
	{
		choice = run_launcher_interface();
	}

	switch (choice)
	{
	case _interface_choice_launch_eac:
		{
			return_code = launch_eac("_mcclauncher.exe");
		}
		break;
	case _interface_choice_launch_modded:
		{
			return_code = launch_hooked("MCC\\Binaries\\Win64\\MCC-Win64-Shipping.exe", "mcclib64.dll");
		}
		break;
	}

	return return_code;
}
