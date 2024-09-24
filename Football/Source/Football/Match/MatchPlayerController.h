// Copyright, 2023, by NGD Studios AB. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MatchPlayerController.generated.h"

/**
 * Player controller for the multiplayer match game mode
 */
UCLASS()
class FOOTBALL_API AMatchPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	UFUNCTION(Server, Reliable)
	void ServerModifyAtkDef(float Value);

	virtual void BeginPlay() override;
};
