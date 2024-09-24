// Copyright, 2023, by NGD Studios AB. All rights reserved.


#include "FieldZone.h"

#include <Components/WidgetComponent.h>

#include <Football/Manager/ManagerPlayerController.h>
#include <Football/Formation/GridGenerator/GridGenerator.h>
#include <Football/UI/UserWidget/Shared/ChipFootballer/ChipFootballerWidget.h>
#include <Football/Formation/FootballerChip.h>
#include <Football/Team/TeamGenerator.h>


AFieldZone::AFieldZone()
{
	SceneComp = CreateDefaultSubobject<USceneComponent>("Scene Component");
	SceneComp->SetupAttachment(this->RootComponent);

	FieldMesh = CreateDefaultSubobject<UStaticMeshComponent>("FieldMesh");
	FieldMesh->SetupAttachment(SceneComp);
	FieldMesh->SetMaterial(0, OffMaterial);

	FieldZoneWidget = CreateDefaultSubobject<UWidgetComponent>("Widget Component");
	FieldZoneWidget->SetupAttachment(SceneComp);

	RootComponent = SceneComp;
}

void AFieldZone::BeginPlay()
{
	Super::BeginPlay();
	AManagerPlayerController* ManagerPlayerController = GetWorld()->GetFirstPlayerController<AManagerPlayerController>();
	ManagerPlayerController->OnActorDragStart.AddUObject(this, &AFieldZone::ShowFieldZone);
	ManagerPlayerController->OnActorDragEnd.AddUObject(this, &AFieldZone::HideFieldZone);

	FieldZoneWidget->SetWidgetClass(FieldZoneWidgetClass);
	FieldZoneWidget->InitWidget();

}

void AFieldZone::MoveAnimation()
{
	ChipToMove->SetActorLocation(FMath::Lerp(ChipToMove->GetActorLocation(), GridPositionToMove->GetActorLocation(), CurveFloat->GetFloatValue(AnimationCounter)));

	AnimationCounter += GetWorld()->GetDeltaSeconds();

	if(AnimationCounter >= 1)
	{
		GetWorld()->GetTimerManager().ClearTimer(MoveAnimationTimer);
		AnimationCounter = 0;
	}
}

void AFieldZone::SetHightlight(bool Value)
{
	isHighlighted = Value;
	if(isHighlighted)
	{
		FieldMesh->SetMaterial(0, OffMaterial);
	}
	else
	{
		FieldMesh->SetMaterial(0, OnMaterial);
	}
}

void AFieldZone::SetGridGenerator(AGridGenerator* Grid)
{
	GridGenerator = Grid;
}

void AFieldZone::AddChip(AFootballerChip* Chip, UTeam_Deprecated* InTeam)
{
	if(!CheckAddChipToField())
	{
		return;
	}

	if(FootballerChips.Contains(Chip))
	{
		return;
	}

	FootballerChips.Add(Chip);
	Chip->SetIsOnField(true);
	UFootballerObject* Footballer = Chip->GetFootballerWidget()->Footballer;

	//Refresh Rating of footballers and change position
	InTeam->ChangeFootballerPosition(Footballer, FootballerPosition);
	Chip->CurrentFieldZone = this;
	Chip->FootballerCurrentTeam = InTeam;
	Chip->GetFootballerWidget()->ShowWidgetData(Footballer->Data.DesiredFieldPositions, Footballer->Data.Number, Footballer->Data.DisplayName.GetDisplayName().ToString());

	UTeamGeneratorFunctionLibrary::SortFootballersByFieldPositions(Chip->FootballerCurrentTeam->Starters);

	OnRefreshTeamRating.Broadcast();
}

void AFieldZone::RemoveChip(AActor* Actor)
{
	AFootballerChip* Chip = Cast<AFootballerChip>(Actor);

	if(FootballerChips.Contains(Chip))
	{
		Chip->SetIsOnField(false);
		Chip->CurrentFieldZone = nullptr;
		FootballerChips.Remove(Chip);
	}
}

void AFieldZone::RemoveAllChips()
{
	FootballerChips.Empty();
}

bool AFieldZone::CheckAddChipToField()
{
	if(FootballerChips.Num() + 1 > GridIndices.Num())
	{
		return false;
	}
	else
	{
		return true;
	}
}

void AFieldZone::SetFieldZoneVisibility(bool bSetVisible)
{
	FieldMesh->SetVisibility(bSetVisible);
	FieldZoneWidget->SetVisibility(bSetVisible);
}


void AFieldZone::ShowFieldZone(AFootballerChip* Chip)
{
	SetFieldZoneVisibility(true);
}

void AFieldZone::HideFieldZone(AFootballerChip* Chip)
{
	SetFieldZoneVisibility(false);
}

void AFieldZone::ToogleFieldZoneVisibility(AFootballerChip* Chip)
{
	if(FieldMesh->IsVisible())
	{
		HideFieldZone(Chip);
	}
	else
	{
		ShowFieldZone(Chip);
	}
}

int32 AFieldZone::GetNumFootballersOnField()
{
	return FootballerChips.Num();
}

void AFieldZone::SortChips()
{
	int32 LastIndex = GridIndices.Num() - 1;
	int32 MiddleIndex = LastIndex / 2;
	const TArray<AGridActor*> Grid = GridGenerator->GridActors;

	switch(FootballerChips.Num())
	{
		case 1:
			MoveChipToGridActor(FootballerChips[0], Grid[GridIndices[MiddleIndex]]);
			break;
		case 2:
			MoveChipToGridActor(FootballerChips[0], Grid[GridIndices[MiddleIndex - 1]]);
			MoveChipToGridActor(FootballerChips[1], Grid[GridIndices[MiddleIndex + 1]]);
			break;
		case 3:
			MoveChipToGridActor(FootballerChips[0], Grid[GridIndices[MiddleIndex]]);
			MoveChipToGridActor(FootballerChips[1], Grid[GridIndices[0]]);
			MoveChipToGridActor(FootballerChips[2], Grid[GridIndices[LastIndex]]);
			break;
		default:
			break;
	}

}

void AFieldZone::MoveChipToGridActor(AFootballerChip* Chip, AGridActor* GridActor)
{
	if(IsAnimationEnabled)
	{
		ChipToMove = Chip;
		GridPositionToMove = GridActor;
		GetWorld()->GetTimerManager().SetTimer(MoveAnimationTimer, this, &AFieldZone::MoveAnimation, TimerInterval, true);
	}
	else
	{
		Chip->SetActorLocation(GridActor->GetActorLocation());
	}

	Chip->AttachToActor(GridActor, FAttachmentTransformRules::KeepWorldTransform);
	Chip->SetActorHiddenInGame(GridActor->IsHidden());

	Chip->GetFootballerWidget()->CheckDesiredPosition(FootballerPosition, Chip->GetFootballerWidget()->Footballer);
}

