// Copyright, 2023, by NGD Studios AB. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Commentator.generated.h"

/**
 * 
 */
UCLASS()
class FOOTBALL_API UCommentator : public UUserWidget
{
	GENERATED_BODY()

public:
	void DisplayMessage(const FText& Message);

	UFUNCTION(BlueprintCallable)
	void DisplayMessage(const FText& Message, float Timeout = -1.f);

protected:
	UFUNCTION(BlueprintImplementableEvent, DisplayName=K2_OnDisplayMessage)
	void K2_OnDisplayMessage(const FText& Message);

private:
	FTimerHandle HideTimerHandle; 
};
