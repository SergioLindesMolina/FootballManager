// Copyright, 2023, by NGD Studios AB. All rights reserved.


#include "DemoPlayerController.h"

ADemoPlayerController::ADemoPlayerController()
{
	bShowMouseCursor = true;
}

void ADemoPlayerController::BeginPlay()
{
	Super::BeginPlay();
	//SetInputMode(FInputModeUIOnly());
}
