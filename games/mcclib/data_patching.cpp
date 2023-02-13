#include "mcclib-private-pch.h"

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <detours.h>

// thanks twister xoxo

const long k_maximum_individual_modification_count = 1024;

long g_detour_hook_count = 0;
c_hook* detour_hooks[k_maximum_individual_modification_count];

module_address global_module;

uintptr_t global_address_get(uintptr_t rva)
{
	if (!global_module.address)
		global_module.pointer = GetModuleHandle(NULL);
	assert(global_module.pointer);

	return global_module.address + rva;
}

void apply_all_hooks(bool revert)
{
	c_hook* detour_hook = nullptr;

	for (long detour_index = 0; detour_index < g_detour_hook_count; detour_index++)
	{
		if (detour_hook = detour_hooks[detour_index]; detour_hook)
			detour_hook->apply(revert);
	}
}

c_hook::c_hook(uintptr_t address, module_address const function)
{
	m_addr.address = function.address;
	m_orig.address = address;

	if (g_detour_hook_count < k_maximum_individual_modification_count)
		detour_hooks[g_detour_hook_count++] = this;
}

bool c_hook::apply(bool revert)
{
	if (NO_ERROR != DetourTransactionBegin())
		return false;

	if (NO_ERROR != DetourUpdateThread(GetCurrentThread()))
		return false;

	if (revert)
	{
		if (NO_ERROR != DetourDetach(&m_orig.pointer, m_addr.pointer))
			return false;
	}
	else
	{
		if (NO_ERROR != DetourAttach(&m_orig.pointer, m_addr.pointer))
			return false;
	}

	if (NO_ERROR != DetourTransactionCommit())
		return false;

	return true;
}
