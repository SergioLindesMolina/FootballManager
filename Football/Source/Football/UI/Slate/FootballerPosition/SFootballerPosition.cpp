// Copyright, 2023, by NGD Studios AB. All rights reserved.

#include "SFootballerPosition.h"

#include <Internationalization/StringTableCore.h>

#include <Football/UI/GlobalColorsBFL.h>


void SFootballerPosition::Construct(const FArguments& InArgs)
{
	TextBlockStyle            = InArgs._TextBlockStyle;
	CurrentLightMode          = InArgs._LightMode;
	Padding					  = InArgs._Padding;
	LocalizationStringTable.Reset(InArgs._LocalizationStringTable);
	
	ChildSlot
	[
		SAssignNew(HorizontalBox, SHorizontalBox)
		.Visibility(EVisibility::HitTestInvisible)
	];

	SetFillFlags(InArgs._bFillFlags);
	SetFieldPositions(InArgs._FieldPositions);
}

void SFootballerPosition::SetFieldPositions(const TArray<EFieldPosition>& InFieldPositions) const
{
	if(InFieldPositions.IsEmpty())
	{
		HorizontalBox->AddSlot()
		[
			CreatePosition(EFieldPosition::None)
		];

		return;
	}
	
	SHorizontalBox::FSlot* Slot {};
	
	HorizontalBox->ClearChildren();
	for(const EFieldPosition& Position : InFieldPositions)
	{
		HorizontalBox->AddSlot()
		.Expose(Slot)
		[
			CreatePosition(Position)
		];

		if(!bFillFlags)
		{
			Slot->SetAutoWidth();
		}
	}
}

void SFootballerPosition::SetLightMode(const ELightMode Mode)
{
	CurrentLightMode = Mode;
}

void SFootballerPosition::SetFillFlags(const bool bFill)
{
	bFillFlags = bFill;
}

TSharedRef<SWidget> SFootballerPosition::CreatePosition(const EFieldPosition FieldPosition) const
{
	FString String;
	if(FieldPosition != EFieldPosition::None && ensureAlways(LocalizationStringTable.IsValid()))
	{
		const FString Key    = FString::Printf(TEXT("Footballer.Attributes.FieldPosition.%s"), *UEnum::GetDisplayValueAsText(FieldPosition).ToString());
    	LocalizationStringTable->GetStringTable()->GetSourceString(Key, String);
    	ensureAlways(!String.IsEmpty());	
	}
	
	const FColor FieldColor = UGlobalColorsBFL::GetFootballerPositionColor(FieldPosition);
	
	switch (CurrentLightMode)
	{
		case ELightMode::Light:
			return SNew(SBorder)
			.BorderBackgroundColor(FieldColor)
			.BorderImage(FCoreStyle::Get().GetBrush("WhiteBrush"))
			.Padding(Padding)
			.VAlign(VAlign_Center)
			[
				SNew(STextBlock)
				.TextStyle(TextBlockStyle)
				.Justification(ETextJustify::Center)
				.Text(FText::FromString(String))
			];			
		
		case ELightMode::Dark:
			return SNew(SBorder)
			.BorderBackgroundColor(FLinearColor::Transparent)
			.Padding(Padding)
			.VAlign(VAlign_Center)
			[
				SNew(STextBlock)
				.TextStyle(TextBlockStyle)
				.Justification(ETextJustify::Center)
				.ColorAndOpacity(FieldColor)
				.Text(FText::FromString(String))
			];
	}

	checkNoEntry();
	return SNullWidget::NullWidget;
}
