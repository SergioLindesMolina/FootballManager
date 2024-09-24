// Copyright, 2023, by NGD Studios AB. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CoachesViewports.generated.h"

/**
 * 
 */
UCLASS()
class FOOTBALL_API UCoachesViewports : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, DisplayName=SetLocalViewportVisibility)
	void K2_SetLocalViewportVisibility(bool bVisible);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, DisplayName=SetRivanViewportVisibility)
	void K2_SetRivalViewportVisibility(bool bVisible);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, DisplayName=PlayLocalHeadCoachReactions)
	void K2_PlayLocalHeadCoachReactions(int32 Index);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, DisplayName=PlayRivalHeadCoachReactions)
	void K2_PlayRivalHeadCoachReactions(int32 Index);
};
