// Copyright, 2023, by NGD Studios AB. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "TutorialCrafter/Public/TutorialAction.h"
#include "HideMessage.generated.h"

/**
 * Close the Assistant coach message if is open
 */
UCLASS()
class FOOTBALL_API UHideMessage : public UTutorialAction
{
	GENERATED_BODY()

public:

	void Do(const UObject* WorldContextObject) override;
	
};
