#pragma once

extern uint64_t steam_userid;
extern uint64_t steam_lobbyid;

void steam_connect_to_lobby(uint64_t user_id, uint64_t lobby_id);
void steam_game_status_create();
void steam_game_status_dispose();
