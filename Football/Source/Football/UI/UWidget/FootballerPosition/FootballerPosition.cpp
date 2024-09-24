// Copyright, 2023, by NGD Studios AB. All rights reserved.


#include "FootballerPosition.h"

#include <Internationalization/StringTable.h>


#include "Football/UI/Slate/FootballerPosition/SFootballerPosition.h"


UFootballerPosition::UFootballerPosition()
	: TextBlockStyle(*LoadObject<USlateWidgetStyleAsset>(nullptr, TEXT("/Game/Football/UI/Styles/FootballerPosition/Style_TextBlock.Style_TextBlock"))->GetStyle<FTextBlockStyle>())
	, FieldPositions({EFieldPosition::GK})
	, LocalizationString(LoadObject<UStringTable>(nullptr, TEXT("/Game/Football/Localization/MainStringTable.MainStringTable")))
{
}

TSharedRef<SWidget> UFootballerPosition::RebuildWidget()
{
	MyFootballerPosition = SNew(SFootballerPosition)
		.FieldPositions(FieldPositions)
		.TextBlockStyle(&TextBlockStyle)
		.LocalizationStringTable(LocalizationString)
		.LightMode(bDarkMode ? SFootballerPosition::ELightMode::Dark : SFootballerPosition::ELightMode::Light)
		.bFillFlags(bFillFlags)
		.Padding(Padding)
	;

	return MyFootballerPosition.ToSharedRef();
}

void UFootballerPosition::ReleaseSlateResources(const bool bReleaseChildren)
{
	Super::ReleaseSlateResources(bReleaseChildren);
	MyFootballerPosition.Reset();
}

void UFootballerPosition::SynchronizeProperties()
{
	Super::SynchronizeProperties();

	if(MyFootballerPosition.IsValid())
	{
		MyFootballerPosition->SetFieldPositions(FieldPositions);
	}
}

void UFootballerPosition::SetFieldPositions(const TArray<EFieldPosition>& InFieldPositions)
{
	FieldPositions = InFieldPositions;

	if (MyFootballerPosition.IsValid())
	{
		MyFootballerPosition->SetFieldPositions(FieldPositions);
	}
}

void UFootballerPosition::SetFillFlags(const bool bFill)
{
	bFillFlags = bFill;
	MyFootballerPosition->SetFillFlags(bFillFlags);
}
