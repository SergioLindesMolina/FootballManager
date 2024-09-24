// Copyright, 2023, by NGD Studios AB. All rights reserved.

#pragma once

#include <CoreMinimal.h>
#include <Blueprint/UserWidget.h>

#include "FootballerProfile.generated.h"

enum class ERatingLevel : uint8;
enum class EFieldPosition : uint8;
enum class EPreferredFootType : uint8;
enum class EPersonalityType : uint8;
enum class ECharacterType : uint8;

class UTeam_Deprecated;
class UFootballerObject;
struct FFootballerData;
struct FISO316612;

/**
 * @todo(jcastro)
 * It's highly likely that this data should have its own slate.
 * There's also a high probability that we'll use this in more locations. 
 * For now, it's defined here temporarily.
 */
USTRUCT(BlueprintType, DisplayName=AwardValue)
struct FAwardValue_Blueprint
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FText Name {};

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32 YearBegin {};

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32 YearEnd {};
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UTexture2D* Icon {};
};

/**
 * Event called when UFootballerProfile is closed
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FFootballerProfileClosed);


/*
 *
*/
UCLASS()
class FOOTBALL_API UFootballerProfile : public UUserWidget
{
	GENERATED_BODY()

public:
	//~=================================================================================================================
	// Setup
	//~=================================================================================================================
	
	void SetupFootballerProfile(const UTeam_Deprecated* Team);

public:
	//~=================================================================================================================
	// Display
	//~=================================================================================================================
	
	UFUNCTION(BlueprintCallable)
	void LoadDebug();

	UFUNCTION(BlueprintCallable, DisplayName="FootballerProfileDisplayWidget", meta = (WorldContext="WorldContextObject"))
	static UFootballerProfile* DisplayWidget(const UObject* WorldContextObject, const UTeam_Deprecated* Team, UFootballerObject* Footballer);


protected:
	//~=================================================================================================================
	// Populate Profile
	//~=================================================================================================================
	
	void PopulateFootballerFromIndex(int32 FootballersCardScrollBoxIndex);
	
	void PopulateFootballerFromData(FFootballerData& FootballerData, const FText& TeamName);

protected:
	//~=================================================================================================================
	// Global
	//~=================================================================================================================
	
	UFUNCTION(BlueprintImplementableEvent, DisplayName="OnUpdateNotes")
	void K2_OnUpdateNotes(const FText& Text);

	UFUNCTION(BlueprintCallable)
	void SaveNotes(const FText& Text);

	UFUNCTION(BlueprintCallable)
	void UpdateDisplayName(const FText& NewName, const FText& NewLastName, bool bLastNameHighlight);

	UFUNCTION(BlueprintCallable)
	void UpdateFootballerNumber(int32 Number);

	UFUNCTION(BlueprintCallable)
	void UpdateFootballerNationality(const FISO316612& ISO316612);
	
private:
	//~=================================================================================================================
	// Utils
	//~=================================================================================================================
	
	TArray<FFootballerData*> GenerateFootballersDataFromTeam_Deprecated() const;

private:
	//~=================================================================================================================
	// Events
	//~=================================================================================================================
	
	UFUNCTION()
	void OnWidgetClosed(const UWidget* Widget) const;

	UFUNCTION()
	void OnSoccerFieldPositionClicked(EFieldPosition FieldPosition, bool bSelected);

	UFUNCTION()
	void OnFootballersCardScrollBoxSelectionChanged(int32 Index, class UDualButtonScroll* DualButtonScroll);

protected:
	//~=================================================================================================================
	// Getters
	//~=================================================================================================================
	
	UFUNCTION(BlueprintImplementableEvent, DisplayName="GetFootballersCardScrollBox")
	UDBSBFootballerCard* K2_GetFootballersCardScrollBox() const;

	UFUNCTION(BlueprintImplementableEvent, DisplayName="GetListTextNumberValues (Technical)")
	UListTextNumberValues* K2_GetListTextNumberValues_Technical() const;

