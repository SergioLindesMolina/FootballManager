// Copyright, 2023, by NGD Studios AB. All rights reserved.

#include "BaseChip.h"

#include <Components/WidgetComponent.h>
#include "Football/Formation/FollowMouseComponent.h"

ABaseChip::ABaseChip()
{
	SceneComp = CreateDefaultSubobject<USceneComponent>("Scene Component");
	SceneComp->SetupAttachment(this->RootComponent);
	RootComponent = SceneComp;
	ChipMesh = CreateDefaultSubobject<UStaticMeshComponent>("ChipMesh");
	ChipMesh->SetupAttachment(SceneComp);
	ChipMesh->SetMaskFilterOnBodyInstance(3);

	ChipWidget = CreateDefaultSubobject<UWidgetComponent>("Widget Component");
	ChipWidget->SetupAttachment(SceneComp);

	FollowMouseComponent = CreateDefaultSubobject<UFollowMouseComponent>("FollowMouseComponent");
	AddOwnedComponent(FollowMouseComponent);
}

void ABaseChip::InitializeWidget()
{
	ChipWidget->SetWidgetClass(ChipWidgetClass);
	ChipWidget->InitWidget();
}

void ABaseChip::SetChipWidget()
{
	checkNoEntry();
}

