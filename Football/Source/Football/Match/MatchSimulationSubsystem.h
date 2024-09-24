// Copyright, 2023, by NGD Studios AB. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "Football/CoreClasses/DataStructures/Footballer.h"
#include "MatchSimulationSubsystem.generated.h"

class UTeam_Deprecated;
class UFootballer_Deprecated;

enum class EAgentState
{
	Idle,
	Moving,
	InterceptingPass
};

USTRUCT(BlueprintType)
struct FFootballerAgent 
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly)
	FVector Location {};
	
	//TODO David: Replace with FFootballerData
	TObjectPtr<class UFootballerObject> Footballer;

	FVector Destination {};

	EAgentState State = EAgentState::Idle;
};

USTRUCT(BlueprintType)
struct FBall
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly)
	FVector Location {};

	FVector Velocity {};
};

enum class ELocalOrVisitor { Local, Visitor };

/**
 *  This subsystem will simulate a match by using an agent system
 */
UCLASS()
class FOOTBALL_API UMatchSimulationSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable)
	void SetTeams(UTeam_Deprecated* PlayerTeam, UTeam_Deprecated* OpTeam);

	UFUNCTION(BlueprintCallable)
	void SimulateUpdate(float DeltaTimeSeconds);

	UFUNCTION(BlueprintCallable)
	void GetFootballerAgents(TArray<FFootballerAgent>& Agents, FBall& Ball);

	void Initialize(FSubsystemCollectionBase& Collection) override;

	static const FVector2D PitchField;
	static const FVector2D GoalArea;
	static const FVector2D SmallArea;
	static const FVector2D BigArea;
	static constexpr float PenaltyDistance = 11;
	static constexpr int MaxStarters = 11;

private:
	TArray<FFootballerAgent*> GetFootballersAtPos(TStaticArray<FFootballerAgent, MaxStarters>& Footballers, EFieldPosition FieldPos);

	void ProcessAgent(FFootballerAgent* Agent, TStaticArray<FFootballerAgent, MaxStarters>& LocalFootballers, const TStaticArray<FFootballerAgent, MaxStarters>& OtherFootballers, ELocalOrVisitor Place);

	TObjectPtr<UTeam_Deprecated> LocalTeam;
	TObjectPtr<UTeam_Deprecated> VisitorTeam;

	FBall Ball;
	float Timer = 0;

	TStaticArray<FFootballerAgent, MaxStarters> LocalFootballers;
	TStaticArray<FFootballerAgent, MaxStarters> VisitorsFootballers;
};