	UFUNCTION(BlueprintImplementableEvent, DisplayName="GetListTextNumberValues (Physical)")
	UListTextNumberValues* K2_GetListTextNumberValues_Physical() const;

	UFUNCTION(BlueprintImplementableEvent, DisplayName="GetListTextNumberValues (Mental)")
	UListTextNumberValues* K2_GetListTextNumberValues_Mental() const;

	UFUNCTION(BlueprintImplementableEvent, DisplayName="GetSoccerField")
	USoccerField* K2_GetSoccerField() const;

	UFUNCTION(BlueprintImplementableEvent, DisplayName="GetListTextNumberValues (Stats This Season)")
	UListTextNumberValues* K2_GetListTextNumberValues_StatsThisSeason() const;

	UFUNCTION(BlueprintImplementableEvent, DisplayName="GetListTextNumberValues (Stats All Seasons)")
	UListTextNumberValues* K2_GetListTextNumberValues_StatsAllSeasons() const;
	
protected:
	//~=================================================================================================================
	// Header
	//~=================================================================================================================

	UFUNCTION(BlueprintImplementableEvent, DisplayName="OnFootballerName")
	void K2_OnFootballerName(const FText& Name, const FText& LastName, bool bLastNameHighlight);

	UFUNCTION(BlueprintImplementableEvent, DisplayName="OnFootballerRating")
	void K2_OnFootballerRating(ERatingLevel RatingLevel, float RatingAmountStars);

	UFUNCTION(BlueprintImplementableEvent, DisplayName="OnFootballerNumber")
	void K2_OnFootballerNumber(int32 Number);
	
	UFUNCTION(BlueprintImplementableEvent, DisplayName="OnFootballerNationality")
	void K2_OnFootballerNationality(const FISO316612& ISO316612);
	
	UFUNCTION(BlueprintImplementableEvent, DisplayName="OnFootballerAge")
	void K2_OnFootballerAge(int32 Age);

	UFUNCTION(BlueprintImplementableEvent, DisplayName="OnFootballerAgeOfRetirement")
	void K2_OnFootballerAgeOfRetirement(int32 Age);

	UFUNCTION(BlueprintImplementableEvent, DisplayName="OnFootballerPreferredPositions")
	void K2_OnFootballerPreferredPositions(const TArray<EFieldPosition>& Positions);

	UFUNCTION(BlueprintImplementableEvent, DisplayName="OnFootballerPreferredFoot")
	void K2_OnFootballerPreferredFoot(EPreferredFootType PreferredFootType);

	UFUNCTION(BlueprintImplementableEvent, DisplayName="OnFootballerRole")
	void K2_OnFootballerRole(const FText& Role);
	
	UFUNCTION(BlueprintImplementableEvent, DisplayName="OnFootballerTeam")
	void K2_OnFootballerTeam(const FText& Team);

	UFUNCTION(BlueprintImplementableEvent, DisplayName="OnFootballerHeight")
	void K2_OnFootballerHeight(int32 Centimeters);

	UFUNCTION(BlueprintImplementableEvent, DisplayName="OnFootballerWeight")
	void K2_OnFootballerWeight(int32 Kilograms);

	UFUNCTION(BlueprintImplementableEvent, DisplayName="OnFootballerContract")
	void K2_OnFootballerContract(int32 BeginYear, int32 EndYear);

	UFUNCTION(BlueprintImplementableEvent, DisplayName="OnFootballerrMilestone (Left)")
	void K2_OnFootballerMilestone_Left(const FText& Header, int32 Value);

	UFUNCTION(BlueprintImplementableEvent, DisplayName="OnFootballerMilestone (Center)")
	void K2_OnFootballerMilestone_Center(const FText& Header, int32 Value);

	UFUNCTION(BlueprintImplementableEvent, DisplayName="OnFootballerMilestone (Right)")
	void K2_OnFootballerMilestone_Right(const FText& Header, int32 Value);

protected:
	//~=================================================================================================================
	// Update Editable Panels
	//~=================================================================================================================

