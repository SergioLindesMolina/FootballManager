// Copyright, 2023, by NGD Studios AB. All rights reserved.

#pragma once

#include <CoreMinimal.h>

#include "Football/UI/UserWidget/Shared/ChipFootballer/ChipFootballerWidget.h"


class SFootballerPosition;
enum class EFieldPosition : uint8;

/**
 * 
 */ 
class FOOTBALL_API SFootballerCard final : public SButton
{

public: 
	SLATE_BEGIN_ARGS(SFootballerCard)
		: _BackgroundColor(FColor::FromHex("8D8D8D"))
		, _NameBackgroundColor(FColor::FromHex("585858"))

		,_BorderBrush(nullptr)
		,_PortraitBrush(nullptr)
		,_FootLeftBrush(nullptr)
		,_FootRightBrush(nullptr)
		,_FootBothBrush(nullptr)
	
		, _NameTextBlockStyle(LoadObject<USlateWidgetStyleAsset>(nullptr, TEXT("/Game/Football/UI/Styles/FootballerCard/Style_NameTextBlock.Style_NameTextBlock"))->GetStyle<FTextBlockStyle>())

		, _Name(INVTEXT("N/A"))
		, _MaxCharacterDisplayName(10)
		, _Foot(EPreferredFootType::Left)

		, _bBorderVisible(true)
		, _bFeetVisible(true)
	
		, _FootballerPositionTextBlockStyle(LoadObject<USlateWidgetStyleAsset>(nullptr, TEXT("/Game/Football/UI/Styles/FootballerPosition/Style_TextBlock.Style_TextBlock"))->GetStyle<FTextBlockStyle>())
		, _FieldPositions({EFieldPosition::GK})
	{}

	SLATE_DEFAULT_SLOT(FArguments, Content)

	SLATE_ARGUMENT(FLinearColor, BackgroundColor)
	SLATE_ARGUMENT(FLinearColor, NameBackgroundColor)

	SLATE_ARGUMENT(const FSlateBrush*, BorderBrush)
	SLATE_ARGUMENT(const FSlateBrush*, PortraitBrush)
	SLATE_ARGUMENT(const FSlateBrush*, FootLeftBrush)
	SLATE_ARGUMENT(const FSlateBrush*, FootRightBrush)
	SLATE_ARGUMENT(const FSlateBrush*, FootBothBrush)

	SLATE_STYLE_ARGUMENT(FTextBlockStyle, NameTextBlockStyle)

	SLATE_ARGUMENT(FText, Name)
	SLATE_ARGUMENT(int32, MaxCharacterDisplayName)
	SLATE_ARGUMENT(EPreferredFootType, Foot)
	
	SLATE_ARGUMENT(bool, bBorderVisible)
	SLATE_ARGUMENT(bool, bFeetVisible)

	SLATE_EVENT(FOnClicked,      OnClicked)
	SLATE_EVENT(FSimpleDelegate, OnHovered)
	SLATE_EVENT(FSimpleDelegate, OnUnhovered)

	// FOOTBALLER POSITION ARGUMENTS
	SLATE_STYLE_ARGUMENT(FTextBlockStyle, FootballerPositionTextBlockStyle)
	SLATE_ARGUMENT(TArray<EFieldPosition>, FieldPositions)

	
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
	void SetFieldPositions(const TArray<EFieldPosition>& FieldPositions);
	void SetBackgroundColor(const FLinearColor& Color);
	void SetNameBackgroundColor(const FLinearColor& Color);
	void SetBorderVisible(bool bVisible);
	void SetFeetVisible(bool bVisible);
	void SetFoot(EPreferredFootType Foot);
	
	TSharedPtr<SFootballerPosition> GetFootballerPosition() const;

private:
	FText GetFootballerName() const;

	
private:
	TSharedPtr<SBorder> NameBackgroundBorder;
	TSharedPtr<SBorder> BackgroundBorder;
	TSharedPtr<SImage> PortraitImage;
	TSharedPtr<SImage> BorderImage;
	TSharedPtr<SImage> HoverBorderImage;
	TSharedPtr<SImage> FeetImage;

	TSharedPtr<SOverlay> CustomContent;
	SOverlay::FOverlaySlot* CustomContentSlot {};

	TSharedPtr<SFootballerPosition> FootballerPosition;

	FText FootballerName;
	int32 MaxCharacterDisplayName {};
	
	bool bBorderVisible {};
	bool bFeetVisible {};

	const FSlateBrush* FootLeftBrush {};
	const FSlateBrush* FootRightBrush {};
	const FSlateBrush* FootBothBrush {};
};
