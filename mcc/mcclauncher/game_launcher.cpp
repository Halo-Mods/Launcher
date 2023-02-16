#include "mcclauncher_private_pch.h"

int launch_executable(
	const char* path,
	const char* command_line,
	const char* current_directory,
	const char* hooking_dll,
	bool blocking)
{
	STARTUPINFOA si = {};
	PROCESS_INFORMATION pi = {};
	int result = EXIT_SUCCESS;
	bool success = false;

	si.cb = sizeof(si);
	
	if (hooking_dll != nullptr)
	{
		success = DetourCreateProcessWithDllExA(
			path,
			const_cast<char*>(command_line),
			nullptr,
			nullptr,
			false,
			CREATE_SUSPENDED,
			nullptr,
			current_directory,
			&si,
			&pi,
			hooking_dll,
			nullptr);
	}
	else
	{
		success = CreateProcessA(
			path,
			const_cast<char*>(command_line),
			nullptr,
			nullptr,
			false,
			CREATE_SUSPENDED,
			nullptr,
			current_directory,
			&si,
			&pi);
	}

	if (success && SUCCEEDED(GetLastError()))
	{
		ResumeThread(pi.hThread);

		if (blocking)
		{
			while (WaitForSingleObject(pi.hProcess, INFINITE));
			CloseHandle(pi.hProcess);
			CloseHandle(pi.hThread);
			GetExitCodeProcess(pi.hProcess, (DWORD*)&result);
		}
	}
	else
	{
		result = EXIT_FAILURE;
	}

	return result;
}
