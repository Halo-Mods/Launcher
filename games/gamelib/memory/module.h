#pragma once

struct s_game_address
{
	const char* game_module;
	uintptr_t module_offset;
};

class c_hook
{
private:
	uintptr_t m_detour;
public:
	s_game_address m_target;
	
	void apply(bool revert);

	explicit c_hook(s_game_address target, uintptr_t detour);
};

extern uintptr_t get_module_address(const void* module, uintptr_t address);
extern void* register_game_reference(void* self, s_game_address target);
extern void apply_game_references_for_module(const char* game_module);
extern void apply_hooks_for_module(const char* game_module, bool revert);

#define _GAMELIB_DECLARE_REFERENCE(_type, _name, ...) _type& _name = *reinterpret_cast<_type*>(register_game_reference(&_name, __VA_ARGS__))
#define _GAMELIB_DECLARE_REFERENCE_ARRAY(_type, _name, _count, ...) _type(&_name)[_count] = *reinterpret_cast<_type(*)[_count]>(register_game_reference(&_name, __VA_ARGS__))

#define _GAMELIB_DECLARE_HOOK(_detour, ...) static c_hook COMBINE(hook_, LINE_ID(_detour))(__VA_ARGS__, reinterpret_cast<uintptr_t>(_detour))
