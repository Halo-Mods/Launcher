#include "launcher-private-pch.h"

int launch_hooked(const char* executable, const char* hook_dll)
{
	STARTUPINFOA si = {};
	PROCESS_INFORMATION pi = {};
	DWORD exit_code = 0;

	si.cb = sizeof(si);

	bool success = DetourCreateProcessWithDllExA(
		executable,
		nullptr,
		nullptr,
		nullptr,
		false,
		CREATE_SUSPENDED,
		nullptr,
		nullptr,
		&si,
		&pi,
		hook_dll,
		nullptr);
	assert(success);
	assert(SUCCEEDED(GetLastError()));

	ResumeThread(pi.hThread);
	WaitForSingleObject(pi.hProcess, INFINITE);

	CloseHandle(pi.hProcess);
	CloseHandle(pi.hThread);
	GetExitCodeProcess(pi.hProcess, &exit_code);

	return exit_code;
}

int launch_eac(const char* executable)
{
	STARTUPINFOA si = {};
	PROCESS_INFORMATION pi = {};
	DWORD exit_code = 0;

	si.cb = sizeof(si);

	bool success = CreateProcessA(
		executable,
		nullptr,
		nullptr,
		nullptr,
		false,
		CREATE_SUSPENDED,
		nullptr,
		nullptr,
		&si,
		&pi);
	assert(success);

	ResumeThread(pi.hThread);
	WaitForSingleObject(pi.hProcess, INFINITE);

	CloseHandle(pi.hProcess);
	CloseHandle(pi.hThread);
	GetExitCodeProcess(pi.hProcess, &exit_code);

	return exit_code;
}
