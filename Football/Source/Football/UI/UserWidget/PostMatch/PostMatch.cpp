// Copyright, 2023, by NGD Studios AB. All rights reserved.


#include "PostMatch.h"

#include <Components/TextBlock.h>

#include <UWidget/CompareTableIntegers.h>
#include <UWidget/DualProgressbar.h>
#include <UWidget/MultiSegmentProgressBar.h>

#include <Football/CoreClasses/FootballGameInstance.h>
#include <Football/UI/LocalizationBFL.h>
#include <Football/UI/UWidget/SoccerField/SoccerField.h>


void UPostMatch::NativeConstruct()
{
	Super::NativeConstruct();

	// GetWorld()->GetTimerManager().SetTimerForNextTick([&]
	// {
	// 	const UFootballGameInstance* FootballGameInstance = GetWorld()->GetGameInstance<UFootballGameInstance>();
	// 	if(ensure(FootballGameInstance))
	// 	{
	// 		FillFromMatchInfo(FootballGameInstance->GetMatchInfo());
	// 	}	
	// });
}

void UPostMatch::ForceLoadFromMathInfo()
{
	const UFootballGameInstance* FootballGameInstance = GetWorld()->GetGameInstance<UFootballGameInstance>();
	if(ensure(FootballGameInstance))
	{
		const FMatchInfo MatchInfo = FootballGameInstance->GetMatchInfo();
		FillFromMatchInfo(MatchInfo);
	}
}

