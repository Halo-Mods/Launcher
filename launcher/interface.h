#pragma once

enum e_interface_choice
{
	_interface_choice_launch_eac,
	_interface_choice_launch_modded,
	_interface_choice_launch_cancel,
	_interface_choice_launch_invalid
};

e_interface_choice run_launcher_interface();
