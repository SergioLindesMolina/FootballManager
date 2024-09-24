// Copyright, 2023, by NGD Studios AB. All rights reserved.


#include "DemoGameMode.h"
#include "DemoGameState.h"
#include "DemoPlayerController.h"
#include "DemoPlayerState.h"

ADemoGameMode::ADemoGameMode(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	GameStateClass = ADemoGameState::StaticClass();
	PlayerControllerClass = ADemoPlayerController::StaticClass();
	PlayerStateClass = ADemoPlayerState::StaticClass();
}

