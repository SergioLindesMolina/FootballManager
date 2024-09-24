// Copyright, 2023, by NGD Studios AB. All rights reserved.


#include "CaptainsFootballerCard.h"

#include <Football/UI/Slate/CaptainsFootballerCard/SCaptainsFootballerCard.h>
#include <Football/CoreClasses/DataStructures/Footballer.h>

#include "Brushes/SlateImageBrush.h"


UCaptainsFootballerCard::UCaptainsFootballerCard()
{

}

TSharedRef<SWidget> UCaptainsFootballerCard::RebuildWidget()
{
	MyButton = SNew(SCaptainsFootballerCard)
		.OnClicked(BIND_UOBJECT_DELEGATE(FOnClicked, SlateHandleClicked))
		.OnHovered(BIND_UOBJECT_DELEGATE(FSimpleDelegate, SlateHandleHovered))
		.OnUnhovered(BIND_UOBJECT_DELEGATE(FSimpleDelegate, SlateHandleUnhovered))

		.BackgroundColor(CardBackgroundColor)
		.PortraitBrush(&PortraitBrush)
		.BorderBrush(&BorderBrush)
		.AfinityBrush(&AfinityBrush)
		.TeamLeaderBrush(&TeamLeaderBrush)
		.TraitLevelBrush(&TraitLevelBrush)
		.NameTextBlockStyle(&NameTextBlockStyle)
		.AfinityTextBlockStyle(&AfinityTextBlockStyle)
		.SpecialTraitTextBlockStyle(&TeamLeaderTextBlockStyle)
		.TraitLevelTextBlockStyle(&TraitLevelTextBlockStyle)
		.FootballerPositionTextBlockStyle(&FootballerPositionTextBlockStyle)
		.RatingBarSize(RatingSize)
		.CaptainButtonStyle(&TraitButtonStyle)
		.FieldPositions(FieldPositions)
	;

	return MyButton.ToSharedRef();
}

void UCaptainsFootballerCard::SynchronizeProperties()
{
	// Skip UButton::SynchronizeProperties(); 
	UWidget::SynchronizeProperties();

	if(MyButton.IsValid())
	{
		StaticCastSharedPtr<SCaptainsFootballerCard>(MyButton)->SetName(Name);
		StaticCastSharedPtr<SCaptainsFootballerCard>(MyButton)->SetAfinity(Afinity);
		StaticCastSharedPtr<SCaptainsFootballerCard>(MyButton)->SetSpecialTrait(SpecialTrait);
		StaticCastSharedPtr<SCaptainsFootballerCard>(MyButton)->SetTraitLevel(TraitLevel);
		StaticCastSharedPtr<SCaptainsFootballerCard>(MyButton)->SetFieldPositions(FieldPositions);
		StaticCastSharedPtr<SCaptainsFootballerCard>(MyButton)->SetBorderEnable(bIsBorderEnable);


		PRAGMA_DISABLE_DEPRECATION_WARNINGS
		MyButton->SetClickMethod(ClickMethod);
		MyButton->SetTouchMethod(TouchMethod);
		MyButton->SetPressMethod(PressMethod);
		PRAGMA_ENABLE_DEPRECATION_WARNINGS
	}
}

void UCaptainsFootballerCard::SetCardName(const FText& InName)
{
	StaticCastSharedPtr<SCaptainsFootballerCard>(MyButton)->SetName(InName);
}

void UCaptainsFootballerCard::SetAfinity(const FText & InAfinity)
{
	StaticCastSharedPtr<SCaptainsFootballerCard>(MyButton)->SetAfinity(InAfinity);
}

void UCaptainsFootballerCard::SetSpecialTrait(const FText & InSpecialTrait)
{
	StaticCastSharedPtr<SCaptainsFootballerCard>(MyButton)->SetSpecialTrait(InSpecialTrait);
}

void UCaptainsFootballerCard::SetTraitLevel(const FText & InTraitLevel)
{
	StaticCastSharedPtr<SCaptainsFootballerCard>(MyButton)->SetTraitLevel(InTraitLevel);
}

void UCaptainsFootballerCard::SetFieldPositions(const TArray<EFieldPosition>& InFieldPositions)
{
	StaticCastSharedPtr<SCaptainsFootballerCard>(MyButton)->SetFieldPositions(InFieldPositions);
}

void UCaptainsFootballerCard::SetBorderEnable(const bool InBorderEnable)
{
	TakeWidget();
	StaticCastSharedPtr<SCaptainsFootballerCard>(MyButton)->SetBorderEnable(InBorderEnable);
}


