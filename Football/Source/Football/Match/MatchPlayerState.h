// Copyright, 2023, by NGD Studios AB. All rights reserved.

#pragma once

#include <CoreMinimal.h>
#include <GameFramework/PlayerState.h>

#include "MatchDefs.h"
#include "Football/Team/TeamGenerator.h"

#include "MatchPlayerState.generated.h"

/**
 *  Player state for the multiplayer mode
 */
UCLASS()
class FOOTBALL_API AMatchPlayerState : public APlayerState
{
	GENERATED_BODY()
	
protected:
	TArray<UFootballer_Deprecated*> Footballers;
	TArray<UTeam_Deprecated> Teams;
	UTeam_Deprecated* CurrentTeam;
};
