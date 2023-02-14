#pragma once

namespace UFG
{
	enum class eLifeCycleState : uint32_t
	{
		eLifeCycleState_None,
		eLifeCycleState_Resume,
		eLifeCycleState_PreGame,
		eLifeCycleState_StartGame,
		eLifeCycleState_InGame,
		eLifeCycleState_EndGame,
		eLifeCycleState_InMatch,
		eLifeCycleState_EndMatch,
		eLifeCycleState_BetweenMatch,
		_9,
		eLifeCycleState_Leaving,
		eLifeCycleState_Joining,
		eLifeCycleState_MM_Begin,
		eLifeCycleState_MM_Recycle,
		eLifeCycleState_MM_FindMatch,
		eLifeCycleState_MM_ElectHost,
		eLifeCycleState_MM_ConnectToLobbyHost,
		eLifeCycleState_MM_AcceptMatch,
		eLifeCycleState_MM_WaitingForPeers,
		eLifeCycleState_MM_PickTeams,
		eLifeCycleState_MM_PrepareMap,
		eLifeCycleState_MM_PrepareGameHost,
		eLifeCycleState_MM_LaunchMatch,
		eLifeCycleState_MM_Leaving,
		eLifeCycleState_MM_Aborting,
		_25,
		eLifeCycleState_Count,
	};
};

extern UFG::eLifeCycleState& ufg_life_cycle_state;

bool is_ufg_active();
