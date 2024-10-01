// Copyright, 2023, by NGD Studios AB. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "TutorialAction.generated.h"

class UTutorialValidator;

/**
 * Base class used to define every action that a tutorial can make, before starting the action all the TutorialValidators must return true
 */
UCLASS(EditInlineNew, DefaultToInstanced, Blueprintable, Abstract)
class TUTORIALCRAFTER_API UTutorialAction : public UObject
{
	GENERATED_BODY()

public:
	
	UPROPERTY(Transient)
	bool bCompleted = false;

	UPROPERTY(Transient)
	bool bValidatorsCompleted = false;

	UPROPERTY(Transient)
	int32 CurrentValidatorIndex = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Instanced, DuplicateTransient, Category = "TutorialCrafter|Actions")
	TArray<UTutorialValidator*> Validators;

	UFUNCTION(meta = (WorldContext = "WorldContextObject"), BlueprintCallable, Category = "TutorialCrafter|Actions")
	virtual void Do(const UObject* WorldContextObject);
	
	/*
	* In case that the action gets stopped without finishing , 
	* this function will clean all the resources that may have used the action
	* and finish the action
	*/
	UFUNCTION(meta = (WorldContext = "WorldContextObject"), BlueprintCallable, Category = "TutorialCrafter|Actions")
	virtual void Clear(const UObject* WorldContextObject);

	UFUNCTION(meta = (WorldContext = "WorldContextObject"), Category = "TutorialCrafter|Actions")
	void CheckValidators(const UObject* WorldContextObject);

};
