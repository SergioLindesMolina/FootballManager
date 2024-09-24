// Copyright, 2023, by NGD Studios AB. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "TutorialCrafter/Public/TutorialValidator.h"
#include "WidgetsAreNotVisible.generated.h"

USTRUCT(BlueprintType)
struct FWidgetHandler
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UUserWidget> ContainerClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName Name;	
};


/**
 * 
 */
UCLASS()
class FOOTBALL_API UWidgetsAreNotVisible : public UTutorialValidator
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FWidgetHandler> WidgetsToFind;

	bool Check(const UObject* WorldContextObject) override;
};
