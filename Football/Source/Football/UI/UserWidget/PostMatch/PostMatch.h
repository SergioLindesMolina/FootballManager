// Copyright, 2023, by NGD Studios AB. All rights reserved.

#pragma once

#include <CoreMinimal.h>
#include <Blueprint/UserWidget.h>

#include "PostMatch.generated.h"


class UMultiSegmentProgressBar;
class UDualProgressbar;
class UTextBlock;
class USoccerField;
struct FMatchInfo;
class UCompareTableIntegers;
enum class EWeather : uint8;

/**
 * 
 */
UCLASS()
class FOOTBALL_API UPostMatch : public UUserWidget
{
	GENERATED_BODY()

protected:
	void NativeConstruct() override;

	UFUNCTION(BlueprintCallable)
	void ForceLoadFromMathInfo();
	
private:
	void FillFromMatchInfo(const FMatchInfo& MatchInfo);

	
protected:
	//~=================================================================================================================
	// Getters
	//~=================================================================================================================
	
	UFUNCTION(BlueprintImplementableEvent, DisplayName=GetCompareTableGoalsHighlights)
	UCompareTableIntegers* K2_GetCompareTableGoalsHighlights() const;

	UFUNCTION(BlueprintImplementableEvent, DisplayName=GetCompareTableMatchStats)
	UCompareTableIntegers* K2_GetCompareTableMatchStats() const;

	UFUNCTION(BlueprintImplementableEvent, DisplayName=GetDualProgressbarBallPossession)
	UDualProgressbar* K2_GetDualProgressbarBallPossession() const;

	UFUNCTION(BlueprintImplementableEvent, DisplayName=GetHeadCoachExperienceProgressbar)
	UMultiSegmentProgressBar* K2_GetHeadCoachExperienceProgressbar() const;

	UFUNCTION(BlueprintImplementableEvent, DisplayName=GetHeadCoachRivalryProgressbar)
	UMultiSegmentProgressBar* K2_GetHeadCoachRivalryProgressbar() const;
	
	UFUNCTION(BlueprintImplementableEvent, DisplayName=GetSoccerField)
	USoccerField* K2_GetSoccerField() const;

	UFUNCTION(BlueprintImplementableEvent, DisplayName=GetFieldTiltLabel)
	UTextBlock* K2_GetFieldTiltLabel() const;

	UFUNCTION(BlueprintImplementableEvent, DisplayName=GetVictoryResultLabel)
	UTextBlock* K2_GetVictoryResultLabel() const;

	UFUNCTION(BlueprintImplementableEvent, DisplayName=GetGoalsResultLabel)
	UTextBlock* K2_GetGoalsResultLabel() const;
	
protected:
	//~=================================================================================================================
	// Header
	//~=================================================================================================================
	
	UFUNCTION(BlueprintImplementableEvent, DisplayName="OnHeader")
	void K2_OnHeader(const FText& Username1, const FText& Teamname1, const FText& Username2, const FText& Teamname2);

	//~=================================================================================================================
	// Match Info
	//~=================================================================================================================

	UFUNCTION(BlueprintImplementableEvent, DisplayName="OnDateAndHour")
	void K2_OnDateAndHour(const FText& Value);

	UFUNCTION(BlueprintImplementableEvent, DisplayName="OnPlace")
	void K2_OnPlace(const FText& Value);

	UFUNCTION(BlueprintImplementableEvent, DisplayName="OnWeather")
	void K2_OnWeather(const FText& Value, EWeather Weather);

	UFUNCTION(BlueprintImplementableEvent, DisplayName="OnAttendance")
	void K2_OnAttendance(const FText& Value);

	UFUNCTION(BlueprintImplementableEvent, DisplayName="OnIncome")
	void K2_OnIncome(const FText& Value);
};
