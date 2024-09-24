// Copyright, 2023, by NGD Studios AB. All rights reserved.


#include "MatchGameMode.h"
#include "MatchGameState.h"
#include "MatchPlayerController.h"

AMatchGameMode::AMatchGameMode(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	GameStateClass = AMatchGameState::StaticClass();
}

void AMatchGameMode::StartMatch()
{
	Super::StartMatch();
	
	FConstPlayerControllerIterator Controllers = GetWorld()->GetPlayerControllerIterator();
//	Cast<AMatchGameState>(GameState)->ServerSimulate(Cast<AMatchPlayerController>(Controllers->Get()), Cast<AMatchPlayerController>((++Controllers)->Get()));
//	Cast<AMatchGameState>(GameState)->ServerSimulate(Cast<AMatchPlayerController>(Controllers->Get()), nullptr);
}
