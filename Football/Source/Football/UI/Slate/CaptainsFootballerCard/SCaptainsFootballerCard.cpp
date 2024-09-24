// Copyright, 2023, by NGD Studios AB. All rights reserved.

#include "SCaptainsFootballerCard.h"

#include <Style/DefaultStyle.h>
#include "Widgets/Layout/SSpacer.h"
#include "Widgets/Layout/SScaleBox.h"
#include <Football/UI/Slate/FootballerPosition/SFootballerPosition.h>
#include <Football/UI/Slate/RatingBar/SRatingBar.h>


void SCaptainsFootballerCard::Construct(const FArguments& InArgs)
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
				  SNew(SOverlay)
				  +SOverlay::Slot()
				  [
					//First Background
					SAssignNew(PortraitImage, SImage)
					.Image(InArgs._PortraitBrush)
				  ]
				  +SOverlay::Slot()
				  .HAlign(HAlign_Fill)
			      .VAlign(VAlign_Bottom)
				  [
					//VERTICAL BOX CORE
					SNew(SVerticalBox)
					+SVerticalBox::Slot()
					.HAlign(HAlign_Center)
					.VAlign(VAlign_Fill)
				    [
						//NAME VERTICAL BOX
						SAssignNew(NameTextBlock, STextBlock)
						.Text(InArgs._Name)
					    .TextStyle(InArgs._NameTextBlockStyle)
					    .Justification(ETextJustify::Center)
					]
				    +SVerticalBox::Slot()
					[
						//FOOTBALLER POSITION
						SNew(SBox)
						.HeightOverride(13.4)
						[
							SAssignNew(FootballerPosition, SFootballerPosition)
							.TextBlockStyle(InArgs._FootballerPositionTextBlockStyle)
						    .FieldPositions(InArgs._FieldPositions)
						    .Padding(0)
						]
					]
				      +SVerticalBox::Slot()
					  .AutoHeight()
					  .HAlign(HAlign_Center)
					  .VAlign(VAlign_Center)
					  [
						  //RATING BAR	
						  SAssignNew(RatingBar, SRatingBar)
						  .StarsSize(InArgs._RatingBarSize)
						  .TextBlockStyle(InArgs._RatingBarStyle)

					  ]
					  +SVerticalBox::Slot()
					  [
						  //AFINITY OVERLAY
						  SNew(SOverlay)
						  +SOverlay::Slot()
						  [
							  //Afinity Background
							  SAssignNew(AfinityBackground, SImage)
							  .Image(InArgs._AfinityBrush)
						  ]
					  
					      +SOverlay::Slot()
						  .HAlign(HAlign_Center)
						  .VAlign(VAlign_Center)
						  [
							  //Afinity Text
							  SAssignNew(AfinityTextBlock, STextBlock)
							  .Text(InArgs._Name)
							  .TextStyle(InArgs._AfinityTextBlockStyle)
							  .Justification(ETextJustify::Center)
						  ]
					  ]
					  +SVerticalBox::Slot()
					  [
						  //TEAM LEADER OVERLAY
						  SNew(SOverlay)
						  +SOverlay::Slot()
						  [
							  //Team Leader Background
							  SAssignNew(TeamLeaderBackground, SImage)
							  .Image(InArgs._TeamLeaderBrush)
						  ]
					  
					      +SOverlay::Slot()
						  .HAlign(HAlign_Center)
						  .VAlign(VAlign_Fill)
						  [
							//TEAM LEADER AND BUTTON HORIZONTAL BOX
							SNew(SHorizontalBox)
							+SHorizontalBox::Slot()
							.HAlign(HAlign_Center)
							.VAlign(VAlign_Center)
							[
								SAssignNew(SpecialTraitTextBlock, STextBlock)
								.Text(InArgs._Name)
								.TextStyle(InArgs._SpecialTraitTextBlockStyle)
								.Justification(ETextJustify::Left)
							]

						  ]
						  +SOverlay::Slot()
						  .HAlign(HAlign_Right)
						  .VAlign(VAlign_Center)
						  .Padding(0,0,1,0)
						  [
							SAssignNew(ButtonPressed,SButton)
							.ButtonStyle(InArgs._CaptainButtonStyle)
							//.OnClicked(this, &SCaptainsFootballerCard::OnPreviousButtonClicked)
							//.Visibility(this, &SDualButtonScroll::CalculateButtonsVisibility)
						  ]
                        
					  ]
					  +SVerticalBox::Slot()
					  [
						  //ESPECIAL TRAIT LEVEL OVERLAY
						  SNew(SOverlay)
						  +SOverlay::Slot()
						  [
							  //Especial Trait Level Background
							  SAssignNew(TraitLevelBackground, SImage)
							  .Image(InArgs._TraitLevelBrush)
						  ]
					      +SOverlay::Slot()
						  .HAlign(HAlign_Center)
						  .VAlign(VAlign_Center)
						  [
							  SAssignNew(TraitLevelTextBlock, STextBlock)
							  .Text(InArgs._Name)
							  .TextStyle(InArgs._TraitLevelTextBlockStyle)
							  .Justification(ETextJustify::Center)
						  ]
					  ]
				  ]
				  +SOverlay::Slot()
					  [
						  SAssignNew(BorderImage, SImage)
						  .Image(InArgs._BorderBrush)
					  .Visibility(EVisibility::HitTestInvisible)
					  ]
				]
			]
	);
	RatingBar->SetTextVisibility(false);
}

void SCaptainsFootballerCard::SetContent(TSharedRef<SWidget> InContent)
{
	CustomContentSlot->DetachWidget();
	CustomContentSlot->AttachWidget(InContent);
}

void SCaptainsFootballerCard::SetContentPadding(TAttribute<FMargin> InContentPadding)
{
	CustomContentSlot->SetPadding(InContentPadding);
}

void SCaptainsFootballerCard::SetHAlign(const EHorizontalAlignment HAlign)
{
	CustomContentSlot->SetHorizontalAlignment(HAlign);
}

void SCaptainsFootballerCard::SetVAlign(const EVerticalAlignment VAlign)
{
	CustomContentSlot->SetVerticalAlignment(VAlign);
}

void SCaptainsFootballerCard::SetName(const FText& Name)
{
	NameTextBlock->SetText(Name);
}

void SCaptainsFootballerCard::SetAfinity(const FText& Afinity)
{
	AfinityTextBlock->SetText(Afinity);
}

void SCaptainsFootballerCard::SetSpecialTrait(const FText & SpecialTrait)
{
	SpecialTraitTextBlock->SetText(SpecialTrait);
}

void SCaptainsFootballerCard::SetTraitLevel(const FText & TraitLevel)
{
	TraitLevelTextBlock->SetText(TraitLevel);
}

void SCaptainsFootballerCard::SetFieldPositions(const TArray<EFieldPosition>& InFieldPositions)
{
	FootballerPosition->SetFieldPositions(InFieldPositions);
}

void SCaptainsFootballerCard::SetBorderEnable(bool BorderEnable)
{
	BorderImage->SetVisibility(BorderEnable ? EVisibility::HitTestInvisible : EVisibility::Hidden);
}

void SCaptainsFootballerCard::SetBackgroundColor(const FLinearColor& Color)
{
	BackgroundBorder->SetBorderBackgroundColor(Color);	
}

void SCaptainsFootballerCard::SetNameBackgroundColor(const FLinearColor& Color)
{
	NameBackgroundBorder->SetBorderBackgroundColor(Color);	
}


