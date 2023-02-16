#pragma once

union game_address
{
	uintptr_t address;
	void* pointer;
};

class c_hook
{
public:
	union game_address m_target;
	union game_address m_detour;
	
	bool apply(bool revert);

	explicit c_hook(void* target, void* detour);
};

extern void* __cdecl get_game_module();
extern void* __cdecl get_game_address(void* module, uintptr_t game_offset);
extern bool __cdecl apply_hooks(bool revert);

#define DECLARE_REFERENCE(_offset, _type, _name) _type& _name = *reinterpret_cast<_type*>(get_game_address(get_game_module(), _offset))
#define DECLARE_REFERENCE_ARRAY(_offset, _type, _name, _count) _type(&_name)[_count] = *reinterpret_cast<_type(*)[_count]>(get_game_address(get_game_module(), _offset))

#define DECLARE_HOOK(_offset, _detour) static c_hook COMBINE(_detour, _hook)(get_game_address(get_game_module(), _offset), _detour)
#define INVOKE_HOOK_ORIGINAL(_func, ...) reinterpret_cast<decltype(_func)*>(_func##_hook.m_target.pointer)(__VA_ARGS__)
