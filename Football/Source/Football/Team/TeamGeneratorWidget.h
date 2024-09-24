// Copyright, 2023, by NGD Studios AB. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Football/Team/TeamGenerator.h"
#include "TeamGeneratorWidget.generated.h"

/**
 * 
 */
UCLASS(abstract)
class FOOTBALL_API UTeamGeneratorWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly);
	FTeamGenerator TeamGenerator;	
};
