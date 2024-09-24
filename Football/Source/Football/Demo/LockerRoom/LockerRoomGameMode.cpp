// Copyright, 2023, by NGD Studios AB. All rights reserved.

#include "LockerRoomGameMode.h"
#include <Football/CoreClasses/GameplayFramework/FootballPlayerController.h>

ALockerRoomGameMode::ALockerRoomGameMode()
{
	DefaultPawnClass      = TSubclassOf<APawn>();
	PlayerControllerClass = AFootballPlayerController::StaticClass();
}
