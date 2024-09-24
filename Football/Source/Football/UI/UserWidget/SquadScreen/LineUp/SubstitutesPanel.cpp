// Copyright, 2023, by NGD Studios AB. All rights reserved.


#include "SubstitutesPanel.h"

#include <Football/UI/UserWidget/Shared/ChipFootballer/ChipFootballerWidget.h>
#include <Football/Formation/GridGenerator/GridGenerator.h>
#include <Football/Formation/FootballerChip.h>
#include "Football/CoreClasses/FootballerObject.h"

void ASubstitutesPanel::SetSubstitutes(TArray<UFootballerObject*> Footballers, UTeam_Deprecated* InTeam)
{
	if (AllGridActors.IsEmpty())
	{
		for (AGridGenerator* Grid : GridGenerators)
		{
			Grid->InitGrid();
			AllGridActors.Append(Grid->GridActors);
		}
	}

	int32 IndexOfSubChips = 0;
	if (ChipsToSave.IsEmpty()) 
	{
		for (UFootballerObject* Footballer : Footballers)
		{
			if (AllGridActors.Num() > IndexOfSubChips)
			{
				CreateChip(Footballer, InTeam, AllGridActors[IndexOfSubChips]);
				++IndexOfSubChips;
			}
		}
	}
	else 
	{
		for(const UFootballerObject* Footballer : Footballers)
		{
			if (AllGridActors.Num() > IndexOfSubChips)
			{
				FVector ChipLocation = AllGridActors[IndexOfSubChips]->GetActorLocation();
				ChipsToSave[IndexOfSubChips]->SetActorLocation(ChipLocation);
				ChipsToSave[IndexOfSubChips]->GetFootballerWidget()->ShowWidgetData(Footballer->Data.DesiredFieldPositions, Footballer->Data.Number, Footballer->Data.DisplayName.GetDisplayName().ToString());
				ChipsToSave[IndexOfSubChips]->GetFootballerWidget()->HideExclamationIcon();
				ChipsToSave[IndexOfSubChips]->AttachToActor(AllGridActors[IndexOfSubChips], FAttachmentTransformRules::KeepWorldTransform);
				ChipsToSave[IndexOfSubChips]->SetActorHiddenInGame(AllGridActors[IndexOfSubChips]->IsHidden());
				ChipsToSave[IndexOfSubChips]->SetIsOnField(false);
				ChipsToSave[IndexOfSubChips]->CurrentFieldZone = nullptr;
				++IndexOfSubChips;
			}
		}
	}
}

UChipFootballerWidget* ASubstitutesPanel::CreateChip(UFootballerObject* Footballer, UTeam_Deprecated* InTeam, AGridActor* GridActor)
{
	FActorSpawnParameters ChipSpawnParameters;
	ChipSpawnParameters.Owner = this;
	AFootballerChip* Chip = GetWorld()->SpawnActor<AFootballerChip>(FootballerChipSubclass, GridActor->GetActorLocation() , FRotator::ZeroRotator, ChipSpawnParameters);
	Chip->AttachToActor(GridActor,FAttachmentTransformRules::KeepWorldTransform);
	Chip->SetActorHiddenInGame(GridActor->IsHidden());

	Chip->SetIsOnField(false);
	ChipsToSave.Add(Chip);
	Chip->SetChipWidget();
	Chip->CurrentFieldZone = nullptr;

	UChipFootballerWidget* FootballerWidget = Chip->GetFootballerWidget();
	FootballerWidget->Footballer = Footballer;
	FootballerWidget->InitializeDelegate();
	Chip->FootballerCurrentTeam = InTeam;
	FootballerWidget->ShowWidgetData(Footballer->Data.DesiredFieldPositions, Footballer->Data.Number, Footballer->Data.DisplayName.GetDisplayName().ToString());

	return FootballerWidget;
}
