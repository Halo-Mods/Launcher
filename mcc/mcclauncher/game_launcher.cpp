#include "mcclauncher_private_pch.h"

int launch_executable(
	const char* path,
	const char* command_line,
	const char* current_directory,
	const char* hooking_dll)
{
	STARTUPINFOA si = {};
	PROCESS_INFORMATION pi = {};
	DWORD exit_code = 0;
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

	assert(success);
	assert(SUCCEEDED(GetLastError()));

	ResumeThread(pi.hThread);
	while (WaitForSingleObject(pi.hProcess, INFINITE));
	CloseHandle(pi.hProcess);
	CloseHandle(pi.hThread);
	
	GetExitCodeProcess(pi.hProcess, &exit_code);

	return exit_code;
}
