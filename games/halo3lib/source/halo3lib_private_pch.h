#pragma once

#include "common/common_public_pch.h"
#include "games/gamelib/gamelib_public_pch.h"

#define HALO3_DECLARE_HOOK(_address, _detour) DECLARE_HOOK(_address - 0x180000000, _detour)
#define HALO3_DECLARE_REFERENCE(_address, _type, _name) DECLARE_REFERENCE(_address - 0x180000000, _type, _name)

#include "game/game_options.h"
