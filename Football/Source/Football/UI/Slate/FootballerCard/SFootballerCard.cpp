// Copyright, 2023, by NGD Studios AB. All rights reserved.

#include "SFootballerCard.h"

#include <Style/DefaultStyle.h>
#include <Football/UI/Slate/FootballerPosition/SFootballerPosition.h>


void SFootballerCard::Construct(const FArguments& InArgs)
{
	SButton::Construct(SButton::FArguments()
		.ButtonStyle(&FFootballDefaultSlateStyleSet::Get().GetWidgetStyle<FButtonStyle>(FFootballDefaultSlateStyleSet::INVISIBLE_BUTTONSTYLE))
		.ContentPadding(0)
		.OnClicked(InArgs._OnClicked)
		.OnHovered(InArgs._OnHovered)
		.OnUnhovered(InArgs._OnUnhovered)
		.Content()
		[
			SNew(SOverlay)
			+SOverlay::Slot()
			[
				SNew(SVerticalBox)
				+SVerticalBox::Slot()
				[
					SNew(SOverlay)
			
					// PORTRAIT IMAGE
					+SOverlay::Slot()
					[
						SAssignNew(BackgroundBorder, SBorder)
						.BorderBackgroundColor(InArgs._BackgroundColor)
						.BorderImage(FCoreStyle::Get().GetBrush("WhiteBrush"))
						.HAlign(HAlign_Center)
						.VAlign(VAlign_Bottom)
						[
							SAssignNew(PortraitImage, SImage)
							.Image(InArgs._PortraitBrush)
							.RenderTransform(FSlateRenderTransform(1, {0, 2}))
						]
					]
			
					// FEET ICON
					+SOverlay::Slot()
					.HAlign(HAlign_Center)
					.VAlign(VAlign_Bottom)
					[
						SAssignNew(FeetImage, SImage)
					]					
				]
			
				// DISPLAY NAME FOOTBALLER
				+SVerticalBox::Slot()
				.AutoHeight()
				[
					SAssignNew(NameBackgroundBorder, SBorder)
					.BorderBackgroundColor(InArgs._NameBackgroundColor)
					.BorderImage(FCoreStyle::Get().GetBrush("WhiteBrush"))
					.Clipping(EWidgetClipping::ClipToBounds)
					.VAlign(VAlign_Center)
					[
						SNew(STextBlock)
						.Margin(2)
						.Text(this, &SFootballerCard::GetFootballerName)
						.TextStyle(InArgs._NameTextBlockStyle)
						.Justification(ETextJustify::Center)
					]	
				]
			
				// FOOTBALLER POSITION
				+SVerticalBox::Slot()
				.AutoHeight()
				[
					SAssignNew(FootballerPosition, SFootballerPosition)
					.TextBlockStyle(InArgs._FootballerPositionTextBlockStyle)
					.FieldPositions(InArgs._FieldPositions)
					.bFillFlags(true)
				]
			]
			+SOverlay::Slot()
			[
				// Custom content
				SAssignNew(CustomContent, SOverlay)
				+SOverlay::Slot()
				.Expose(CustomContentSlot)
				[
					InArgs._Content.Widget
				]
			]
			+SOverlay::Slot()
			[
				SAssignNew(BorderImage, SImage)
				.Image(InArgs._BorderBrush)
				.Visibility(EVisibility::HitTestInvisible)
			]
		]
	);

	FootballerName = InArgs._Name;
	MaxCharacterDisplayName = InArgs._MaxCharacterDisplayName;

	FootLeftBrush  = InArgs._FootLeftBrush;
	FootRightBrush = InArgs._FootRightBrush;
	FootBothBrush  = InArgs._FootBothBrush;
	
	SetFoot(InArgs._Foot);
	SetBorderVisible(InArgs._bBorderVisible);
	SetFeetVisible(InArgs._bFeetVisible);
}

void SFootballerCard::SetContent(TSharedRef<SWidget> InContent)
{
	CustomContentSlot->DetachWidget();
	CustomContentSlot->AttachWidget(InContent);
}

void SFootballerCard::SetContentPadding(TAttribute<FMargin> InContentPadding)
{
	CustomContentSlot->SetPadding(InContentPadding);
}

void SFootballerCard::SetHAlign(const EHorizontalAlignment HAlign)
{
	CustomContentSlot->SetHorizontalAlignment(HAlign);
}

void SFootballerCard::SetVAlign(const EVerticalAlignment VAlign)
{
	CustomContentSlot->SetVerticalAlignment(VAlign);
}

void SFootballerCard::SetName(const FText& Name)
{
	FootballerName = Name;
}

void SFootballerCard::SetFieldPositions(const TArray<EFieldPosition>& InFieldPositions)
{
	FootballerPosition->SetFieldPositions(InFieldPositions);
}

void SFootballerCard::SetBackgroundColor(const FLinearColor& Color)
{
	BackgroundBorder->SetBorderBackgroundColor(Color);	
}

void SFootballerCard::SetNameBackgroundColor(const FLinearColor& Color)
{
	NameBackgroundBorder->SetBorderBackgroundColor(Color);	
}

void SFootballerCard::SetBorderVisible(const bool bVisible)
{
	bBorderVisible = bVisible;
	BorderImage->SetVisibility(bBorderVisible ? EVisibility::HitTestInvisible : EVisibility::Hidden);
}

void SFootballerCard::SetFeetVisible(const bool bVisible)
{
	bFeetVisible = bVisible;
	FeetImage->SetVisibility(bFeetVisible ? EVisibility::HitTestInvisible : EVisibility::Hidden);
}

void SFootballerCard::SetFoot(const EPreferredFootType Foot)
{
	switch (Foot)
	{
		case EPreferredFootType::Left:
			FeetImage->SetImage(FootLeftBrush); break;
		
		case EPreferredFootType::Right:
			FeetImage->SetImage(FootRightBrush); break;
		
		case EPreferredFootType::Both:
			FeetImage->SetImage(FootBothBrush); break;
	}
}

TSharedPtr<SFootballerPosition> SFootballerCard::GetFootballerPosition() const
{
	return FootballerPosition;
}

FText SFootballerCard::GetFootballerName() const
{
	if(FootballerName.ToString().Len() >= MaxCharacterDisplayName)
	{
		FString EllipsesName = FootballerName.ToString().Mid(0, MaxCharacterDisplayName - 3);
		EllipsesName.Append("...");

		return FText::FromString(EllipsesName);
	}
	
	return FootballerName;
}
