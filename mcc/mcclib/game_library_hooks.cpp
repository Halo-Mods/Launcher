#include "mcclib_private_pch.h"

struct s_dll_name_function_pairing
{
	const wchar_t* dll_name;
	const wchar_t* hook_dll_name;
	HMODULE loaded_hook_module;
};

static s_dll_name_function_pairing game_dll_functions[] =
{
	{ L"halo1.dll",		L"../../../halomods/halo1lib.dll" },
	{ L"halo2.dll",		L"../../../halomods/halo2lib.dll" },
	{ L"halo3.dll",		L"../../../halomods/halo3lib.dll" },
	{ L"halo3odst.dll",	L"../../../halomods/atlaslib.dll" },
	{ L"haloreach.dll",	L"../../../halomods/omahalib.dll" },
	{ L"halo4.dll",		L"../../../halomods/midnightlib.dll" },
	{ L"groundhog.dll",	L"../../../halomods/groundhoglib.dll" },
};

HMODULE (WINAPI* real_LoadLibraryExW)(LPCWSTR lpLibFileName, HANDLE hFile, DWORD dwFlags) = LoadLibraryExW;
BOOL (WINAPI* real_FreeLibrary)(HMODULE hLibModule) = FreeLibrary;

HMODULE WINAPI hook_LoadLibraryExW(LPCWSTR lpLibFileName, HANDLE hFile, DWORD dwFlags)
{
	HMODULE result = real_LoadLibraryExW(lpLibFileName, hFile, dwFlags);

	for (s_dll_name_function_pairing& pairing : game_dll_functions)
	{
		if (!wcscmp(pairing.dll_name, lpLibFileName))
		{
			HMODULE loaded_hook_module = LoadLibraryW(pairing.hook_dll_name);
			pairing.loaded_hook_module = loaded_hook_module;
			break;
		}
	}

	return result;
}

BOOL hook_FreeLibrary(HMODULE hLibModule)
{
	for (s_dll_name_function_pairing& pairing : game_dll_functions)
	{
		if (pairing.loaded_hook_module == hLibModule)
		{
			real_FreeLibrary(pairing.loaded_hook_module);
			pairing.loaded_hook_module = nullptr;
		}
	}

	return real_FreeLibrary(hLibModule);
}

void game_library_hooks_initialize()
{
	DetourTransactionBegin();
	DetourUpdateThread(GetCurrentThread());
	DetourAttach(&(PVOID&)real_LoadLibraryExW, hook_LoadLibraryExW);
	DetourAttach(&(PVOID&)real_FreeLibrary, hook_FreeLibrary);
	DetourTransactionCommit();
}

void game_library_hooks_dispose()
{
	DetourTransactionBegin();
	DetourUpdateThread(GetCurrentThread());
	DetourDetach(&(PVOID&)real_LoadLibraryExW, hook_LoadLibraryExW);
	DetourDetach(&(PVOID&)real_FreeLibrary, hook_FreeLibrary);
	DetourTransactionCommit();
}
