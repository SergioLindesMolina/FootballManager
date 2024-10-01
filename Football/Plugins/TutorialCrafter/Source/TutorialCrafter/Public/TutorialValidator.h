// Copyright, 2023, by NGD Studios AB. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "TutorialValidator.generated.h"

/**
 * Base class for the creation of the validators that every TutorialAction can have, the validator only are meant to perform a 
 * single check and return true or false, to decide if a TutorialActions should start
 */
UCLASS(EditInlineNew, DefaultToInstanced, Blueprintable, Abstract)
class TUTORIALCRAFTER_API UTutorialValidator : public UObject
{
	GENERATED_BODY()
	
public:

	UFUNCTION(meta = (WorldContext = "WorldContextObject"), Category= "TutorialCrafter|Validator")
	virtual bool Check(const UObject* WorldContextObject);

};
