#include "mcclib-private-pch.h"

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

static HANDLE discord_thread = INVALID_HANDLE_VALUE;
static LONG should_stop = FALSE;

struct s_discord_data
{
	struct IDiscordCore* core;
	struct IDiscordUserManager* users;
	struct IDiscordActivityManager* activities;
	struct IDiscordLobbyManager* lobbies;
	DiscordUserId user_id;
};

void DISCORD_CALLBACK on_rich_presence_updated(void* data, EDiscordResult res)
{
	assert(res == DiscordResult_Ok);
}

const char* discord_get_game_state_string()
{
	const char* status = "Starting";

	if (xlive_is_ufg_active())
	{
		switch (ufg_life_cycle_state)
		{
			case UFG::eLifeCycleState::eLifeCycleState_Resume:
			case UFG::eLifeCycleState::eLifeCycleState_PreGame:
				status = "In menus";
				break;
			case UFG::eLifeCycleState::eLifeCycleState_StartGame:
			case UFG::eLifeCycleState::eLifeCycleState_InGame:
			case UFG::eLifeCycleState::eLifeCycleState_EndGame:
				status = "Ingame";
				break;
		}
	}

	return status;
}

void discord_rich_presence_update(s_discord_data* discord, const char* state)
{
	DiscordActivity discord_activity = {};

	discord_activity.application_id = DISCORD_APP_ID;
	strcpy(discord_activity.assets.large_image, "mcc_activity_nobg");
	strcpy(discord_activity.name, "Halomods Rich Presence " __TIMESTAMP__);
	strcpy(discord_activity.state, state);
	discord_activity.supported_platforms = DiscordActivitySupportedPlatformFlags_Desktop;

	// TODO: we could use xuids and xbox lobby ids instead?
	if (steam_userid != 0 && steam_lobbyid != 0)
	{
		uint64_t party_hash = XXH64(&steam_lobbyid, sizeof(steam_lobbyid), 0);
		snprintf(discord_activity.party.id, sizeof(discord_activity.party.id), "%016llx", party_hash);
		discord_activity.party.privacy = DiscordActivityPartyPrivacy_Public;
		discord_activity.party.size.current_size = 1;
		discord_activity.party.size.max_size = 16;

		snprintf(discord_activity.secrets.join, sizeof(discord_activity.secrets.join), "%llu/%llu", steam_lobbyid, steam_userid);
	}

	discord->activities->update_activity(discord->activities, &discord_activity, discord, on_rich_presence_updated);
}

uint32_t discord_update(s_discord_data* discord)
{
	discord->core->run_callbacks(discord->core);

	static bool needs_rich_presence_update = true;

	// Steam lobby ID changed
	static uint64_t previous_lobbyid = 0;
	if (previous_lobbyid != steam_lobbyid)
	{
		previous_lobbyid = steam_lobbyid;
		needs_rich_presence_update = true;
	}

	// MCC lobby details changed
	static const char* previous_game_state_string = nullptr;
	const char* game_state_string = discord_get_game_state_string();
	if (previous_game_state_string != game_state_string)
	{
		previous_game_state_string = game_state_string;
		needs_rich_presence_update = true;
	}

	// Game DLL status changed?

	// HaloMods CGB status changed?

	if (needs_rich_presence_update)
	{
		DEV("Updating Discord rich presence, status %s\n", game_state_string);
		discord_rich_presence_update(discord, previous_game_state_string);
		needs_rich_presence_update = false;
	}

	return 50;
}

void DISCORD_CALLBACK on_user_updated(void* data)
{
	s_discord_data* discord = reinterpret_cast<s_discord_data*>(data);
	struct DiscordUser user;
	discord->users->get_current_user(discord->users, &user);
	discord->user_id = user.id;
}

void DISCORD_CALLBACK on_activity_join(void* event_data, const char* secret)
{
	uint64_t user_id;
	uint64_t lobby_id;

	int result = sscanf(secret, "%llu/%llu", &lobby_id, &user_id);
	assert(result == 2);

	steam_connect_to_lobby(user_id, lobby_id);
}

void DISCORD_CALLBACK on_discord_log_print(void* hook_data, enum EDiscordLogLevel level, const char* message)
{
	DEV(message);
}

DWORD WINAPI discord_thread_proc(LPVOID lpParam)
{
	static IDiscordUserEvents users_events = {};
	static IDiscordActivityEvents activities_events = {};
	static s_discord_data discord = {};

	users_events.on_current_user_update = on_user_updated;
	activities_events.on_activity_join = on_activity_join;

	static DiscordCreateParams params = {};
	DiscordCreateParamsSetDefault(&params);
	params.client_id = DISCORD_CLIENT_ID;
	params.flags = DiscordCreateFlags_Default;
	params.event_data = &discord;
	params.user_events = &users_events;
	params.activity_events = &activities_events;
	EDiscordResult res = DiscordCreate(DISCORD_VERSION, &params, &discord.core);
	if (res != DiscordResult_Ok)
	{
		DEV("Failed to create Discord Game SDK instance (%u)\n", res);
		return 1;
	}

	discord.core->set_log_hook(discord.core, DiscordLogLevel_Debug, &discord, on_discord_log_print);

	discord.users = discord.core->get_user_manager(discord.core);
	discord.activities = discord.core->get_activity_manager(discord.core);
	discord.lobbies = discord.core->get_lobby_manager(discord.core);

	discord.activities->register_command(discord.activities, "steam://run/976730//-enabled/");

	while (!should_stop)
	{
		Sleep(discord_update(&discord));
	}

	discord.activities->clear_activity(discord.activities, &discord, on_rich_presence_updated);

	discord.core->destroy(discord.core);

	return 0;
}

void discord_game_status_create()
{
	discord_thread = CreateThread(
		nullptr,
		0,
		discord_thread_proc,
		nullptr,
		0,
		nullptr);
}

void discord_game_status_dispose()
{
	InterlockedAdd(&should_stop, 1);
	WaitForSingleObject(discord_thread, INFINITE);
}
