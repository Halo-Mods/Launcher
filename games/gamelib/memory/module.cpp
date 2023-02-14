#include "gamelib_private_pch.h"
#include <vector>

struct s_game_reference_declaration
{
	uintptr_t* reference;
	s_game_address target;
};

static std::vector<s_game_reference_declaration> references;
static char bad_reference[] = { 'b', 'a', 'd', 'b', 'a', 'd', 'b', 'a', 'd', 'b', 'a', 'd', 'b', 'a', 'd', '\0' };

static std::vector<c_hook*> hooks;

uintptr_t get_module_address(void* module, uintptr_t address)
{
	PIMAGE_DOS_HEADER dos_header = reinterpret_cast<PIMAGE_DOS_HEADER>(module);
	PIMAGE_NT_HEADERS64 nt_headers = reinterpret_cast<PIMAGE_NT_HEADERS64>(reinterpret_cast<uint8_t*>(module) + dos_header->e_lfanew);

	return reinterpret_cast<uintptr_t>(module) + (address - nt_headers->OptionalHeader.ImageBase);
}

uintptr_t resolve_game_address(const s_game_address* game_address)
{
	void* module = GetModuleHandle(game_address->game_module);
	return get_module_address(module, game_address->module_offset);
}

extern void* register_game_reference(void* self, s_game_address target)
{
	references.push_back({ reinterpret_cast<uintptr_t*>(self), target });

	// has to dereference something.
	return bad_reference;
}

extern void apply_game_references_for_module(const char* game_module)
{
	for (s_game_reference_declaration& game_reference : references)
	{
		if (!strcmp(game_module, game_reference.target.game_module))
		{
			*game_reference.reference = resolve_game_address(&game_reference.target);
		}
	}
}

extern void apply_hooks_for_module(const char* game_module, bool revert)
{
	for (c_hook* hook : hooks)
	{
		assert(hook);

		if (!strcmp(game_module, hook->m_target.game_module))
		{
			hook->apply(revert);
		}
	}
}

void c_hook::apply(bool revert)
{
	void* target_resolved = reinterpret_cast<void*>(resolve_game_address(&m_target));
	void* detour = reinterpret_cast<void*>(m_detour);

	DetourTransactionBegin();
	DetourUpdateThread(GetCurrentThread());
	if (!revert)
	{
		DetourAttach(&target_resolved, detour);
	}
	else
	{
		DetourDetach(&target_resolved, detour);
	}
	DetourTransactionCommit();
}

c_hook::c_hook(s_game_address target, uintptr_t detour) :
	m_target(target),
	m_detour(detour)
{
	hooks.push_back(this);
}
