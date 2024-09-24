// Copyright, 2023, by NGD Studios AB. All rights reserved.

#pragma once

#include <CoreMinimal.h>
#include <Kismet/BlueprintFunctionLibrary.h>

#include "LocalizationBFL.generated.h"

enum class EFootballerAttributes : uint8;
enum class EFootballerRole : uint8;
enum class ESpecialTrait : uint8;
enum class EPersonalityType : uint8;
enum class EWeather : uint8;

UCLASS()
class FOOTBALL_API ULocalizationBFL : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintPure, Category="UserInterface|Localization")
	static FText LoadLocalizedAttribute(EFootballerAttributes Attributes);

	UFUNCTION(BlueprintPure, Category="UserInterface|Localization")
	static FText LoadLocalizedRole(EFootballerRole FootballerRole);
	
	UFUNCTION(BlueprintPure, Category="UserInterface|Localization")
	static FText LoadLocalizedSpecialTrait(ESpecialTrait SpecialTrait);
	
	UFUNCTION(BlueprintPure, Category="UserInterface|Localization")
	static FText LoadLocalizedPersonalityType(EPersonalityType PersonalityType);

	UFUNCTION(BlueprintPure, Category="UserInterface|Localization")
	static FText LoadLocalizedWeather(EWeather Weather);
	
};
