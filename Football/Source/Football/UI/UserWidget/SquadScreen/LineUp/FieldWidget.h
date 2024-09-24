// Copyright, 2023, by NGD Studios AB. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "FieldWidget.generated.h"

class UImage;

/**
 * 
 */
UCLASS()
class FOOTBALL_API UFieldWidget : public UUserWidget
{
	GENERATED_BODY()	

public:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UImage* Field;
};
