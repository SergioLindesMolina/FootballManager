// Copyright, 2023, by NGD Studios AB. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Football/Match/MatchDefs.h"
#include "PostMatchSplashScreen.generated.h"

class UPostMatchSplashScreenMVP;
struct FMatchInfo;

/**
 * 
 */
UCLASS()
class FOOTBALL_API UPostMatchSplashScreen : public UUserWidget
{
	GENERATED_BODY()


protected:
	
	UFUNCTION(BlueprintCallable)
	void SetUpSplashScreen();

	UFUNCTION(BlueprintImplementableEvent, DisplayName="OnUpdateHomeTeam")
	void K2_OnUpdateHomeTeam(const FString& Name, int32 Score, const FLinearColor& BackGroundColor, const FLinearColor& ScoreColor);

	UFUNCTION(BlueprintImplementableEvent, DisplayName="OnUpdateAwayTeam")
	void K2_OnUpdateAwayTeam(const FString& Name, int32 Score, const FLinearColor& BackGroundColor, const FLinearColor& ScoreColor);

	void CalculateTeamResaults();

	void SetUpMVP();

	UPROPERTY(BlueprintReadWrite, meta=(ExposeOnSpawn = true))
	FMatchInfo MatchInfo;
	
	UPROPERTY(BlueprintReadWrite)
	TMap<FString, FLinearColor> BackgroundColors;
	UPROPERTY(BlueprintReadWrite)
	TMap<FString, FLinearColor> ScoreColors;

	UPROPERTY(BlueprintReadWrite, meta=(BindWidget))
	UPostMatchSplashScreenMVP* MVP;

};
