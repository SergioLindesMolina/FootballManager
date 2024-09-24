// Copyright, 2023, by NGD Studios AB. All rights reserved.


#include "FootballerCard.h"

#include <Football/UI/Slate/FootballerCard/SFootballerCard.h>
#include <Football/CoreClasses/DataStructures/Footballer.h>

#include "FootballerCardSlot.h"
#include "Brushes/SlateImageBrush.h"


UFootballerCard::UFootballerCard()
	: CardBackgroundColor(FColor::FromHex("8D8D8D"))
	, NameBackgroundColor(FColor::FromHex("585858"))
	, NameTextBlockStyle(*LoadObject<USlateWidgetStyleAsset>(nullptr, TEXT("/Game/Football/UI/Styles/FootballerCard/Style_NameTextBlock.Style_NameTextBlock"))->GetStyle<FTextBlockStyle>())
	, Name(INVTEXT("N/A"))
	, BorderBrush(FSlateImageBrush(LoadObject<UTexture2D>(nullptr, TEXT("/Game/Football/UI/Textures/FootballerCard/T_HoverBorder_png.T_HoverBorder_png")), FVector2D(96,84)))
	, PortraitBrush(FSlateImageBrush(LoadObject<UTexture2D>(nullptr, TEXT("/Game/Football/UI/Textures/FootballerCard/T_DefaultFootballer.T_DefaultFootballer")), FVector2D(96,84)))
	, FootLeftBrush(FSlateImageBrush(LoadObject<UTexture2D>(nullptr, TEXT("/Game/Football/UI/Textures/FootballerCard/T_DominantFoot_Left.T_DominantFoot_Left")), FVector2D(31, 31)))
	, FootRightBrush(FSlateImageBrush(LoadObject<UTexture2D>(nullptr, TEXT("/Game/Football/UI/Textures/FootballerCard/T_DominantFootRight.T_DominantFootRight")), FVector2D(31, 31)))
	, FootBothBrush(FSlateImageBrush(LoadObject<UTexture2D>(nullptr, TEXT("/Game/Football/UI/Textures/FootballerCard/T_DominantFootBoth.T_DominantFootBoth")), FVector2D(31, 31)))
	, bFocused(true)
	, bFeetVisible(true)

	, FootballerPositionTextBlockStyle(*LoadObject<USlateWidgetStyleAsset>(nullptr, TEXT("/Game/Football/UI/Styles/FootballerPosition/Style_TextBlock.Style_TextBlock"))->GetStyle<FTextBlockStyle>())
	, FieldPositions({EFieldPosition::GK})
{
}

TSharedRef<SWidget> UFootballerCard::RebuildWidget()
{
	MyButton = SNew(SFootballerCard)
		.OnClicked(BIND_UOBJECT_DELEGATE(FOnClicked, SlateHandleClicked))
		.OnHovered(BIND_UOBJECT_DELEGATE(FSimpleDelegate, SlateHandleHovered))
		.OnUnhovered(BIND_UOBJECT_DELEGATE(FSimpleDelegate, SlateHandleUnhovered))
		.BackgroundColor(CardBackgroundColor)
		.NameBackgroundColor(NameBackgroundColor)
		.BorderBrush(&BorderBrush)
		.PortraitBrush(&PortraitBrush)
		.FootLeftBrush(&FootLeftBrush)
		.FootRightBrush(&FootRightBrush)
		.FootBothBrush(&FootBothBrush)
		.NameTextBlockStyle(&NameTextBlockStyle)
		.Name(Name)
		.FieldPositions(FieldPositions)
		.Foot(EPreferredFootType::Both)
		.bBorderVisible(bFocused)
		.bFeetVisible(bFeetVisible)
		.FootballerPositionTextBlockStyle(&FootballerPositionTextBlockStyle)
		.FieldPositions(FieldPositions)
	;

	if (GetChildrenCount() > 0)
	{
		Cast<UFootballerCardSlot>(GetContentSlot())->BuildSlot(StaticCastSharedPtr<SFootballerCard>(MyButton).ToSharedRef());
	}

	return MyButton.ToSharedRef();
}

