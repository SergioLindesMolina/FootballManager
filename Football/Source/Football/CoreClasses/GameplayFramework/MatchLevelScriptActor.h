// Copyright, 2023, by NGD Studios AB. All rights reserved.

#pragma once

#include <CoreMinimal.h>
#include <Engine/LevelScriptActor.h>

#include "MatchLevelScriptActor.generated.h"

class ALevelSequenceActor;
class ULevelSequence;

UCLASS()
class FOOTBALL_API AMatchLevelScriptActor : public ALevelScriptActor
{
	GENERATED_BODY()

public:
	ALevelSequenceActor* GetHighlightsLevelSequenceActor() const;
	
protected:
	UPROPERTY(BlueprintReadWrite)
	ALevelSequenceActor* HighlightsLevelSequenceActor {};

	UPROPERTY(EditAnywhere)
	TArray<ULevelSequence*> Highlights;
};
