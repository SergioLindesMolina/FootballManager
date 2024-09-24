// Copyright, 2023, by NGD Studios AB. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ManagerGameMode.generated.h"

/**
 * Game mode for the manager gameplay
 */
UCLASS()
class FOOTBALL_API AManagerGameMode : public AGameModeBase
{
	GENERATED_BODY()

	virtual void InitGameState() override;

	void InitConsoleVariables();

public:
	AManagerGameMode(const FObjectInitializer& ObjectInitializer);

	IConsoleCommand* UseFieldZonesCommand;
};