void UFootballerCard::SynchronizeProperties()
{
	// Skip UButton::SynchronizeProperties(); 
	UWidget::SynchronizeProperties();

	if(MyButton.IsValid())
	{
		StaticCastSharedPtr<SFootballerCard>(MyButton)->SetBackgroundColor(CardBackgroundColor);
		StaticCastSharedPtr<SFootballerCard>(MyButton)->SetNameBackgroundColor(NameBackgroundColor);
		StaticCastSharedPtr<SFootballerCard>(MyButton)->SetName(Name);
		StaticCastSharedPtr<SFootballerCard>(MyButton)->SetFoot(Feet);
		StaticCastSharedPtr<SFootballerCard>(MyButton)->SetFieldPositions(FieldPositions);
		StaticCastSharedPtr<SFootballerCard>(MyButton)->SetBorderVisible(bFocused);
		StaticCastSharedPtr<SFootballerCard>(MyButton)->SetFeetVisible(bFeetVisible);

		PRAGMA_DISABLE_DEPRECATION_WARNINGS
		MyButton->SetClickMethod(ClickMethod);
		MyButton->SetTouchMethod(TouchMethod);
		MyButton->SetPressMethod(PressMethod);
		PRAGMA_ENABLE_DEPRECATION_WARNINGS
	}
}

void UFootballerCard::PostLoad()
{
	// Skip UButton::PostLoad(); 
	UContentWidget::PostLoad();

	if (GetChildrenCount() > 0)
	{
		if (UPanelSlot* PanelSlot = GetContentSlot())
		{
			UFootballerCardSlot* ButtonSlot = Cast<UFootballerCardSlot>(PanelSlot);
			if (ButtonSlot == NULL)
			{
				ButtonSlot = NewObject<UFootballerCardSlot>(this);
				ButtonSlot->Content = GetContentSlot()->Content;
				ButtonSlot->Content->Slot = ButtonSlot;
				Slots[0] = ButtonSlot;
			}
		}
	}
}

UClass* UFootballerCard::GetSlotClass() const
{
	return UFootballerCardSlot::StaticClass();
}

void UFootballerCard::OnSlotAdded(UPanelSlot* InSlot)
{
	if ( MyButton.IsValid() )
	{
		Cast<UFootballerCardSlot>(InSlot)->BuildSlot(StaticCastSharedPtr<SFootballerCard>(MyButton).ToSharedRef());
	}
}

void UFootballerCard::SetCardBackgroundColor(const FLinearColor& InCardBackgroundColor)
{
	CardBackgroundColor = InCardBackgroundColor;
	StaticCastSharedPtr<SFootballerCard>(MyButton)->SetBackgroundColor(CardBackgroundColor);
}

void UFootballerCard::SetNameBackgroundColor(const FLinearColor& InNameBackgroundColor)
{
	NameBackgroundColor = InNameBackgroundColor;
	StaticCastSharedPtr<SFootballerCard>(MyButton)->SetNameBackgroundColor(NameBackgroundColor);
}

void UFootballerCard::SetCardName(const FText& InName)
{
	StaticCastSharedPtr<SFootballerCard>(MyButton)->SetName(InName);
}

void UFootballerCard::SetFieldPositions(const TArray<EFieldPosition>& InFieldPositions)
{
	FieldPositions = InFieldPositions;
	StaticCastSharedPtr<SFootballerCard>(MyButton)->SetFieldPositions(FieldPositions);
}

void UFootballerCard::SetBorderVisible(const bool bInFocused)
{
	bFocused = bInFocused;
	StaticCastSharedPtr<SFootballerCard>(MyButton)->SetBorderVisible(bFocused);
}

void UFootballerCard::SetFeetVisible(const bool bInFeetVisible)
{
	bFeetVisible = bInFeetVisible;
	StaticCastSharedPtr<SFootballerCard>(MyButton)->SetFeetVisible(bFeetVisible);
}

void UFootballerCard::SetFeet(EPreferredFootType InFeet)
{
	Feet = InFeet;
	StaticCastSharedPtr<SFootballerCard>(MyButton)->SetFoot(InFeet);
}

void UFootballerCard::SetBorderBrush(const FSlateBrush Brush)
{
	BorderBrush = Brush;
}

void UFootballerCard::SetPortraitBrush(const FSlateBrush Brush)
{
	PortraitBrush = Brush;
}
