// Copyright, 2023, by NGD Studios AB. All rights reserved.

#include "SoccerField.h"

#include <Football/UI/Slate/SoccerField/SSoccerField.h>


void USoccerField::SynchronizeProperties()
{
	Super::SynchronizeProperties();

	if(MySoccerField.IsValid())
	{
		MySoccerField->SetPossessionValues(PossessionValues);
		MySoccerField->SetLatticeAmount(LatticeAmount);
		MySoccerField->SetLatticeSize({static_cast<float>(LatticeSize), static_cast<float>(LatticeSize)});
		MySoccerField->SetDrawShadow(bDrawShadow);
		MySoccerField->SetShadowOffset(ShadowOffset);

		TStaticArray<FLinearColor, 3> SynchronizeValues;
		SynchronizeValues[0] = PossessionColorLeft; 
		SynchronizeValues[1] = PossessionColorMiddle; 
		SynchronizeValues[2] = PossessionColorRight; 
		MySoccerField->SetPossessionColors(SynchronizeValues);

		//MySoccerField->UpdateFieldPositionsList(FieldPositionsList);

		MySoccerField->ClearInteractablePositions();
		for(const EFieldPosition FieldPosition : FieldPositions)
		{
			AddInteractablePosition(FieldPosition);
		}
	}
}

void USoccerField::ReleaseSlateResources(const bool bReleaseChildren)
{
	Super::ReleaseSlateResources(bReleaseChildren);
	MySoccerField.Reset();
}

void USoccerField::ClearInteractablePosition()
{
	MySoccerField->ClearInteractablePositions();
}

void USoccerField::AddInteractablePosition(const EFieldPosition FieldPosition)
{
	FInteractablePositionClicked Event;
	Event.BindUFunction(this, "InteractablePositionClicked");
	
	FInteractablePositionClicked InteractablePositionClicked;
	MySoccerField->AddInteractablePosition(FieldPosition, Event);
}

void USoccerField::InteractablePositionClicked(const EFieldPosition FieldPosition, const bool bSelected)
{
	OnInteractablePositionClicked.Broadcast(FieldPosition, bSelected);
}

void USoccerField::ChangeInteractablePositionsStatus(const EFieldPosition FieldPosition, const bool bSelected)
{
	MySoccerField->ChangeInteractablePositionsStatus(FieldPosition, bSelected);
}

void USoccerField::ChangeAllInteractablePositionsStatus(const bool bSelected)
{
	MySoccerField->ChangeAllInteractablePositionsStatus(bSelected);
}

void USoccerField::SetPossessionValues(const FVector2f& InPossessionValues)
{
	PossessionValues = InPossessionValues;
	MySoccerField->SetPossessionValues(PossessionValues);
}

TSharedRef<SWidget> USoccerField::RebuildWidget()
{
	MySoccerField = SNew(SSoccerField)
		.FieldMaterial(SoccerMaterial)
		//.FieldPositionsList(FieldPositionsList)
		.FieldPositionButtonDefaultStyle(&FieldPositionButtonDefaultStyle)
		.FieldPositionButtonSelectedStyle(&FieldPositionButtonSelectedStyle)
	;
	
	return MySoccerField.ToSharedRef();
}
