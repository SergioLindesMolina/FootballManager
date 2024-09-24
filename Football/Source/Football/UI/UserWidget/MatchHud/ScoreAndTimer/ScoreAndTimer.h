// Copyright, 2023, by NGD Studios AB. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ScoreAndTimer.generated.h"

/**
 * 
 */
UCLASS()
class FOOTBALL_API UScoreAndTimer : public UUserWidget
{
	GENERATED_BODY()

public:
	void UpdateTime(uint8 Minute, uint8 Second);

	UFUNCTION(BlueprintImplementableEvent, DisplayName=AddScoreEntry)
	void K2_AddScoreEntry(bool bLocalTeam, const FText& DisplayName, uint8 Minute);
	
protected:
	UFUNCTION(BlueprintImplementableEvent, DisplayName=OnUpdateTime)
    void K2_OnUpdateTime(const FText& Time);
};
