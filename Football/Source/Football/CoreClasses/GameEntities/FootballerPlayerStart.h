// Copyright, 2023, by NGD Studios AB. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerStart.h"
#include "FootballerPlayerStart.generated.h"

/**
 * 
 */
UCLASS()
class FOOTBALL_API AFootballerPlayerStart : public APlayerStart
{
	GENERATED_BODY()

public:
	AFootballerPlayerStart(const FObjectInitializer& ObjectInitializer);

private:
	#if WITH_EDITORONLY_DATA
	UTexture2D* FootballerEntityTeture;
	#endif
};
