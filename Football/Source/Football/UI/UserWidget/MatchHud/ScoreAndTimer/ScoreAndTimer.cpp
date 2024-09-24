// Copyright, 2023, by NGD Studios AB. All rights reserved.


#include "ScoreAndTimer.h"

void UScoreAndTimer::UpdateTime(const uint8 Minute, const uint8 Second)
{
	const FString TimerDisplay = FString::Printf(TEXT("%02d:%02d"), Minute, Second);
	K2_OnUpdateTime(FText::FromString(TimerDisplay));
}
