// Copyright, 2023, by NGD Studios AB. All rights reserved.


#include "LocalizationBFL.h"

#include <Internationalization/StringTable.h>
#include <Internationalization/StringTableCore.h>

#include <Football/CoreClasses/DataStructures/Footballer.h>


template<typename Enum>
static FText LoadLocalizedText(const FString& Key, const Enum Value)
{
	const UStringTable* MainStringTable = LoadObject<UStringTable>(nullptr, TEXT("/Game/Football/Localization/MainStringTable.MainStringTable"));
	check(MainStringTable);

	FString OutString;

	FStringFormatOrderedArguments Args;
	Args.Add(FText::FromString(StaticEnum<Enum>()->GetNameStringByValue(static_cast<int64>(Value))).ToString());
	MainStringTable->GetStringTable()->GetSourceString(FString::Format(*Key, Args), OutString);

	ensureAlwaysMsgf(!OutString.IsEmpty(), TEXT("LoadLocalizedText yields an empty result.\nKey = '%s'\nEnum Value = '%s'"), *Key, *UEnum::GetValueAsName(Value).ToString());
	
	return FText::FromString(OutString);
}

FText ULocalizationBFL::LoadLocalizedAttribute(const EFootballerAttributes Attributes)
{
	return LoadLocalizedText("Footballer.Attributes.{0}", Attributes);
}

FText ULocalizationBFL::LoadLocalizedRole(const EFootballerRole FootballerRole)
{
	return LoadLocalizedText("Footballer.Role.{0}", FootballerRole);
}

FText ULocalizationBFL::LoadLocalizedSpecialTrait(const ESpecialTrait SpecialTrait)
{
	return LoadLocalizedText("Footballer.SpecialTrait.{0}", SpecialTrait);
}

FText ULocalizationBFL::LoadLocalizedPersonalityType(const EPersonalityType PersonalityType)
{
	return LoadLocalizedText("Footballer.PersonalityType.{0}", PersonalityType);
}

FText ULocalizationBFL::LoadLocalizedWeather(const EWeather Weather)
{
	return LoadLocalizedText("World.Weather.{0}", Weather);
}