	UFUNCTION(BlueprintCallable, DisplayName="GetEditablePanelInfo (Footballer Name)")
	void GetEditablePanelInfo_FootballerName(FText& OutName, FText& OutLastName, bool& OutLastNameHighlight) const;

	UFUNCTION(BlueprintCallable, DisplayName="GetEditablePanelInfo (Footballer Number)")
	void GetEditablePanelInfo_FootballerNumber(int32& OutNumber, TArray<int32>& OutReservedNumbers) const;

	UFUNCTION(BlueprintCallable, DisplayName="GetEditablePanelInfo (Footballer Nationality)")
	FISO316612 GetEditablePanelInfo_FootballerNationality() const;

	
protected:
	//~=================================================================================================================
	// Events | General tab
	//~=================================================================================================================

	/**
	 * @param Fill Normalized value between 0 and 1
	 */
	UFUNCTION(BlueprintImplementableEvent, DisplayName="OnUpdateCondition")
	void K2_OnUpdateCondition(float Fill);

	/**
	 * @param Fill Normalized value between 0 and 1
	 */
	UFUNCTION(BlueprintImplementableEvent, DisplayName="OnUpdateMorale")
	void K2_OnUpdateMorale(float Fill);

	/**
	 * @param Percentage Normalized value between 0 and 1
	 */	
	UFUNCTION(BlueprintImplementableEvent, DisplayName="OnUpdateSharpness")
	void K2_OnUpdateSharpness(const FText& TextValue, const FLinearColor& Color);

	/**
	 * @param Index 0:None 1:Low 2:High
	 */	
	UFUNCTION(BlueprintImplementableEvent, DisplayName="OnUpdateInjuries")
	void K2_OnUpdateInjuries(int32 Index, const FDateTime& InjuredEndDate);

	UFUNCTION(BlueprintImplementableEvent, DisplayName="OnUpdateCards")
	void K2_OnUpdateCards(int32 YellowAmount, int32 RedAmount);

	UFUNCTION(BlueprintImplementableEvent, DisplayName="OnUpdateRatingLevel")
	void K2_OnUpdateRatingLevel(ERatingLevel RatingLevel);

	UFUNCTION(BlueprintImplementableEvent, DisplayName="OnUpdateOverallRating")
	void K2_OnUpdateOverallRating(ERatingLevel RatingLevel, float RatingAmountStars);

	UFUNCTION(BlueprintImplementableEvent, DisplayName="OnUpdatePotentialRating")
	void K2_OnUpdatePotentialRating(ERatingLevel RatingLevel, float RatingAmountStars);

	UFUNCTION(BlueprintImplementableEvent, DisplayName="OnUpdateSpecialTrait")
	void K2_OnUpdateSpecialTrait(const FText& DisplayName, int32 Level);

	UFUNCTION(BlueprintImplementableEvent, DisplayName="OnEnableCaptainRibbon")
	void K2_OnEnableCaptainRibbon(ECharacterType CharacterType);
	
	UFUNCTION(BlueprintImplementableEvent, DisplayName="OnUpdateAffinityWithManager")
	void K2_OnUpdateAffinityWithManager(float ProgressbarFill, int32 NumericValue);

	UFUNCTION(BlueprintImplementableEvent, DisplayName="OnUpdateAlignmentWithTeam")
	void K2_OnUpdateAlignmentWithTeam(float ProgressbarFill, int32 NumericValue);

	UFUNCTION(BlueprintImplementableEvent, DisplayName="OnPersonalityType")
	void K2_OnPersonalityType(EPersonalityType PersonalityType, const FText& PersonalityText);

	UFUNCTION(BlueprintImplementableEvent, DisplayName="OnTeamDynamics")
	void K2_OnTeamDynamics();
	
protected:
	//~=================================================================================================================
	// Events | Attributes tab
	//~=================================================================================================================

