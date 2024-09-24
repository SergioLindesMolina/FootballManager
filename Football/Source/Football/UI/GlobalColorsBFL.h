// Copyright, 2023, by NGD Studios AB. All rights reserved.

#pragma once

#include <CoreMinimal.h>
#include <Kismet/BlueprintFunctionLibrary.h>

#include <array>
#include <Football/CoreClasses/DataStructures/Footballer.h>

#include "GlobalColorsBFL.generated.h"


/**
 * 
 */
UCLASS()
class FOOTBALL_API UGlobalColorsBFL : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	//~=================================================================================================================
	// Global Colors
	//~=================================================================================================================

	UFUNCTION(BlueprintPure, Category="UserInterface|GlobalColors")
	static FColor GetRatingColor(ERatingLevel RatingLevel);
	
	UFUNCTION(BlueprintPure, Category="UserInterface|GlobalColors")
	static FColor GetFootballerPositionColor(EFieldPosition FieldPosition);

private:
	static std::array<FColor, static_cast<size_t>(ERatingLevel::MAX_COUNT)> RatingLevelColors;
	static std::array<FColor, static_cast<size_t>(EFieldPosition::MAX_COUNT)> FieldPositionColors;
};
