#pragma once

#include "common/common_public_pch.h"
#include "games/gamelib/gamelib_public_pch.h"

#include <discord_game_sdk.h>
#include <steam/steam_api.h>

#include "steam_manager.h"
#include "discord_manager.h"
#include "ufg.h"

#define MCC_REFERENCE(_address, _type, _name) _GAMELIB_DECLARE_REFERENCE(_type, _name, { "MCC-Win64-Shipping.exe", _address })
#define MCC_HOOK(_address, _detour) _GAMELIB_DECLARE_HOOK(_detour, { "MCC-Win64-Shipping.exe", _address })

#define DEV(...)

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <detours.h>
