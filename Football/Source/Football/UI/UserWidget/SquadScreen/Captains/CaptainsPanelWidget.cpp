// Copyright, 2023, by NGD Studios AB. All rights reserved.


#include "CaptainsPanelWidget.h"
#include "Football/CoreClasses/FootballerObject.h"
#include "Football/Private/Common/Logging.h"

void UCaptainsPanelWidget::UpdateFootballerType(const ECharacterType& InCharacterType, const int32 InPriority)
{
	if (IsValid(Footballer))
	{
		Footballer->Data.CharacterType = InCharacterType;
		Footballer->Data.CharacterTypePriority = InPriority;
	}
}

void UCaptainsPanelWidget::DemoteFootballer()
{
	if (IsValid(Footballer))
	{
		Footballer->Data.CharacterType = ECharacterType::RegularCharacter;
		Footballer->Data.CharacterTypePriority = 0;

		Footballer = nullptr;
		bSelected = false;

		K2_OnFootballerDemoted();
	}
}

void UCaptainsPanelWidget::K2_UpdateFootballer(UFootballerObject* InFootballer)
{
	if (IsValid(InFootballer))
	{
		Footballer = InFootballer;
		bSelected = true;

		UpdateFootballerType(PanelCharacterType, PanelCharacterPriority);

		K2_OnUpdateFootballerInfo(Footballer->Data.Number, Footballer->Data.DisplayName.LastName, Footballer->Data.DesiredFieldPositions);
		K2_OnUpdateFootballerRating(Footballer->Data.Rating.Overall, Footballer->Data.Rating.Stars, Footballer->Data.Rating.Level);
		K2_OnUpdateAffinity(Footballer->Data.TeamDynamics.AffinityWithManager);
		K2_OnUpdateSpecialTrait(Footballer->Data.SpecialTrait, Footballer->Data.SpecialTraitLevel, Footballer->Data.TraitPoints);
		if (Footballer->Data.CharacterType == ECharacterType::CaptainCharacter)
		{
			K2_OnUpdateCaptianStatus(true);
		}
		else
		{
			K2_OnUpdateCaptianStatus(false);
		}

		K2_OnFootballerSelected();
	}
}

int32 UCaptainsPanelWidget::K2_GetFootballerID() const
{
	if (IsValid(Footballer))
	{
		return Footballer->Data.Id;
	}
	else
	{
		return -1;
	}
}

UFootballerObject* UCaptainsPanelWidget::GetFootballer() const
{
	return Footballer;
}
