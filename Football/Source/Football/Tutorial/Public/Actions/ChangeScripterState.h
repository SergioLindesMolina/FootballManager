// Copyright, 2023, by NGD Studios AB. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "TutorialCrafter/Public/TutorialAction.h"
#include "ChangeScripterState.generated.h"


UENUM(BlueprintType)
enum class EScripterState : uint8 
{
	Resume,
	Stop
};

class AScripter;

UCLASS()
class FOOTBALL_API UChangeScripterState : public UTutorialAction
{
	GENERATED_BODY()

public: 

	UPROPERTY(EditAnywhere)
	EScripterState DesiredScripterState;

	UPROPERTY(Transient)
	AScripter* MapScripter;

	void Do(const UObject* WorldContextObject) override;
	
};
