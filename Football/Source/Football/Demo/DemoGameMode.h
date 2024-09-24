// Copyright, 2023, by NGD Studios AB. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "DemoGameMode.generated.h"

/**
 * GameMode to use for the Demo
 */
UCLASS()
class FOOTBALL_API ADemoGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ADemoGameMode(const FObjectInitializer& ObjectInitializer);
};
