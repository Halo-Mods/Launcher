#pragma once

#include <discord_game_sdk.h>
#include <steam_api.h>
#include <xxhash.h>

#include <cassert>
#include <cstdint>

using dword = uint32_t;
using byte = uint8_t;

#include "debug_print.h"
#include "data_patching.h"
#include "steam_manager.h"
#include "discord_manager.h"
#include "xlive_manager.h"
