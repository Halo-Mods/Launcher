#pragma once

#include <cstdlib>

#include <Ultralight/Ultralight.h>
#include <AppCore/AppCore.h>

#include "common/common_public_pch.h"

namespace ul = ultralight;
#include "ul_interface.h"
#include "game_launcher.h"

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <detours.h>
