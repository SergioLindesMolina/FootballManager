// Copyright, 2023, by NGD Studios AB. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "Training.h"
#include "Football/Team/TeamGenerator.h"
#include "ManagerGameState.generated.h"

class UFootballerObject;
class UNameByRegionDataAsset;

/**
 * 
 */
UCLASS()
class FOOTBALL_API AManagerGameState : public AGameStateBase
{
	GENERATED_BODY()
	
public:

	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadOnly)
	FTraining CurrentTraining;

	UFUNCTION(Exec)
	void SetMoney(int32 Money);

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	FTeamGenerator ScoutTeamGenerator;

	UPROPERTY(BlueprintReadOnly)
	TArray<TObjectPtr<UFootballerObject>> ScoutDatabase;

	//Last time I checked exporting an int64 to blueprint crashes everything.
	//Maybe it should be changed to FDateTime
	int64 ServerTime;
};
