// Copyright, 2023, by NGD Studios AB. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "EmptyChipWidget.generated.h"

/**
 * Use to set an image of Empty Chip, without footballer data.
 */

class UImage;

UCLASS()
class FOOTBALL_API UEmptyChipWidget : public UUserWidget
{
	GENERATED_BODY()

public:



protected:

	
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UImage* EmptyChipImage;

};
