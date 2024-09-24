// Copyright, 2023, by NGD Studios AB. All rights reserved.

#pragma once

#include <Engine/DataTable.h>
#include "Football/CoreClasses/DataStructures/Footballer.h"
#include "MatchDefs.generated.h"

constexpr int32 MAX_STARTERS = 11;
constexpr int32 MAX_SUBSTITUTES = 7;

//@todo(jcastro) Remove this. We use FCountryCode and FISO316612
UENUM(BlueprintType)
enum class ECountryCode : uint8
{
	ES,
	US,
	GB,
	BR,

	MAX
};

UENUM(BlueprintType)
enum class ETeamFormation : uint8
{
	Formation3331,
	Formation3331DM,
	Formation343,
	Formation352,
	Formation4213,
	Formation42211Narrow,
	Formation42211Wide,
	Formation4222,
	Formation4231,
	Formation4231DM,
	Formation424,
	Formation4312Narrow,
	Formation4312Wide,
	Formation4321,
	Formation433,
	Formation433NoST,
	Formation433DM,
	Formation433DMWide,
	Formation442,
	Formation442Diamond,
	Formation442DiamondWide,
	Formation451,
	Formation451DM,
	Formation5131,
	Formation523,
	Formation523DM,
	Formation532,
	Formation532NoST,
	Formation541,
	Formation541Diamond,
	MAX UMETA(Hidden)
};


USTRUCT(BlueprintType)
struct FTeamTacticsData : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	ETeamFormation Formation = ETeamFormation::Formation442;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	UTexture2D* FormationImage = nullptr;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	int32 ST = 0;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	int32 AMR = 0;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	int32 AMC = 0;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	int32 AML = 0;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	int32 MR = 0;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	int32 MC = 0;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	int32 ML = 0;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	int32 DM = 0;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	int32 DR = 0;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	int32 DC = 0;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	int32 DL = 0;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	int32 GK = 0;
};

UENUM(BlueprintType)
enum class EWeather : uint8
{
	Sunny,
	Rainy,
	Windy,
	Stormy,
	Cloudy,
	Snowy,
	MAX_COUNT UMETA(Hidden)
};

UENUM(BlueprintType)
enum class EHighlightEvent : uint8
{
	Invalid,
	Goal,
	BallLoss,
	ShotMissed,
	ShotBlocked,
	Foul,
	Assistance,
	YellowCard,
	DoubleYellowCard,
	RedCard,
	Injury,
	Subtitution,
	Corner,
	Penalty,
	FreeKick,
	LongFreeKick,
	Offside,

	MAX_COUNT UMETA(Hidden)
};

struct FMatchHighlight
{
	bool IsHomeTeam = false;
	float Minute = 0;
	EHighlightEvent Type = EHighlightEvent::Invalid;
	FFootballerData PerformingPlayer;
};

struct FPostMatchEffects
{
	float Condition;
	float Morale;
	float Sharpness;

	TMap<EFootballerAttributes, int32> AttributesToIncrease;
};

struct FMatchStats
{
	FString Name;
	int32 Goals = 0;
	float Possession = 0;
	int32 Shots = 0;
	int32 ShotsOnTarget = 0;
	
	int32 Corners = 0;
	int32 Fouls = 0;
	int32 PassesCompleted = 0;
	float ExpectedGoals = 0;

	int32 RedPenaltyCards = 0;
	int32 YellowPenaltyCards = 0;

	// First parameter FFootballerData.Id
	TMap<int32, FPostMatchEffects> PostMatchEffectsByFootballer;
	TMap<int32, int32> PeformanceByFootballer;
	TMap<int32, int32> MinutesByFootballer;

	//Starters of the game
	//TODO Sergio Add the subs if necessary
	TArray<FFootballerData> PlayingFootballers;

};
struct FMatchResult
{
	FMatchStats HomeTeam;
	FMatchStats AwayTeam;
	TArray<FMatchHighlight> Highlights;
	
	float FieldTilt {};
	
	inline static float PreviousManagerXPRnd = 120;	//< Fastest Workaround to milestone 1. Please, change me :)
	float ManagerXPRnd {};
	float ManagerRivalryRnd {};
};

USTRUCT(BlueprintType)
struct FMatchInfo
{
	GENERATED_BODY();

	FDateTime DateAndHour;
	ECountryCode Country;
	FString City;
	EWeather Weather = EWeather::Sunny;
	int32 Attedances = 0;
	int32 Income = 0;
	FMatchResult Results;

	TArray<FMatchHighlight> GetHighlightsByType(EHighlightEvent HighlightEventType, bool IsHomeTeam) const
	{
		TArray<FMatchHighlight> ResultArray;

		for (const FMatchHighlight& MatchHighlight : Results.Highlights)
		{
			if (MatchHighlight.IsHomeTeam == IsHomeTeam && MatchHighlight.Type == HighlightEventType)
			{
				ResultArray.Add(MatchHighlight);
			}
		}

		return ResultArray;
	}

	TMap<int32, int32> GetHighlightsCountMapByType(const TArray<EHighlightEvent>& HighlightEventTypes, bool IsHomeTeam) const
	{
		// First parameter FFootballerData.Id
		TMap<int32, int32> HighlightMapResult;
		TArray<FFootballerData> PlayingFootballers = (IsHomeTeam) ? Results.HomeTeam.PlayingFootballers : Results.AwayTeam.PlayingFootballers;

		for (const FFootballerData &PlayingFootballer : PlayingFootballers)
		{
			HighlightMapResult.Add(PlayingFootballer.Id, 0);
		}

		for (const FMatchHighlight &MatchHighlight : Results.Highlights)
		{
			if (MatchHighlight.IsHomeTeam == IsHomeTeam && HighlightEventTypes.Contains(MatchHighlight.Type))
			{
				int32 CurrentPlayerId = MatchHighlight.PerformingPlayer.Id;
				if (HighlightMapResult.Contains(CurrentPlayerId))
				{
					HighlightMapResult[CurrentPlayerId] += 1;
				}
				else
				{
					HighlightMapResult.Add(CurrentPlayerId, 1);
				}
			}
		}

		return HighlightMapResult;
	}

	TArray<FMatchHighlight> GetHighlightsByFootballerId(int32 FootballerId, bool IsHomeTeam) const
	{
		TArray<FMatchHighlight> ResultArray;

		for (const FMatchHighlight& MatchHighlight : Results.Highlights)
		{
			if (MatchHighlight.IsHomeTeam == IsHomeTeam && MatchHighlight.PerformingPlayer.Id == FootballerId)
			{
				ResultArray.Add(MatchHighlight);
			}
		}

		return ResultArray;
	}
};
