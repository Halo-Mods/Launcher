#pragma once

#include "common/common_public_pch.h"
#include "games/gamelib/gamelib_public_pch.h"

#define HALO2_DECLARE_HOOK(_address, _detour) DECLARE_HOOK(_address - 0x180000000, _detour)
#define HALO2_DECLARE_REFERENCE(_address, _type, _name) DECLARE_REFERENCE(_address - 0x180000000, _type, _name)

#include "main/main_time.h"
