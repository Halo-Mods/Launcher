#include "mcclib-private-pch.h"

static HANDLE xlive_thread = INVALID_HANDLE_VALUE;
static LONG should_stop = FALSE;

struct xlive_lobby_player
{
	xlive_lobby_player** next;
	xlive_lobby_player** prev;
	char* __unknown10;
	void* __unknown18;
	uint64_t __unknown20;
	uint64_t __unknown28;
	uint64_t __unknown30;
	uint64_t xuid;
	wchar_t name[16];
};

struct xlive_lobby_player_list
{
	xlive_lobby_player* start;
	xlive_lobby_player* end;
};

struct s_ufg_data
{
	char __unknown00[0x70];
	xlive_lobby_player_list* xlive_lobby_members;
};

REFERENCE_DECLARE(0x14401B8D8, s_ufg_data*, ufg_data);

REFERENCE_DECLARE(0x143FB6730, void*, qword_143FB6730);
REFERENCE_DECLARE(0x143FB6778, UFG::eLifeCycleState, ufg_life_cycle_state);

bool xlive_is_ufg_active()
{
	return (qword_143FB6730 != nullptr);
}

uint32_t xlive_update()
{
	if (ufg_data == nullptr)
	{
		// hasn't been started by MCC yet
		return 250;
	}
	
	return 5000;
}

DWORD WINAPI xlive_thread_proc(LPVOID lpParam)
{
	while (!should_stop)
	{
		Sleep(xlive_update());
	}

	return 0;
}

void xlive_game_status_create()
{
	xlive_thread = CreateThread(
		nullptr,
		0,
		xlive_thread_proc,
		nullptr,
		0,
		nullptr);
}

void xlive_game_status_dispose()
{
	InterlockedAdd(&should_stop, 1);
	WaitForSingleObject(xlive_thread, INFINITE);
}
