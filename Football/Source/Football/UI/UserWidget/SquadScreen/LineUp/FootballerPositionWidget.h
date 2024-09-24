// Copyright, 2023, by NGD Studios AB. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "FootballerPositionWidget.generated.h"


class UImage;
class UTextBlock;

/**
 * 
 */
UCLASS()
class FOOTBALL_API UFootballerPositionWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UImage* BackgroundPosition;

	
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* FootballerPosition;
};
