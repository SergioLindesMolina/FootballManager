// Copyright, 2023, by NGD Studios AB. All rights reserved.

#pragma once

#include <CoreMinimal.h>
#include <Engine/DataTable.h>

#include "BlackBoxSimulationConfig.generated.h"

class UDataTable;


USTRUCT(BlueprintType)
struct FPerformanceAttributesWeightsData : public FTableRowBase
{
	GENERATED_BODY();

	//Name 
	//Properties Names

	UPROPERTY(BlueprintReadWrite,EditDefaultsOnly)
	float GK = 0;
	
	UPROPERTY(BlueprintReadWrite,EditDefaultsOnly)
	float DL = 0;
	
	UPROPERTY(BlueprintReadWrite,EditDefaultsOnly)
	float DC = 0;
	
	UPROPERTY(BlueprintReadWrite,EditDefaultsOnly)
	float DR = 0;
	
	UPROPERTY(BlueprintReadWrite,EditDefaultsOnly)
	float DM = 0;
	
	UPROPERTY(BlueprintReadWrite,EditDefaultsOnly)
	float ML = 0;
	
	UPROPERTY(BlueprintReadWrite,EditDefaultsOnly)
	float MC = 0;
	
	UPROPERTY(BlueprintReadWrite,EditDefaultsOnly)
	float MR = 0;
	
	UPROPERTY(BlueprintReadWrite,EditDefaultsOnly)
	float AML = 0;
	
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	float AMC = 0;
	
	UPROPERTY(BlueprintReadWrite,EditDefaultsOnly)
	float AMR = 0;
	
	UPROPERTY(BlueprintReadWrite,EditDefaultsOnly)
	float ST = 0;	
};


/**
 * 
 */
UCLASS(Blueprintable)
class FOOTBALL_API UBlackBoxSimulationConfig : public UObject
{
	GENERATED_BODY()
public:
	UPROPERTY(EditDefaultsOnly, meta = (RequiredAssetDataTags =	"RowStructure=/Script/Football.PerformanceAttributesWeightsData"))
	UDataTable* PerformanceAttributesWeightsTable;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float PossessionOffenseMultiplier = 1.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float PossessionDefenseMultiplier = 1.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float ShotPrecisionMultiplier = 1.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float OpportunityMultiplier = 1.0f;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float GoalkeeperMultiplier = 1.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float ShotRandomFactor = 0.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float PossessionRandomFactor = 0.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float GoalkeeperThreshold = 1.2f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float ConditionNormalFactor = 0.45f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float ConditionFitnessFactor = 0.25f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float ScoreValueWinFactor = 1.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float ScoreValueLossFactor = -1.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float ScoreValueDrawFactor = 0.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float MoraleNormalFactor = 10.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FVector2D MoraleRndFactor = { 1.0f , 3.7f };

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float SharpnessNormalFactor = 0.5f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FVector2D SharpnessRndFactor = { 0.8f , 1.5f };

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int32 MinimumMinutesPlayedToProgress = 45;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float StateMaxValue = 100.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float AttributeMaxValue = 100.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int32 MinAttendance = 12000;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int32 MaxAdditionalAttendance = 38000;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int32 MaxTeamRating = 160;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float TicketPrice = 30.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FIntPoint ValueToIncreaseRandomRange = { 1 , 3 };

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float OneAttributeToIncreseProbability = 0.25f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float TwoAttributeToIncreseProbability = 0.12f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float ThreeAttributeToIncreseHighProbability = 0.03f;

	UFUNCTION(BlueprintImplementableEvent)
	float CalculateGoalkeeperProbability(float GoalkeeperQuality);

	UFUNCTION(BlueprintImplementableEvent)
	float CalculatePostMatchCondition(int32 MinutesPlayed, float FitnessValue);

	UFUNCTION(BlueprintImplementableEvent)
	float CalculatePostMatchMorale(FIntPoint Score, bool IsHome);

	UFUNCTION(BlueprintImplementableEvent)
	float CalculatePostMatchSharpness(int32 MinutesPlayed);

	UFUNCTION(BlueprintImplementableEvent)
	int32 CalculateAttendance(float HomeTeamRating, float AwayTeamRating);

	UFUNCTION(BlueprintImplementableEvent)
	float CalculateIncome(int32 Attendance);
};
