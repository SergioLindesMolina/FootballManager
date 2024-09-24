// Copyright, 2023, by NGD Studios AB. All rights reserved.

#pragma once

#include <CoreMinimal.h>

#include "UserInterface/Public/Style/DefaultStyle.h"
#include "Football/UI/UserWidget/Shared/ChipFootballer/ChipFootballerWidget.h"


class SFootballerPosition;
class SRatingBar;

enum class EFieldPosition : uint8;

/**
 * 
 */ 
class FOOTBALL_API SCaptainsFootballerCard final : public SButton
{

public: 
	SLATE_BEGIN_ARGS(SCaptainsFootballerCard)
		: _BackgroundColor(FColor::FromHex("8D8D8D"))
		, _NameBackgroundColor(FColor::FromHex("585858"))

		,_PortraitBrush(nullptr)
		,_BorderBrush(nullptr)
		,_AfinityBrush(nullptr)
		,_TeamLeaderBrush(nullptr)

		, _NameTextBlockStyle(LoadObject<USlateWidgetStyleAsset>(nullptr, TEXT("/Game/Football/UI/Styles/FootballerCard/Style_NameTextBlock.Style_NameTextBlock"))->GetStyle<FTextBlockStyle>())
		, _AfinityTextBlockStyle(LoadObject<USlateWidgetStyleAsset>(nullptr, TEXT("/Game/Football/UI/Styles/FootballerCard/Style_NameTextBlock.Style_NameTextBlock"))->GetStyle<FTextBlockStyle>())
		, _SpecialTraitTextBlockStyle(LoadObject<USlateWidgetStyleAsset>(nullptr, TEXT("/Game/Football/UI/Styles/FootballerCard/Style_NameTextBlock.Style_NameTextBlock"))->GetStyle<FTextBlockStyle>())
		, _TraitLevelTextBlockStyle(LoadObject<USlateWidgetStyleAsset>(nullptr, TEXT("/Game/Football/UI/Styles/FootballerCard/Style_NameTextBlock.Style_NameTextBlock"))->GetStyle<FTextBlockStyle>())

		, _Name(INVTEXT("N/A"))
	
		, _FootballerPositionTextBlockStyle(LoadObject<USlateWidgetStyleAsset>(nullptr, TEXT("/Game/Football/UI/Styles/FootballerPosition/Style_TextBlock.Style_TextBlock"))->GetStyle<FTextBlockStyle>())
		, _FieldPositions({EFieldPosition::GK})

		, _CaptainButtonStyle(&FCoreStyle::Get().GetWidgetStyle<FButtonStyle>("Button"))

		, _RatingBarStyle(LoadObject<USlateWidgetStyleAsset>(nullptr, TEXT("/Game/Football/UI/Styles/FootballerPosition/Style_TextBlock.Style_TextBlock"))->GetStyle<FTextBlockStyle>())
	{}

	SLATE_DEFAULT_SLOT(FArguments, Content)

	SLATE_ARGUMENT(FLinearColor, BackgroundColor)
	SLATE_ARGUMENT(FLinearColor, NameBackgroundColor)

	SLATE_ARGUMENT(const FSlateBrush*, PortraitBrush)
	SLATE_ARGUMENT(const FSlateBrush*, BorderBrush)
	SLATE_ARGUMENT(const FSlateBrush*, AfinityBrush)
	SLATE_ARGUMENT(const FSlateBrush*, TeamLeaderBrush)
	SLATE_ARGUMENT(const FSlateBrush*, TraitLevelBrush)

	SLATE_STYLE_ARGUMENT(FTextBlockStyle, NameTextBlockStyle)
	SLATE_STYLE_ARGUMENT(FTextBlockStyle, AfinityTextBlockStyle)
	SLATE_STYLE_ARGUMENT(FTextBlockStyle, SpecialTraitTextBlockStyle)
	SLATE_STYLE_ARGUMENT(FTextBlockStyle, TraitLevelTextBlockStyle)

	SLATE_ARGUMENT(FText, Name)

	SLATE_EVENT(FOnClicked,      OnClicked)
	SLATE_EVENT(FSimpleDelegate, OnHovered)
	SLATE_EVENT(FSimpleDelegate, OnUnhovered)

	// FOOTBALLER POSITION ARGUMENTS
	SLATE_STYLE_ARGUMENT(FTextBlockStyle, FootballerPositionTextBlockStyle)
	SLATE_ARGUMENT(TArray<EFieldPosition>, FieldPositions)

	SLATE_STYLE_ARGUMENT(FButtonStyle, CaptainButtonStyle)

	//RATING BAR ARGUMENTS
	SLATE_ARGUMENT(FVector2D, RatingBarSize)
	SLATE_STYLE_ARGUMENT(FTextBlockStyle, RatingBarStyle)


	SLATE_END_ARGS()

public:
	void Construct(const FArguments& InArgs);
	void SetContent(TSharedRef<SWidget> InContent) override;

public:
	//FORCE SHADOWING METHOD
	void SetContentPadding(TAttribute<FMargin> InContentPadding);
	void SetHAlign(EHorizontalAlignment HAlign);
	void SetVAlign(EVerticalAlignment VAlign);
	
public:
	void SetName(const FText& Name);
	void SetAfinity(const FText& Afinity);
	void SetSpecialTrait(const FText& SpecialTrait);
	void SetTraitLevel(const FText& TraitLevel);
	void SetFieldPositions(const TArray<EFieldPosition>& FieldPositions);
	void SetBorderEnable(bool BorderEnable);


	void SetBackgroundColor(const FLinearColor& Color);
	void SetNameBackgroundColor(const FLinearColor& Color);
	
private:
	TSharedPtr<STextBlock> NameTextBlock;
	TSharedPtr<STextBlock> AfinityTextBlock;
	TSharedPtr<STextBlock> SpecialTraitTextBlock;
	TSharedPtr<STextBlock> TraitLevelTextBlock;
	TSharedPtr<SBorder> NameBackgroundBorder;
	TSharedPtr<SBorder> BackgroundBorder;
	TSharedPtr<SImage> PortraitImage;
	TSharedPtr<SImage> BorderImage;
	TSharedPtr<SImage> AfinityBackground;
	TSharedPtr<SImage> TeamLeaderBackground;
	TSharedPtr<SImage> TraitLevelBackground;
	TSharedPtr<SImage> HoverBorderImage;


	TSharedPtr<SButton> ButtonPressed;

	TSharedPtr<SFootballerPosition> FootballerPosition;

	TSharedPtr<SRatingBar> RatingBar;

	TSharedPtr<SOverlay> CustomContent;
	SOverlay::FOverlaySlot* CustomContentSlot {};
};
