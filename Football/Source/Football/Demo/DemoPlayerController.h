// Copyright, 2023, by NGD Studios AB. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "DemoPlayerController.generated.h"

/**
 * Player controller for the demo version
 */
UCLASS()
class FOOTBALL_API ADemoPlayerController : public APlayerController
{
	GENERATED_BODY()
	
protected:
	ADemoPlayerController();
	virtual void BeginPlay() override;
};
