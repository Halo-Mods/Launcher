#include "halo3lib_private_pch.h"

HALO3_DECLARE_HOOK(0x1800E4058, game_options_new);
HALO3_DECLARE_REFERENCE(0x180B0251A, uint8_t, g_game_tickrate_override);

void __cdecl game_options_new(struct game_options* options)
{
	g_game_tickrate_override = 30;
	INVOKE_HOOK_ORIGINAL(game_options_new, options);
}
