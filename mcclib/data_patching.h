#pragma once

#define DECLFUNC(ADDR, R, CC, ...) reinterpret_cast<R(CC*)(__VA_ARGS__)>(global_address_get(ADDR - 0x140000000))
#define INVOKE(ADDR, TYPE, ...) reinterpret_cast<decltype(TYPE)*>(global_address_get(ADDR - 0x140000000))(__VA_ARGS__)

// #define HOOK_DECLARE_CALL_WITH_ADDRESS(ADDR, ADDR2, NAME) c_hook_call STRCONCAT(NAME##_hook,__LINE__)(ADDR, { .address = ADDR2 })
// #define HOOK_DECLARE_CALL(ADDR, NAME) c_hook_call STRCONCAT(NAME##_hook,__LINE__)(ADDR, { .pointer = NAME })
#define HOOK_DECLARE(ADDR, NAME) c_hook NAME##_hook(global_address_get(ADDR - 0x140000000), { .pointer = NAME })
#define HOOK_DECLARE_CLASS(ADDR, CLASS, NAME) c_hook CLASS##_##NAME##_hook(global_address_get(ADDR - 0x140000000), { .pointer = CLASS::NAME })
#define HOOK_INVOKE(RESULT, NAME, ...) { NAME##_hook.apply(true); RESULT reinterpret_cast<decltype(NAME)*>(NAME##_hook.get_original())(__VA_ARGS__); NAME##_hook.apply(false); }
// #define HOOK_INVOKE_CLASS(RESULT, CLASS, NAME, TYPE, ...) { CLASS##_##NAME##_hook.apply(true); RESULT reinterpret_cast<TYPE>(CLASS##_##NAME##_hook.get_original())(__VA_ARGS__); CLASS##_##NAME##_hook.apply(false); }

// #define DATA_PATCH_DECLARE(ADDR, NAME, ...) c_data_patch STRCONCAT(NAME##_patch,__LINE__)(ADDR, NUMBEROF(__VA_ARGS__), __VA_ARGS__)
// #define DATA_PATCH_DECLARE2(ADDR, NAME, SIZE, ...) c_data_patch STRCONCAT(NAME##_patch,__LINE__)(ADDR, SIZE, __VA_ARGS__)

#define REFERENCE_DECLARE(address, type, name) type& name = *reinterpret_cast<type*>(global_address_get(address - 0x140000000))
#define REFERENCE_DECLARE_ARRAY(address, type, name, count) type(&name)[count] = *reinterpret_cast<type(*)[count]>(global_address_get(address - 0x140000000))
#define REFERENCE_DECLARE_STATIC_ARRAY(address, type, count, name) c_static_array<type, count> &name = *reinterpret_cast<c_static_array<type, count>*>(global_address_get(address - 0x140000000))

union module_address
{
	uintptr_t address;
	byte* data;
	void* pointer;
};

extern module_address global_module;

extern uintptr_t global_address_get(uintptr_t rva);
extern void apply_all_hooks(bool revert);

class c_hook
{
public:
	c_hook(uintptr_t address, module_address const function);

	bool apply(bool revert);

	uintptr_t get_address()
	{
		return m_addr.address;
	}

	uintptr_t get_original()
	{
		return m_orig.address;
	}

private:
	module_address m_addr;
	module_address m_orig;
};
