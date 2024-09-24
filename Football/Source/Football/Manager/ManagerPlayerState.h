// Copyright, 2023, by NGD Studios AB. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "Football/Team/TeamGenerator.h"
#include "ManagerPlayerState.generated.h"

/**
 * Base class for the player state, manager mode
 */
UCLASS(Blueprintable)
class FOOTBALL_API AManagerPlayerState : public APlayerState
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintReadWrite)
	UTeam_Deprecated* CurrentTeam;

	UPROPERTY(BlueprintReadWrite)
	int32 TotalMoney;

	UFUNCTION(BlueprintCallable, Exec)
	void SetMoney(int32 Money);

	bool TrySpend(int32 MoneyToSpend);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Data Tables || Team Tactics")
	UDataTable* TeamTacticsData;
};
