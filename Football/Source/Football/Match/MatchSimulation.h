// Copyright, 2023, by NGD Studios AB. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Football/Team/TeamGenerator.h"
#include "MatchSimulation.generated.h"

UCLASS(BlueprintType)
class FOOTBALL_API UPlayingTeam : public UObject
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadOnly)
	TArray<UFootballerObject*> Footballers;
};

UCLASS(Blueprintable)
class FOOTBALL_API AMatchSimulation : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMatchSimulation();

	UFUNCTION(BlueprintCallable)
	virtual void GetAttackerAndDefender(float RandomScore, UPlayingTeam*& Attacker, UPlayingTeam*& Defender) const;

	UFUNCTION(BlueprintCallable)
	virtual TArray<UFootballerObject*> GetAttackingFootballers(const UPlayingTeam* Attacker) const;

	UFUNCTION(BlueprintCallable)
	virtual TArray<UFootballerObject*> GetDefenseFootballers(const TArray<UFootballerObject*>& AttackingFootballers, const UPlayingTeam *Defender) const;

protected:

	TArray<UFootballerObject*> TeamA;
	TArray<UFootballerObject*> TeamB;
};
