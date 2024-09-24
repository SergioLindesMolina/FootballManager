// Copyright, 2023, by NGD Studios AB. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "TutorialCrafter/Public/TutorialAction.h"
#include "ShowMessage.generated.h"



/**
 * Open the Assistant Coach message with the specified message for the amount of time specified, 
 * in case of the time being 0 the message will remain unless is removed manually
 */
UCLASS()
class FOOTBALL_API UShowMessage : public UTutorialAction
{
	GENERATED_BODY()

public:
	void Do(const UObject* WorldContextObject) override;

private:
	UFUNCTION()
	void HiddeDisplayMessage(const UMatchHudWidget* MatchWidget) const;
	
private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta =(AllowPrivateAccess))
	FText Message;

	/** How much time (seconds) the message remain. A value of zero means until next call. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta =(AllowPrivateAccess))
	float Time = 0;
	
// private:
// 	FTimerHandle DisplayMessageTimerHandle;
};
