// Copyright, 2023, by NGD Studios AB. All rights reserved.

#include "ChipFootballerWidget.h"

#include <Components/TextBlock.h>
#include <Components/Image.h>

#include <UWidget/PenaltyCard.h>
#include <UWidget/ColoredProgressbar.h>

#include "Football/UI/UserWidget/SquadScreen/LineUp/LineUpWidget.h" 
#include "Football/UI/UWidget/RatingBar/RatingBarWidget.h"
#include <Logging/StructuredLog.h>
#include "Football/CoreClasses/FootballerObject.h"

void UChipFootballerWidget::NativeConstruct()
{
	Super::NativeConstruct();

	UpdateChipRating();
}

void UChipFootballerWidget::ShowWidgetData(const TArray<EFieldPosition>& ChipPositions, const uint8 Number, const FString& DisplayName)
{
	check(FootballerPosition);
	(void)FootballerPosition->TakeWidget();
	
	FootballerPosition->SetFieldPositions(ChipPositions);
	FootballerNumber->SetText(FText::FromString(FString::FromInt(Number)));
	FootballerName->SetText(FText::FromString(DisplayName));

	UpdateState();
}

void UChipFootballerWidget::RefreshData()
{
	UpdateState();
	FootballerNumber->SetText(FText::FromString(FString::FromInt(Footballer->Data.Number)));
	FootballerName->SetText(Footballer->Data.DisplayName.GetDisplayName());
}

void UChipFootballerWidget::UpdateState() 
{
	FFootballerData* Data = &Footballer->Data;

	PenaltyCard->TakeWidget();
	if (Data->State.PenaltyCards[0] == 0 && Data->State.PenaltyCards[1] == 0)
	{
		PenaltyCard->SetVisibility(ESlateVisibility::Hidden);
	}
	else
	{
		PenaltyCard->SetVisibility(ESlateVisibility::Visible);
		PenaltyCard->SetCardsAmount(Data->State.PenaltyCards[0], Data->State.PenaltyCards[1]);
	}

	int32 MoraleState = (int32)(Data->State.Morale / 20);
	switch (MoraleState)
	{
	case 0:
		MoraleIcon->SetBrushFromTexture(LoadObject<UTexture2D>(nullptr, TEXT("/Script/Engine.Texture2D'/Game/Football/UI/Textures/Stateboard/T_Moral_verysad_icon.T_Moral_verysad_icon'")));
		break;
	case 1:
		MoraleIcon->SetBrushFromTexture(LoadObject<UTexture2D>(nullptr, TEXT("/Script/Engine.Texture2D'/Game/Football/UI/Textures/Stateboard/T_Moral_sad_icon.T_Moral_sad_icon'")));
		break;
	case 2:
		MoraleIcon->SetBrushFromTexture(LoadObject<UTexture2D>(nullptr, TEXT("/Script/Engine.Texture2D'/Game/Football/UI/Textures/Stateboard/T_Moral_standard_icon.T_Moral_standard_icon'")));
		break;
	case 3:
		MoraleIcon->SetBrushFromTexture(LoadObject<UTexture2D>(nullptr, TEXT("/Script/Engine.Texture2D'/Game/Football/UI/Textures/Stateboard/T_Moral_happy_icon.T_Moral_happy_icon'")));
		break;
	case 4:
		MoraleIcon->SetBrushFromTexture(LoadObject<UTexture2D>(nullptr, TEXT("/Script/Engine.Texture2D'/Game/Football/UI/Textures/Stateboard/T_Moral_veryhappy_icon.T_Moral_veryhappy_icon'")));
		break;
	}

	//TODO (David): Try to fix this code flow so we don't use take widget
	ConditionBar->TakeWidget();

	ConditionBar->SetFillPercentage(Data->State.Condition / 100.0f);

	switch (Data->State.Injured)
	{
	case 0:
		InjuriesIcon->SetVisibility(ESlateVisibility::Hidden);
		BackgroundInjuriesIcon->SetVisibility(ESlateVisibility::Hidden);
		break;
	case 1:
		InjuriesIcon->SetVisibility(ESlateVisibility::Visible);
		BackgroundInjuriesIcon->SetVisibility(ESlateVisibility::Visible);
		InjuriesIcon->SetBrushTintColor(FSlateColor(FColor::FromHex("FFC700")));
		break;
	case 2:
		InjuriesIcon->SetVisibility(ESlateVisibility::Visible);
		BackgroundInjuriesIcon->SetVisibility(ESlateVisibility::Visible);
		InjuriesIcon->SetBrushTintColor(FSlateColor(FColor::FromHex("FF0000")));
		break;
	}

	if (Data->CharacterType == ECharacterType::CaptainCharacter)
	{
		CaptainIcon->SetVisibility(ESlateVisibility::Visible);
	}
	else
	{
		CaptainIcon->SetVisibility(ESlateVisibility::Hidden);
	}
}

