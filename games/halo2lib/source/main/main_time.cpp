#include "halo2lib_private_pch.h"

HALO2_DECLARE_HOOK(0x1806BDC90, main_time_get_native_tick_rate);

uint64_t __cdecl main_time_get_native_tick_rate()
{
	return 30;
}