void UPostMatch::FillFromMatchInfo(const FMatchInfo& MatchInfo)
{
	//~=================================================================================================================
	// HEADER
	//~=================================================================================================================
	{
		K2_OnHeader(
			INVTEXT("MANAGER1"),
			FText::FromString(MatchInfo.Results.HomeTeam.Name),
			INVTEXT("MANAGER2"),
			FText::FromString(MatchInfo.Results.AwayTeam.Name)
		);

		K2_GetGoalsResultLabel()->SetText(FText::Format(INVTEXT("{0}-{1}"), MatchInfo.Results.HomeTeam.Goals, MatchInfo.Results.AwayTeam.Goals));

		if(MatchInfo.Results.HomeTeam.Goals > MatchInfo.Results.AwayTeam.Goals)
		{
			K2_GetVictoryResultLabel()->SetText(INVTEXT("VICTORY"));
			K2_GetVictoryResultLabel()->SetColorAndOpacity(FColor::FromHex("#3DC726"));
		}
		else if(MatchInfo.Results.HomeTeam.Goals < MatchInfo.Results.AwayTeam.Goals)
		{
			K2_GetVictoryResultLabel()->SetText(INVTEXT("DEFEAT"));
			K2_GetVictoryResultLabel()->SetColorAndOpacity(FColor::FromHex("#F51D1D"));
		}
		else
		{
			K2_GetVictoryResultLabel()->SetText(INVTEXT("DRAW"));
			K2_GetVictoryResultLabel()->SetColorAndOpacity(FColor::FromHex("#DFCB1A"));
		}		
	}
	
	//~=================================================================================================================
	// MATCH INFO
	//~=================================================================================================================
	{
		K2_OnDateAndHour(FText::FromString(MatchInfo.DateAndHour.ToString()));
		K2_OnPlace(FText::Format(INVTEXT("{0},{1}"), FText::FromString(MatchInfo.City), INVTEXT("N/A")));
		K2_OnWeather(ULocalizationBFL::LoadLocalizedWeather(MatchInfo.Weather), MatchInfo.Weather);
		K2_OnAttendance(FText::AsNumber(MatchInfo.Attedances));
		K2_OnIncome(FText::AsNumber(MatchInfo.Income));
	}

	//~=================================================================================================================
	// BALL POSSESSION
	//~=================================================================================================================
	{
		UDualProgressbar* BallPossession = K2_GetDualProgressbarBallPossession();
		check(BallPossession);

		BallPossession->SetFillPercentage(MatchInfo.Results.HomeTeam.Possession);
	}

	//~=================================================================================================================
	// FIELD TILT
	//~=================================================================================================================
	{
		USoccerField* SoccerField = K2_GetSoccerField();
		check(SoccerField);
		SoccerField->SetPossessionValues({1.0f - MatchInfo.Results.FieldTilt, MatchInfo.Results.FieldTilt});
		K2_GetFieldTiltLabel()->SetText(FText::Format(INVTEXT("{0}% - {1}%"), FMath::RoundToInt(100*MatchInfo.Results.FieldTilt), FMath::RoundToInt(100*(1.0f - MatchInfo.Results.FieldTilt))));
	}
	
	//~=================================================================================================================
	// GOALS HIGHLIGHTS
	//~=================================================================================================================
	{
		const UCompareTableIntegers* GoalsHighlights = K2_GetCompareTableGoalsHighlights();
		check(GoalsHighlights);

		GoalsHighlights->ClearElements();
		
		for(const FMatchHighlight& Highlight : MatchInfo.Results.Highlights)
		{
			if(Highlight.Type == EHighlightEvent::Goal)
			{
				if(Highlight.IsHomeTeam)
				{
					GoalsHighlights->AddElement(1, 0, Highlight.PerformingPlayer.DisplayName.GetDisplayName());
				}
				else
				{
					GoalsHighlights->AddElement(0, 1, Highlight.PerformingPlayer.DisplayName.GetDisplayName());
				}
			}
		}
	}

	//~=================================================================================================================
	// MATCH STATS
	//~=================================================================================================================
	{
		const UCompareTableIntegers* MatchStats = K2_GetCompareTableMatchStats();
		check(MatchStats);

		MatchStats->ClearElements();

		// 1. Shots
		MatchStats->AddElement(
			MatchInfo.Results.HomeTeam.Shots,
			MatchInfo.Results.AwayTeam.Shots,
			INVTEXT("Shots")
		);
		// 1. Shots on Target
		MatchStats->AddElement(
			MatchInfo.Results.HomeTeam.ShotsOnTarget,
			MatchInfo.Results.AwayTeam.ShotsOnTarget,
			INVTEXT("Shots on Target")
		);
		// 2. Expected Goals
		MatchStats->AddElement(
			MatchInfo.Results.HomeTeam.ExpectedGoals,
			MatchInfo.Results.AwayTeam.ExpectedGoals,
			INVTEXT("Expected Goals")
		);
		// 3. Passes Completed
		MatchStats->AddElement(
			MatchInfo.Results.HomeTeam.PassesCompleted,
			MatchInfo.Results.AwayTeam.PassesCompleted,
			INVTEXT("Passes Completed")
		);
		// 4. Corners
		MatchStats->AddElement(
			MatchInfo.Results.HomeTeam.Corners,
			MatchInfo.Results.AwayTeam.Corners,
			INVTEXT("Corners")
		);
		// 5. Fouls
		MatchStats->AddElement(
			MatchInfo.Results.HomeTeam.Fouls,
			MatchInfo.Results.AwayTeam.Fouls,
			INVTEXT("Fouls")
		);		
		// 6. Yellow Cards
		MatchStats->AddElement(
			MatchInfo.Results.HomeTeam.YellowPenaltyCards,
			MatchInfo.Results.AwayTeam.YellowPenaltyCards,
			INVTEXT("Yellow Cards")
		);
		// 7. Red Cards
		MatchStats->AddElement(
			MatchInfo.Results.HomeTeam.RedPenaltyCards,
			MatchInfo.Results.AwayTeam.RedPenaltyCards,
			INVTEXT("Red Cards")
		);		
	}

	//~=================================================================================================================
	// MANAGER PROGRESSION
	//~=================================================================================================================
	{
		UMultiSegmentProgressBar* Experience = K2_GetHeadCoachExperienceProgressbar();
		UMultiSegmentProgressBar* Rivalry    = K2_GetHeadCoachRivalryProgressbar();

		check(Experience && Rivalry);

		//@todo(jcastro) Missing data from design, so I invented here.
		constexpr float EXPERIENCE_MAX_VALUE = 500;
		constexpr float RIVALRY_MAX_VALUE    = 12;

		const float ManagerExperienceTotalFill = MatchInfo.Results.PreviousManagerXPRnd / EXPERIENCE_MAX_VALUE;
		const float ManagerExperienceFill      = MatchInfo.Results.ManagerXPRnd / EXPERIENCE_MAX_VALUE;
		Experience->SetFillPercentage(ManagerExperienceTotalFill);
		Experience->SetSecondFillPercentage(ManagerExperienceFill);
		Experience->SetNumericValue(ManagerExperienceTotalFill * EXPERIENCE_MAX_VALUE);
		Experience->SetSecondNumericValue(ManagerExperienceFill * EXPERIENCE_MAX_VALUE);

		const float RivalryTotal = FMath::RandRange(0.f, (RIVALRY_MAX_VALUE - 3) / RIVALRY_MAX_VALUE);
		const float RivalryPts   = MatchInfo.Results.ManagerRivalryRnd / RIVALRY_MAX_VALUE;
		Rivalry->SetFillPercentage(RivalryTotal);
		Rivalry->SetSecondFillPercentage(RivalryPts);
		Rivalry->SetNumericValue(RivalryTotal * RIVALRY_MAX_VALUE);
		Rivalry->SetSecondNumericValue(RivalryPts * RIVALRY_MAX_VALUE);
	}

	//~=================================================================================================================
	// TEAM PROGRESSION
	//~=================================================================================================================
	{
	}	
}
