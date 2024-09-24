#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"

#include "Training.generated.h"

//NOTE: Maybe a better name for those are stats and not skills?
UENUM(BlueprintType)
enum class ESkillType : uint8
{
	Speed,
	Stamina,
	Strength,
	Tackling,
	Marking,
	Positioning,
	Heading,
	ShortPassing,
	LongPassing,
	Dribbling,
	Shooting,

	Max UMETA(Hidden),
};

USTRUCT(BlueprintType)
struct FTrainingData : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	FText Name;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	FText Description;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	int32 TimeInHours = 0;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	TArray<ESkillType> SkillsToTrain;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	int32 ImprovementBase = 0;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	int32 ImprovementMax = 0;
};

/**
 * Only to pass a trainging row data around in umg
 */
UCLASS(BlueprintType)
class UTrainingHolder : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite)
	FTrainingData Training;
};

USTRUCT(BlueprintType)
struct FTraining
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly)
	FTrainingData TrainingData;
	
	UPROPERTY(BlueprintReadOnly)
	FDateTime TimeTrainingStarted = 0;
	
	UPROPERTY(BlueprintReadOnly)
	bool IsRunning = 0;
};
