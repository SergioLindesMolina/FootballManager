// Copyright, 2023, by NGD Studios AB. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "StaticsAndHighlights.generated.h"

/**
 * 
 */
UCLASS()
class FOOTBALL_API UStaticsAndHighlights : public UUserWidget
{
	GENERATED_BODY()


public:
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, DisplayName=AddHighlight)
	void K2_AddHighlight(const FString& Time, const FString& LocalHighlight, const FString& RivalHighlight);
};
