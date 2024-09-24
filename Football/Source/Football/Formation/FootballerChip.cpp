// Copyright, 2023, by NGD Studios AB. All rights reserved.


#include "FootballerChip.h"

#include <Components/WidgetComponent.h>

#include <Football/UI/UserWidget/Shared/ChipFootballer/ChipFootballerWidget.h>
#include <Football/Formation/FollowMouseComponent.h>
#include <Football/Team/TeamGenerator.h>


void AFootballerChip::BeginPlay()
{
	Super::BeginPlay();

	FollowMouseComponent->OnSwapedActorsEvent.AddUObject(this, &AFootballerChip::SwapPositions);

}

void AFootballerChip::SetChipWidget()
{
	InitializeWidget();

	UChipFootballerWidget* FootballerBox = Cast<UChipFootballerWidget>(ChipWidget->GetUserWidgetObject());

	if(ensure(IsValid(FootballerBox)))
	{
		ChipFootballerWidget = FootballerBox;
	}
	else
	{
		ChipFootballerWidget = nullptr;
	}
}


void AFootballerChip::SwapPositions(AActor* OverlappedActor)
{
	AFootballerChip* OverlappedChip = Cast<AFootballerChip>(OverlappedActor);

	//Position of both footballers
	EFieldPosition PickFootballerPosition = ChipFootballerWidget->Footballer->Data.SelectedFieldPosition;
	EFieldPosition OverlappedFootballerPosition = OverlappedChip->ChipFootballerWidget->Footballer->Data.SelectedFieldPosition;

	//Line Up of both footballers
	EFootballerLineUp PickedFootballerLineUp = ChipFootballerWidget->Footballer->Data.LineUpPosition;
	EFootballerLineUp OverlappedFootballerLineUp = OverlappedChip->ChipFootballerWidget->Footballer->Data.LineUpPosition;

	//if(PickedFootballerLineUp != OverlappedFootballerLineUp)
	//{
	FootballerCurrentTeam->ChangeFootballerLineUp(ChipFootballerWidget->Footballer, OverlappedChip->ChipFootballerWidget->Footballer, OverlappedFootballerLineUp);
	//}

	ChipFootballerWidget->ChangePosition(OverlappedFootballerPosition);
	OverlappedChip->ChipFootballerWidget->ChangePosition(PickFootballerPosition);

	ChipFootballerWidget->CheckDesiredPosition(OverlappedFootballerPosition, ChipFootballerWidget->Footballer);
	OverlappedChip->ChipFootballerWidget->CheckDesiredPosition(PickFootballerPosition, OverlappedChip->ChipFootballerWidget->Footballer);

	UTeamGeneratorFunctionLibrary::SortFootballersByFieldPositions(FootballerCurrentTeam->Starters);

}

bool AFootballerChip::IsUsed() const
{
	return bIsUsed;
}

bool AFootballerChip::IsOnField() const
{
	return bIsOnField;
}

const UChipFootballerWidget* AFootballerChip::GetFootballerWidget() const
{
	return ChipFootballerWidget;
}

UChipFootballerWidget* AFootballerChip::GetFootballerWidget()
{
	return ChipFootballerWidget;
}

const UTeam_Deprecated* AFootballerChip::GetFootballerCurrentTeam() const
{
	return FootballerCurrentTeam;
}

void AFootballerChip::SetIsOnField(bool Value)
{
	bIsOnField = Value;
}
