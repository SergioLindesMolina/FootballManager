// Copyright, 2023, by NGD Studios AB. All rights reserved.

#include "MatchPlayerController.h"

void AMatchPlayerController::ServerModifyAtkDef_Implementation(float Value)
{
}

void AMatchPlayerController::BeginPlay()
{
	Super::BeginPlay();
	SetShowMouseCursor(false);
}