	UFUNCTION(BlueprintImplementableEvent, DisplayName="OnUpdateRadarChart")
	void K2_OnUpdateRadarChart(const TArray<struct FRadarChartValue_Blueprint>& Values, EFieldPosition FieldPosition, ERatingLevel RatingLevel, float RatingStars);

protected:
	//~=================================================================================================================
	// Events | Contracts tab
	//~=================================================================================================================

	UFUNCTION(BlueprintImplementableEvent, DisplayName="OnContractDuration")
	void K2_OnContractDuration(const FDateTime& ExpirySeason, int32 SeasonsRemaining);

	UFUNCTION(BlueprintImplementableEvent, DisplayName="OnContractSalary")
	void K2_OnContractSalary(double Salary);

	UFUNCTION(BlueprintImplementableEvent, DisplayName="OnContractMarketValue")
	void K2_OnContractMarketValue(double MarketValue, const FDateTime& LastUpdateMarketValue);

	UFUNCTION(BlueprintImplementableEvent, DisplayName="OnContractOffers")
	void K2_OnContractOffers();
	
protected:
	//~=================================================================================================================
	// Events | History/Stats tab
	//~=================================================================================================================

	UFUNCTION(BlueprintImplementableEvent, DisplayName="OnUpdateStartSeason")
	void K2_OnUpdateStartSeason(const FText& DisplayText);
	
	// UFUNCTION(BlueprintImplementableEvent, DisplayName="OnPopulateStats (This Season)")
	// void K2_OnPopulateStats_ThisSeason(int32 MatchesPlayed, int32 GoalsScored, int32 MostGoalsInOneMatch, int32 SeasonsInTheClub);
	//
	// UFUNCTION(BlueprintImplementableEvent, DisplayName="OnPopulateStats (All Time)")
	// void K2_OnPopulateStats_AllTime(int32 MatchesPlayed, int32 GoalsScored, int32 MostGoalsInOneMatch, int32 SeasonsInTheClub);

	UFUNCTION(BlueprintImplementableEvent, DisplayName="OnUpdateAwards")
	void K2_OnUpdateAwards(const TArray<FAwardValue_Blueprint>& Values);

protected:
	//~=================================================================================================================
	// Popup notifies
	//~=================================================================================================================

	UFUNCTION(BlueprintImplementableEvent, DisplayName="OnPopupDisplay (Condition)")
	void K2_OnPopupDisplay_Condition(bool bVisible, const FText& Message);

	UFUNCTION(BlueprintImplementableEvent, DisplayName="OnPopupDisplay (Morale)")
	void K2_OnPopupDisplay_Morale(bool bVisible, const FText& Message);

	UFUNCTION(BlueprintImplementableEvent, DisplayName="OnPopupDisplay (Sharpness)")
	void K2_OnPopupDisplay_Sharpness(bool bVisible, const FText& Message);

	UFUNCTION(BlueprintImplementableEvent, DisplayName="OnPopupDisplay (Injuries)")
	void K2_OnPopupDisplay_Injuries(bool bVisible, const FText& Message);

	UFUNCTION(BlueprintImplementableEvent, DisplayName="OnPopupDisplay (Cards)")
	void K2_OnPopupDisplay_Cards(bool bVisible, const FText& Message);
	
private:
	UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess=true))
	UStringTable* LocalizationStringTable {};
	
	UPROPERTY()
	const UTeam_Deprecated* CurrentTeam {};

	//@todo(jcastro): Make smart pointer? Create callback?
	FFootballerData* CurrentFootballerData {};

public:
	//~=================================================================================================================
	// @todo(jcastro) This is a temporary fix to prevent repetitive calls of DisplayWidget. It should be removed once
	// @todo(jcastro) LineUp is migrated to Slate.
	//~=================================================================================================================
	inline static bool bDisplayWidget {};
	//~=================================================================================================================

	UPROPERTY(BlueprintAssignable)
	FFootballerProfileClosed OnFootballerProfileClosed {};
};
