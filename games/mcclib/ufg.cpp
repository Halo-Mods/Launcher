#include "mcclib_private_pch.h"

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

MCC_REFERENCE(0x14401B8D8, s_ufg_data*, ufg_data);

MCC_REFERENCE(0x143FB6730, void*, qword_143FB6730);
MCC_REFERENCE(0x143FB6778, UFG::eLifeCycleState, ufg_life_cycle_state);

bool is_ufg_active()
{
	return (qword_143FB6730 != nullptr);
}
