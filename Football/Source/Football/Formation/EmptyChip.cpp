// Copyright, 2023, by NGD Studios AB. All rights reserved.


#include "EmptyChip.h"
#include "FootballerChip.h"

#include <Components/WidgetComponent.h>
#include <Components/TextBlock.h>

#include <Football/UI/UserWidget/SquadScreen/LineUp/FootballerPositionWidget.h>
#include <Football/Formation/FollowMouseComponent.h>
#include <Football/UI/UserWidget/Shared/ChipFootballer/ChipFootballerWidget.h>
#include <Football/Team/TeamGenerator.h>
#include <Football/Manager/ManagerPlayerController.h>


void AEmptyChip::BeginPlay()
{
	Super::BeginPlay();
	AManagerPlayerController* ManagerPC = GetWorld()->GetFirstPlayerController<AManagerPlayerController>();
	ManagerPC->OnStatusEmptyChips.AddUObject(this, &AEmptyChip::ToggleChipVisibility);
}


void AEmptyChip::SetChipWidget()
{
	InitializeWidget();

}

void AEmptyChip::ToggleChipVisibility(AActor* OverlapedActor)
{
	AFootballerChip* OverlappedChip = Cast<AFootballerChip>(OverlapedActor);
	UChipFootballerWidget* ChipFootballerWidget = OverlappedChip->GetFootballerWidget();
	if(ChipMesh->IsVisible())
	{
		ChipMesh->SetVisibility(false);
		ChipWidget->SetVisibility(false);
		ChipMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}
	else
	{
		ChipMesh->SetVisibility(true);
		ChipWidget->SetVisibility(true);
		ChipMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
		ChipMesh->SetCollisionObjectType(ECC_WorldDynamic);
	}
}