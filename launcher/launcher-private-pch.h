#pragma once

#ifndef _DEBUG
#define DO_INTERFACE
#endif

#include <cstdio>
#include <cstdlib>
#include <cassert>
#include <malloc.h>

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <detours.h>

#ifdef DO_INTERFACE
#define GLATTER_HEADER_ONLY
#include <glatter/glatter.h>

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#endif

#include "launch.h"
#include "interface.h"

#include "ui/resource_loading.h"
