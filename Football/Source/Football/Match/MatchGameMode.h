// Copyright, 2023, by NGD Studios AB. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "MatchDefs.h"

#include "MatchGameMode.generated.h"

class AFtbPlayerController;

/**
 * The multiplayer match game mode
 */
UCLASS()
class FOOTBALL_API AMatchGameMode : public AGameMode
{
	GENERATED_BODY()
	
public:

	AMatchGameMode(const FObjectInitializer& ObjectInitializer);

	virtual void StartMatch() override;
};
