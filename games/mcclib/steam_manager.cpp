#include "mcclib-private-pch.h"

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

static HANDLE steam_thread = INVALID_HANDLE_VALUE;
static LONG should_stop = FALSE;
static ISteamFriends* steam_friends = nullptr;
static ISteamUser* steam_user = nullptr;

uint64_t steam_userid = 0;
uint64_t steam_lobbyid = 0;

uint32_t steam_update()
{
	assert(steam_friends);
	assert(steam_user);

	bool logged_on = false;

	// when MCC shuts off steamapi and we're timed for an update we'll end up using a dangling pointer
	// if it happens? let's just ignore it $TODO don't
	__try
	{
		logged_on = steam_user->BLoggedOn();
	}
	__except (EXCEPTION_EXECUTE_HANDLER)
	{
		DEV("Caught Steam API dangling pointer\n");
	}

	if (!logged_on)
	{
		return 500;
	}

	CSteamID uid = steam_user->GetSteamID();
	FriendGameInfo_t friend_game_info = {};
	if (!steam_friends->GetFriendGamePlayed(uid, &friend_game_info))
	{
		return 250;
	}
	
	InterlockedExchange64(reinterpret_cast<LONG64*>(&steam_userid), uid.ConvertToUint64());
	InterlockedExchange64(reinterpret_cast<LONG64*>(&steam_lobbyid), friend_game_info.m_steamIDLobby.ConvertToUint64());

	return 5000;
}

DWORD WINAPI steam_thread_proc(LPVOID lpParam)
{
	Sleep(5000);

	// in case steamapi hasn't been loaded by MCC yet
	while (SteamAPI_Init == nullptr)
	{
		Sleep(50);
	}

	// won't function until MCC has initialised steam
	while (steam_friends == nullptr)
	{
		steam_friends = SteamFriends();
		Sleep(250);
	}

	steam_user = SteamUser();

	DEV("Steam initialised...\n");

	while (!should_stop)
	{
		Sleep(steam_update());
	}

	return 0;
}

void steam_connect_to_lobby(uint64_t user_id, uint64_t lobby_id)
{
	if (steam_lobbyid != lobby_id)
	{
		char fmt[256];
		snprintf(fmt, sizeof(fmt), "steam://joinlobby/976730/%llu/%llu", lobby_id, user_id);
		fmt[sizeof(fmt) - 1] = '\0';
		DEV("Steam: executing %s\n", fmt);
		ShellExecuteA(nullptr, nullptr, fmt, nullptr, nullptr, SW_SHOW);
	}
	else
	{
		DEV("Steam: blocking repeat lobby join, we're already in the lobby\n");
	}
}

void steam_game_status_create()
{
	steam_thread = CreateThread(
		nullptr,
		0,
		steam_thread_proc,
		nullptr,
		0,
		nullptr);
}

void steam_game_status_dispose()
{
	InterlockedAdd(&should_stop, 1);
	WaitForSingleObject(steam_thread, INFINITE);
}
