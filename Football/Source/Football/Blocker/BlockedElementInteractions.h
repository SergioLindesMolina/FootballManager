// Copyright, 2023, by NGD Studios AB. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "BlockedElementInteractions.generated.h"


UINTERFACE(MinimalAPI)
class UBlockedElementInteractions : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class FOOTBALL_API IBlockedElementInteractions
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Football | BlockedElementInteractions")
	UButton* GetButton();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Football | BlockedElementInteractions")
	FText GetBlockedWidgetText(const UWidget* WidgetClicked);
};
