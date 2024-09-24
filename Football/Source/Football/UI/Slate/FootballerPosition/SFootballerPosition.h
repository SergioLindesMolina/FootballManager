// Copyright, 2023, by NGD Studios AB. All rights reserved.

#pragma once

#include <CoreMinimal.h>
#include <Football/CoreClasses/DataStructures/Footballer.h>

#include <UserInterface/Public/Style/DefaultStyle.h>
#include <Internationalization/StringTable.h>


/**
 * 
 */ 
class FOOTBALL_API SFootballerPosition final : public SCompoundWidget
{
public:
	enum class ELightMode
	{
		Light,
		Dark
	};
	
public: 
	SLATE_BEGIN_ARGS(SFootballerPosition)
		: _FieldPositions({EFieldPosition::GK})
		, _LocalizationStringTable(LoadObject<UStringTable>(nullptr, TEXT("/Game/Football/Localization/MainStringTable.MainStringTable")))
		, _LightMode(ELightMode::Light)
		, _bFillFlags(true)
		, _Padding(5)
		, _TextBlockStyle(&FFootballDefaultSlateStyleSet::Get().GetWidgetStyle<FTextBlockStyle>(FFootballDefaultSlateStyleSet::NORMAL_TEXTBLOCKSTYLE))
	{}
	
	SLATE_ARGUMENT(TArray<EFieldPosition>, FieldPositions)
	SLATE_ARGUMENT(UStringTable*, LocalizationStringTable)
	SLATE_ARGUMENT(ELightMode, LightMode)
	SLATE_ARGUMENT(bool, bFillFlags)
	SLATE_ARGUMENT(float, Padding)
	
	
	SLATE_STYLE_ARGUMENT(FTextBlockStyle, TextBlockStyle)
	
	SLATE_END_ARGS()

public:
	void Construct(const FArguments& InArgs);
	void SetFieldPositions(const TArray<EFieldPosition>& FieldPositions) const;
	void SetLightMode(ELightMode Mode);
	void SetFillFlags(bool bFill);
	
	
private:
	TSharedRef<SWidget> CreatePosition(EFieldPosition FieldPosition) const;

	
private:
	TSharedPtr<SHorizontalBox> HorizontalBox;

	const FTextBlockStyle* TextBlockStyle {};

	TStrongObjectPtr<UStringTable> LocalizationStringTable {};
	ELightMode CurrentLightMode = ELightMode::Light;
	bool bFillFlags {};
	float Padding {};
};
