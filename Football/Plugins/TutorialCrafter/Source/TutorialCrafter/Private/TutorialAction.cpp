// Copyright, 2023, by NGD Studios AB. All rights reserved.


#include "TutorialAction.h"
#include "TutorialValidator.h"


void UTutorialAction::Do(const UObject* WorldContextObject)
{
	bCompleted = true;
}

void UTutorialAction::Clear(const UObject* WorldContextObject)
{

}

void UTutorialAction::CheckValidators(const UObject* WorldContextObject)
{
	for (UTutorialValidator* Validator : Validators)
	{
		check(IsValid(Validator));

		if (!Validator->Check(WorldContextObject))
		{
			bValidatorsCompleted = false;
			return;
		}
	}

	bValidatorsCompleted = true;
}
