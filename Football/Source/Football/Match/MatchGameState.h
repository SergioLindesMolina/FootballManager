// Copyright, 2023, by NGD Studios AB. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "Football/Team/TeamGenerator.h"
#include "Football/Match/MatchDefs.h"

#include "MatchGameState.generated.h"

class AMatchPlayerController;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnOrdinaryTimeBegin, int32, HalfTime);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnOrdinaryTimeEnd, int32, HalfTime);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHalfTimeBegin, int32, HalfTime);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHalfTimeEnd, int32, HalfTime);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnExtraTimeBegin, int32, HalfTime);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnExtraTimeEnd, int32, HalfTime);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnExtraTimeHalfTimeBegin, int32, HalfTime);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnExtraTimeHaltFimeEnd, int32, HalfTime);

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnMatchFinished);

class UPlayingTeam;

UENUM(BlueprintType)
enum class EFootballMatchState : uint8
{
	OrdinaryTime,
	HalfTime,
	ExtraTime,
	ExtraTimeHalfTime,
};

/**
 * Multiplayer Match Game state
 */
UCLASS()
class FOOTBALL_API AMatchGameState : public AGameState
{
	GENERATED_BODY()

public:
	FMatchResult ServerSimulate(AMatchPlayerController* PlayerA, AMatchPlayerController* PlayerB);
	
	//Time of the first two halves. Expressed in minutes.
	UPROPERTY(EditDefaultsOnly)
	float OrdinaryTime;

	//Time for the extra time. Expressed in minutes.
	UPROPERTY(EditDefaultsOnly)
	float ExtraTime;

	UPROPERTY(EditDefaultsOnly)
	float HalfTimeTime;

	UPROPERTY(EditDefaultsOnly)
	float HalfTimeExtraTime;

	UPROPERTY(BlueprintAssignable)
	FOnOrdinaryTimeBegin OnOrdinaryTimeBegin;

	UPROPERTY(BlueprintAssignable)
	FOnOrdinaryTimeEnd OnOrdinaryTimeEnd;

	UPROPERTY(BlueprintAssignable)
	FOnHalfTimeBegin OnHalfTimeBegin;

	UPROPERTY(BlueprintAssignable)
	FOnHalfTimeEnd OnHalfTimeEnd;

	UPROPERTY(BlueprintAssignable)
	FOnExtraTimeBegin OnExtraTimeBegin;

	UPROPERTY(BlueprintAssignable)
	FOnExtraTimeEnd OnExtraTimeEnd;

	UPROPERTY(BlueprintAssignable)
	FOnExtraTimeHalfTimeBegin OnExtraTimeHalfTimeBegin;

	UPROPERTY(BlueprintAssignable)
	FOnExtraTimeHaltFimeEnd OnExtraTimeHalfTimeEnd;

	UPROPERTY(BlueprintAssignable)
	FOnMatchFinished OnMatchFinished;

	float PlayerAAttack;
	float PlayerBAttack;

	UPlayingTeam* PlayingTeamA;
	UPlayingTeam* PlayingTeamB;

protected:
	UPROPERTY(BlueprintReadOnly)
	float CurrentOrdinaryTime;

	UPROPERTY(BlueprintReadOnly)
	float CurrentExtraTime;

	UPROPERTY(BlueprintReadOnly)
	EFootballMatchState FootballMatchState;

private:
	//It will handle all the time events in the game, ordinary time, half time, extra time, etc
	FTimerHandle TimerHandle;

	int32 HalfNumber = 1;

	void OnEndTimer();

	void DoOrdinaryTimeEnd();
	void DoHalfTimeEnd();
	void DoExtraTimeBegin();
	void DoExtraTimeEnd();

	void DoExtraTimeHalfTimeEnd();

	void FinishFootballMatch();

	bool IsTie();
};
