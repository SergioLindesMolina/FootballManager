// Copyright, 2023, by NGD Studios AB. All rights reserved.


#include "MatchSimulation.h"
#include "MatchGameState.h"
#include "Football/CoreClasses/FootballerObject.h"

// Sets default values
AMatchSimulation::AMatchSimulation()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

void AMatchSimulation::GetAttackerAndDefender(float RandomScore, UPlayingTeam*& Attacker, UPlayingTeam*& Defender) const
{
	if (AMatchGameState* GameState = GetWorld()->GetGameState<AMatchGameState>())
	{
		if (GameState->PlayerAAttack - GameState->PlayerBAttack - RandomScore > 0)
		{
			Attacker = GameState->PlayingTeamA;
			Defender = GameState->PlayingTeamB;
		}
		else
		{
			Attacker = GameState->PlayingTeamB;
			Defender = GameState->PlayingTeamA;
		}
	}
}

TArray<UFootballerObject*> AMatchSimulation::GetAttackingFootballers(const UPlayingTeam* Attacker) const
{
	TArray<UFootballerObject*> Result;

	for (UFootballerObject* Footballer : Attacker->Footballers)
	{
		if (Footballer->Data.SelectedFieldPosition == EFieldPosition::AMC)
		{
			Result.Add(Footballer);
		}
	}

	return Result;
}

TArray<UFootballerObject*> AMatchSimulation::GetDefenseFootballers(const TArray<UFootballerObject*>& AttackingFootballers, const UPlayingTeam* Defender) const
{
	TArray<UFootballerObject*> Result;
	
	for (UFootballerObject* Footballer : Defender->Footballers)
	{
		if (Footballer->Data.SelectedFieldPosition == EFieldPosition::DC)
		{
			Result.Add(Footballer);
		}
	}

	return Result;
}