void UChipFootballerWidget::ChangePosition(EFieldPosition InChipPosition)
{
	Footballer->Data.SelectedFieldPosition = InChipPosition;
}

void UChipFootballerWidget::CheckDesiredPosition(const EFieldPosition InChipPosition, const UFootballerObject* InFootballer)
{
	if(InFootballer->Data.LineUpPosition == EFootballerLineUp::Reserve || InFootballer->Data.LineUpPosition == EFootballerLineUp::Substitute)
	{
		ExclamationIcon->SetVisibility(ESlateVisibility::Hidden);
		return;
	}
	for (EFieldPosition Position : InFootballer->Data.DesiredFieldPositions)
	{
		if (InChipPosition == Position)
		{
			ExclamationIcon->SetVisibility(ESlateVisibility::Hidden);
			return;
		}
	}

	ExclamationIcon->SetVisibility(ESlateVisibility::Visible);
}

void UChipFootballerWidget::HideExclamationIcon()
{
	ExclamationIcon->SetVisibility(ESlateVisibility::Hidden);
}

void UChipFootballerWidget::UpdateChipRating()
{
	if(Footballer == NULL)
	{
		UE_LOGFMT(LogTemp, Warning, "No Footballer On Chip assigned");
		return;
	}

	RatingBar->TakeWidget();
	RatingBar->SetCurrentStars(Footballer->Data.Rating.Stars);
	RatingBar->SetNumericValue(Footballer->Data.Rating.Overall);

	RatingBar->UpdateLevel(Footballer->Data.Rating.Level);
}

void UChipFootballerWidget::InitializeDelegate()
{
	if(ensure(IsValid(Footballer)))
	{
		Footballer->OnUpdateRating.AddUniqueDynamic(this, &UChipFootballerWidget::UpdateChipRating);
	}
}

UFootballerObject* UChipFootballerWidget::GetInitialPositionFootballer(const TArray<UFootballerObject*>& Footballers, const EFieldPosition TeamPosition,
																			const EChipFormationStatus ChipFormationStatus) const
{
	switch(ChipFormationStatus)
	{
		case EChipFormationStatus::InitialPosition:
			for(UFootballerObject* FObj : Footballers)
			{
				if(FObj->Data.DesiredFieldPositions[0] == TeamPosition)
				{
					ExclamationIcon->SetVisibility(ESlateVisibility::Hidden);
					return FObj;
				}
			}
			break;
		case EChipFormationStatus::AdjacentPosition:
			for(UFootballerObject* FObj : Footballers)
			{
				for(EFieldPosition Position : FObj->Data.DesiredFieldPositions)
				{
					if(Position == TeamPosition)
					{
						ExclamationIcon->SetVisibility(ESlateVisibility::Hidden);
						Footballer->Data.SelectedFieldPosition = Position;
						return Footballer;
					}
				}
			}
			break;
		case EChipFormationStatus::RandomPosition:
			for(UFootballerObject* FObj : Footballers)
			{
				ExclamationIcon->SetVisibility(ESlateVisibility::Visible);
				Footballer->Data.SelectedFieldPosition = TeamPosition;
				return Footballer;
			}
			break;
		default:
			UE_LOG(LogTemp, Error, TEXT("No Formation Status detected"));
			break;
	}

	return nullptr;
}
