// Copyright, 2023, by NGD Studios AB. All rights reserved.

#include "ManagerGameState.h"
#include "ManagerPlayerState.h"
#include "Backend/BackendBridgeLibrary.h"

void AManagerGameState::BeginPlay()
{
	//TODO Temporal until we decide how the scout system will work
	//UBackendScoutAsyncAction* AsyncAction = UBackendScoutAsyncAction::AsyncScoutAction(this);
	//AsyncAction->ScoutTeamGenerator = ScoutTeamGenerator;
	//AsyncAction->Activate();

	UBackendGetServerTime* AsyncActionGetServerTime = UBackendGetServerTime::AsyncGetServerTime(this);
	AsyncActionGetServerTime->Activate();
}

void AManagerGameState::SetMoney(int32 Money)
{
	GetWorld()->GetFirstPlayerController()->GetPlayerState<AManagerPlayerState>()->SetMoney(Money);
}
