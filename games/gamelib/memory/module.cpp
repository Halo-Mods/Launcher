#include "gamelib_private_pch.h"
#include <TlHelp32.h>

const long k_maximum_individual_modification_count = 1024;

static long g_detour_hook_count = 0;
static c_hook* detour_hooks[k_maximum_individual_modification_count];

static void* game_module = nullptr;

void* __cdecl get_game_module()
{
	void* module = nullptr;

	if (game_module != nullptr)
	{
		module = game_module;
	}
	else
	{
		const char* game_module_name = gamelib_get_target_dll_filename();
		DWORD current_process_id = GetCurrentProcessId();
		HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, current_process_id);

		MODULEENTRY32 module_entry = {};
		module_entry.dwSize = sizeof(module_entry);
		if (Module32First(snapshot, &module_entry))
		{
			do
			{
				if (!strcmp(game_module_name, module_entry.szModule))
				{
					module = module_entry.hModule;
					break;
				}
			} while (Module32Next(snapshot, &module_entry));
		}

		CloseHandle(snapshot);

		game_module = module;
	}

	return module;
}

void* __cdecl get_game_address(void* module, uintptr_t game_offset)
{
	assert(module != nullptr);
	union game_address resolved_address;
	resolved_address.pointer = module;
	resolved_address.address += game_offset;
	return resolved_address.pointer;
}

bool __cdecl apply_hooks(bool revert)
{
	c_hook* detour_hook = nullptr;
	bool success = true;

	for (long detour_index = 0; detour_index < g_detour_hook_count; detour_index++)
	{
		detour_hook = detour_hooks[detour_index];

		if (detour_hook != nullptr)
		{
			success = detour_hook->apply(revert);

			if (success == false)
			{
				break;
			}
		}
	}

	return success;
}

bool c_hook::apply(bool revert)
{
	bool success = false;

	DetourTransactionBegin();
	DetourUpdateThread(GetCurrentThread());
	
	if (!revert)
	{
		DetourAttach(&m_target.pointer, m_detour.pointer);
	}
	else
	{
		DetourDetach(&m_target.pointer, m_detour.pointer);
	}
	
	success = (DetourTransactionCommit() == NO_ERROR);

	return success;
}

c_hook::c_hook(void* target, void* detour)
{
	m_target.pointer = target;
	m_detour.pointer = detour;

	if (g_detour_hook_count < k_maximum_individual_modification_count)
	{
		detour_hooks[g_detour_hook_count++] = this;
	}
}
