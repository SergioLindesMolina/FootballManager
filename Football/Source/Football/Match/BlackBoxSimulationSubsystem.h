// Copyright, 2023, by NGD Studios AB. All rights reserved.

#pragma once

#include <CoreMinimal.h>
#include <Subsystems/GameInstanceSubsystem.h>

#include <Football/CoreClasses/DataStructures/Footballer.h>
#include <Football/Team/TeamGenerator.h>
#include <Football/Match/MatchDefs.h>

#include "BlackBoxSimulationSubsystem.generated.h"

class UBlackBoxSimulationConfig;

enum class EHighlightType : uint8
{
	Invalid,
	BallLoss,
	ShotMissed,
	ShotBlocked,
	Goal,
	Foul,
	RedCard,
	YellowCard,
	Penalty,
	FreeKick,
	Corner,
	Offside,

	MAX,
};


UCLASS()
class FOOTBALL_API UBlackBoxSimulationSubsystem final : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category="BlackBoxSimulation")
	FMatchInfo SimulateMatch(UBlackBoxSimulationConfig* Config, UTeam_Deprecated* HomeTeam, UTeam_Deprecated* AwayTeam);

private:
	//~=================================================================================================================
	// SIMULATE
	//~=================================================================================================================
	
	FVector2D SimulatePossession(const UTeam_Deprecated* HomeTeam, const UTeam_Deprecated* AwayTeam);
	FIntPoint SimulateShotsOnTarget(TArray<FMatchHighlight>& MatchHighlights, const UTeam_Deprecated* HomeTeam, const UTeam_Deprecated* AwayTeam);
	FIntPoint SimulateGoals(TArray<FMatchHighlight>& MatchHighlights, const UTeam_Deprecated* HomeTeam, const UTeam_Deprecated* AwayTeam);
	FIntPoint SimulateOpportunities(TArray<FMatchHighlight>& MatchHighlights, FVector2D TotalPossession, const UTeam_Deprecated* HomeTeam, const UTeam_Deprecated* AwayTeam);

	//~===============================================================================================================>>
	// https://nimblegiant.atlassian.net/browse/FTB1-1474
	float CalculateFieldTilt(const FMatchStats& LocalTeamMatchStats, const UTeam_Deprecated* HomeTeam, const UTeam_Deprecated* AwayTeam);
	FIntPoint CalculateCorners(const UTeam_Deprecated* HomeTeam, const UTeam_Deprecated* RivalTeam, float FieldTilt);
	FIntPoint CalculateFouls(const UTeam_Deprecated* HomeTeam, const UTeam_Deprecated* RivalTeam);
	FIntPoint CalculatePassesCompleted(const UTeam_Deprecated* HomeTeam, const UTeam_Deprecated* RivalTeam);
	FVector2d SimulateExpectedGoals(TArray<FMatchHighlight>& MatchHighlights);
	std::array<FIntPoint, 2> SimulatePenaltyCards(const UTeam_Deprecated* HomeTeam, const UTeam_Deprecated* RivalTeam);
	//~===============================================================================================================>>

	
private:
	//~=================================================================================================================
	// CALCULATE
	//~=================================================================================================================
	
	float CalculateTeamAttributesQuality(const UTeam_Deprecated* Team, const TArray<EFootballerAttributes>& Attributes, float Multiplier, const TArray<EFieldPosition>& IncluedPositions);
	float CalculatePlayerAttributesQuality(const FFootballerData* Footballer, const TArray<EFootballerAttributes>& Attributes, float Multiplier, const TArray<EFieldPosition>& IncluedPositions);
	TMap<int32, FPostMatchEffects> CalculatePostMatchEffects(UTeam_Deprecated* Team, TMap<int32, int32> MinutesByFootballer, FIntPoint Score, bool IsHome);
	TMap<int32, int32> CalculateMinutesByFootballer(const UTeam_Deprecated* Team);
	void CalculateTeamAttributesToIncrease(FMatchStats& HomeTeamStats);
	TMap<EFootballerAttributes, int32> CalculateAttributesToIncrease(FFootballerData FootballerData, TMap<int32, int32> MinutesByFootballer);
	
	
	float CalculateGoalkeeperProbability(float GoalkeeperQuality);
	float CalculatePostMatchCondition(int32 MinutesPlayed, float FitnessValue);
	float CalculatePostMatchMorale(FIntPoint Score, bool IsHome);
	float CalculatePostMatchSharpness(int32 MinutesPlayed);
	int32 CalculateAttendance(float HomeTeamRating, float AwayTeamRating);
	float CalculateIncome(int32 Attendance);


private:
	//~=================================================================================================================
	//  
	//~=================================================================================================================
	
	TArray<EFootballerAttributes> GetAttributesByPassingStyle(const UTeam_Deprecated* Team);
	const FFootballerData* ChooseShootingPlayer(const UTeam_Deprecated* Team);
	void PopulateMatchStats(FMatchStats& HomeStats, FMatchStats& AwayStats, const TArray<FMatchHighlight>* MatchHighlights, const UTeam_Deprecated* HomeTeam, const UTeam_Deprecated* AwayTeam);
	int32 GetNumberOfAttributesToIncrease();

	
private:
	UPROPERTY()
	UBlackBoxSimulationConfig* SimulationConfig;
};
