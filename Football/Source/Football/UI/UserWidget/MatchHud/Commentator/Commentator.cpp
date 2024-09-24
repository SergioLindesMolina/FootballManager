// Copyright, 2023, by NGD Studios AB. All rights reserved.


#include "Commentator.h"

#include <Common/Logging.h>


void UCommentator::DisplayMessage(const FText& Message)
{
	DisplayMessage(Message, 0);
}

void UCommentator::DisplayMessage(const FText& Message, const float Timeout)
{
	K2_OnDisplayMessage(Message);
	SetVisibility(ESlateVisibility::SelfHitTestInvisible);
	
	if(Timeout > 0)
	{
		if(const float t = GetWorld()->GetTimerManager().GetTimerRemaining(HideTimerHandle); t > 0)
		{
			UE_LOG(LogFootball, Warning, TEXT("The UCommentator::DisplayMessage was invoked again with a timeout greater than zero while a previous timer is still awaiting. The remaining time for the old timer is %f."), t);
		}
	
		GetWorld()->GetTimerManager().SetTimer(HideTimerHandle, [&]()
		{
			UE_LOG(LogFootball, Log, TEXT("UCommentator hidden automatically"));
			SetVisibility(ESlateVisibility::Hidden);
		}, Timeout, false);	
	}
}
