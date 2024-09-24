// Copyright, 2023, by NGD Studios AB. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "FootballerOverview.generated.h"

enum class EK2EFieldPosition : uint8;
enum class ERatingLevel : uint8;

/*
 * Display Footaballer's stats.
 *
 * This class is designed with scalability in mind, hence future usages are expected in other scenarios 
 * where character information needs to be displayed interactively.
 *
 * Examples: Inside a BubblePanel in world coordinates. Inside a 2D panel. And so on...
*/
UCLASS()
class FOOTBALL_API UFootballerOverview : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintImplementableEvent, DisplayName=OnUpdateStats)
	void K2_OnUpdateStats(const FText& DisplayName, EFieldPosition Position, ERatingLevel RatingLevel, float RatingStars, float NumericValue);
};
