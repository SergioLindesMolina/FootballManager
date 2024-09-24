// Copyright, 2023, by NGD Studios AB. All rights reserved.


#include "ManagerGameMode.h"
#include "ManagerGameState.h"
#include "ManagerPlayerState.h"
#include "ManagerPlayerController.h"

void AManagerGameMode::InitGameState()
{
	Super::InitGameState();
	InitConsoleVariables();
}

AManagerGameMode::AManagerGameMode(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	GameStateClass = AManagerGameState::StaticClass();
	PlayerStateClass = AManagerPlayerState::StaticClass();
	PlayerControllerClass = AManagerPlayerController::StaticClass();
}

void AManagerGameMode::InitConsoleVariables()
{
	IConsoleManager::Get().RegisterConsoleVariable(TEXT("UseFieldZones"),
		1,
		TEXT("Set the SquadScreen chip interaction.\n")
		TEXT("0 = EmptyChips Mode\n")
		TEXT("1 = FieldZones Mode\n"),
		ECVF_Cheat);
}