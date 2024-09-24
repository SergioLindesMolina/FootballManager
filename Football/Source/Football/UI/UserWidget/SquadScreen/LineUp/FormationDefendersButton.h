// Copyright, 2023, by NGD Studios AB. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "FormationDefendersButton.generated.h"


class UButton;
class UTextBlock;

/**
 * 
 */
UCLASS()
class FOOTBALL_API UFormationDefendersButton : public UUserWidget
{
	GENERATED_BODY()

public:
	
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UButton* DefendersNumButton;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* DefendersNumText;

	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	FString DefendersNumString;

	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	int32 DefendersNum;

};
