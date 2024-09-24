// Copyright, 2023, by NGD Studios AB. All rights reserved.

#pragma once

#include <CoreMinimal.h>

#include <UserInterface/Public/UWidget/DualButtonScroll.h>
#include <Football/UI/Slate/FootballerCard/SFootballerCard.h>
#include <Interfaces/IButtonContainerBase.h>
#include <Slate/DualButtonScroll/SDualButtonScroll.h>

#include "Football/UI/UWidget/FootballerCard/FootballerCard.h"
#include "Style/DefaultStyle.h"
#include "DBSBFootballerCard.generated.h"


/**
 * Specialization of UDualButtonScroll to display "FootballerCard"
 */
UCLASS(meta=(DisplayName="DualButtonScrollBox (Custom FootballerCard)"))
class FOOTBALL_API UDBSBFootballerCard : public UDualButtonScroll
{
	GENERATED_BODY()

	explicit UDBSBFootballerCard()
	{
		Orientation = Orient_Horizontal;
		bAutoHighlightStartIndex = true;
	}

	void OnPopulateElements() override
	{
		FootballerCards.Empty(TextValues.Num() * 2);
		
		static FFootballerData DummyData;
		DummyData.DisplayName = FFootballerData::FFootballerName(INVTEXT("Pepito"), INVTEXT("Salas"));
		DummyData.DesiredFieldPositions = { EFieldPosition::GK, EFieldPosition::DC };
		
		TArray<FFootballerData*> FootballersData;

		FootballersData.Empty(TextValues.Num());
		for(int32 i = 0; i < TextValues.Num(); i++)
		{
			FootballersData.Add(&DummyData);
		}
		
		FillFootballersData(FootballersData);
	}

public:
	void FillFootballersData(const TArray<FFootballerData*>& FootballersData)
	{
		FootballerCards.Empty(TextValues.Num() * 2);
		
		if(MyDualButtonScroll.IsValid())
		{
			MyDualButtonScroll->ClearButtonChildren();
			for(int32 i = 0; i < FootballersData.Num(); i++)
			{
				MyDualButtonScroll->AddChild([&]() -> IButtonBaseContainer::FButtonsPair
				{
					return
					{
						CreateDefaultButton(*FootballersData[i], i),
						CreateSelectedButton(*FootballersData[i], i)			
					};
				});
			}
		}	
	}

private:
	TSharedRef<SButton> CreateDefaultButton(const FFootballerData& FootballerData, int32 Index)
	{
		FootballerCards.Add(NewObject<UFootballerCard>(this));
			
		const TSharedPtr<SFootballerCard> FootballerCard
		= StaticCastSharedRef<SFootballerCard>(FootballerCards.Last()->TakeWidget());

		check(FootballerCard.IsValid());
		FootballerCard->SetName(FootballerData.DisplayName.GetDisplayName());
		FootballerCard->SetFieldPositions(FootballerData.DesiredFieldPositions);
		FootballerCard->SetBorderVisible(false);
		FootballerCard->SetFeetVisible(false);
		FootballerCard->SetVisibility(EVisibility::HitTestInvisible);
			
		return SNew(SButton)
		.ButtonStyle(&FFootballDefaultSlateStyleSet::Get().GetWidgetStyle<FButtonStyle>(FFootballDefaultSlateStyleSet::INVISIBLE_BUTTONSTYLE))
		.Content()
		[
			SNew(SBox)
			.MaxDesiredWidth(100)
			[
				FootballerCard.ToSharedRef()
			]
		];
	}

	TSharedRef<SButton> CreateSelectedButton(const FFootballerData& FootballerData, int32 Index)
	{
		FootballerCards.Add(NewObject<UFootballerCard>(this));
			
		const TSharedPtr<SFootballerCard> FootballerCard
		= StaticCastSharedRef<SFootballerCard>(FootballerCards.Last()->TakeWidget());

		check(FootballerCard.IsValid());
		FootballerCard->SetName(FootballerData.DisplayName.GetDisplayName());
		FootballerCard->SetFieldPositions(FootballerData.DesiredFieldPositions);
		FootballerCard->SetBorderVisible(true);
		FootballerCard->SetFeetVisible(false);
		FootballerCard->SetVisibility(EVisibility::HitTestInvisible);

		return SNew(SButton)
		.ButtonStyle(&FFootballDefaultSlateStyleSet::Get().GetWidgetStyle<FButtonStyle>(FFootballDefaultSlateStyleSet::INVISIBLE_BUTTONSTYLE))
		.Content()
		[
			SNew(SBox)
			.MaxDesiredWidth(100)
			[
				FootballerCard.ToSharedRef()
			]
		];
	}	

private:
	UPROPERTY(Transient)
	TArray<UFootballerCard*> FootballerCards;
};
