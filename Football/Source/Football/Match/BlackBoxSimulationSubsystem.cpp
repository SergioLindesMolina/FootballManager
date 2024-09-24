// Copyright, 2023, by NGD Studios AB. All rights reserved.


#include "BlackBoxSimulationSubsystem.h"
#include <Common/Logging.h>
#include <Kismet/DataTableFunctionLibrary.h>
#include "Football/CoreClasses/FootballerObject.h"
#include "BlackBoxSimulationConfig.h"


namespace
{
	TMap<ETacticValue, float> DefaultWorkRateMultipliers =
	{
		{ ETacticValue::VeryLow , 0.8f },
		{ ETacticValue::Low , 0.9f },
		{ ETacticValue::Balanced , 1.0f },
		{ ETacticValue::High , 1.1f },
		{ ETacticValue::VeryHigh , 1.2f }
	};

	TMap<ETacticValue,float> TeamFocusMultipliers =
	{
		{ ETacticValue::UltraDefensive , 0.5f },
		{ ETacticValue::Defensive , 0.8f },
		{ ETacticValue::Balanced , 1.0f },
		{ ETacticValue::Offensive , 1.2f },
		{ ETacticValue::AllOutAttack , 1.5f }
	};

	TMap<ETacticValue,float> ForceCounterAttackPossessionMultipliers =
	{
		{ ETacticValue::Yes , 0.5f },
		{ ETacticValue::No , 1.0f }
	};

	TMap<ETacticValue,float> ForceCounterAttackShotsMultipliers =
	{
		{ ETacticValue::Yes , 1.1f },
		{ ETacticValue::No , 1.0f }
	};

	TMap<EFieldPosition,float> ShotsByPositionWeights =
	{
		{ EFieldPosition::GK , 0.5f },
		{ EFieldPosition::DL , 5.0f },
		{ EFieldPosition::DC , 5.0f },
		{ EFieldPosition::DR , 5.0f },
		{ EFieldPosition::DM , 5.0f },
		{ EFieldPosition::ML , 10.0f },
		{ EFieldPosition::MC , 10.0f },
		{ EFieldPosition::MR , 10.0f },
		{ EFieldPosition::AML , 20.0f },
		{ EFieldPosition::AMC , 20.0f },
		{ EFieldPosition::AMR , 20.0f },
		{ EFieldPosition::ST , 65.0f }
	};
}

namespace
{
	TArray BalancedPassingPossesionAttributes = {
		EFootballerAttributes::ShortPassing,
		EFootballerAttributes::LongPassing,
		EFootballerAttributes::Control,
		EFootballerAttributes::Dribbling,
		EFootballerAttributes::Creativity
	};

	TArray ShortPassingOffensePossesionAttributes = {
		EFootballerAttributes::ShortPassing,
		EFootballerAttributes::Control,
		EFootballerAttributes::Dribbling,
		EFootballerAttributes::Creativity
	};

	TArray LongPassingOffensePossesionAttributes = {
		EFootballerAttributes::LongPassing,
		EFootballerAttributes::Control,
		EFootballerAttributes::Dribbling,
		EFootballerAttributes::Creativity
	};

	TArray DefensePossesionAttributes = {
		EFootballerAttributes::Marking,
		EFootballerAttributes::Tackling,
		EFootballerAttributes::Sacrifice,
		EFootballerAttributes::Aggression,
		EFootballerAttributes::Teamwork,
		EFootballerAttributes::Discipline
	};

	TArray ShotAttributes = {
		EFootballerAttributes::Heading,
		EFootballerAttributes::Shooting,
		EFootballerAttributes::Finishing
	};

	TArray GKAttributes = {
		EFootballerAttributes::Reflexes,
		EFootballerAttributes::Handling,
		EFootballerAttributes::OneOnOnes,
		EFootballerAttributes::Reach
	};

	TArray GoalkeeperPosition = { EFieldPosition::GK };

	TArray FieldPositions = {
		EFieldPosition::DC,
		EFieldPosition::DL,
		EFieldPosition::DR,
		EFieldPosition::DM,
		EFieldPosition::MC,
		EFieldPosition::ML,
		EFieldPosition::MR,
		EFieldPosition::AMC,
		EFieldPosition::AML,
		EFieldPosition::AMR,
		EFieldPosition::ST
	};
}


FMatchInfo UBlackBoxSimulationSubsystem::SimulateMatch(UBlackBoxSimulationConfig* Config, UTeam_Deprecated* HomeTeam, UTeam_Deprecated* AwayTeam)
{
	SimulationConfig = Config;

	TArray<FMatchHighlight> MatchHighlights;

	FVector2D Possession = SimulatePossession( HomeTeam, AwayTeam );
	FIntPoint Shots = SimulateOpportunities( MatchHighlights, Possession, HomeTeam, AwayTeam );
	FIntPoint ShotsOnTarget = SimulateShotsOnTarget( MatchHighlights, HomeTeam, AwayTeam );
	FIntPoint Score = SimulateGoals( MatchHighlights, HomeTeam, AwayTeam );

	FMatchStats HomeTeamStats;
	FMatchStats AwayTeamStats;

	HomeTeamStats.Name = HomeTeam->Name;
	AwayTeamStats.Name = AwayTeam->Name;

	HomeTeamStats.ExpectedGoals = SimulateExpectedGoals(MatchHighlights).X;
	AwayTeamStats.ExpectedGoals = SimulateExpectedGoals(MatchHighlights).Y;

	HomeTeamStats.MinutesByFootballer = CalculateMinutesByFootballer(HomeTeam);
	AwayTeamStats.MinutesByFootballer = CalculateMinutesByFootballer(AwayTeam);

	HomeTeamStats.Goals = Score.X;
	AwayTeamStats.Goals = Score.Y;

	HomeTeamStats.Possession = Possession.X;
	AwayTeamStats.Possession = Possession.Y;

	HomeTeamStats.Shots = Shots.X;
	AwayTeamStats.Shots = Shots.Y;

	HomeTeamStats.ShotsOnTarget = ShotsOnTarget.X;
	AwayTeamStats.ShotsOnTarget = ShotsOnTarget.Y;

	HomeTeamStats.RedPenaltyCards    = SimulatePenaltyCards(HomeTeam, AwayTeam)[Footballer::EPenaltyCardType::Red].X;
	AwayTeamStats.RedPenaltyCards    = SimulatePenaltyCards(HomeTeam, AwayTeam)[Footballer::EPenaltyCardType::Red].Y;
	HomeTeamStats.YellowPenaltyCards = SimulatePenaltyCards(HomeTeam, AwayTeam)[Footballer::EPenaltyCardType::Yellow].X;
	AwayTeamStats.YellowPenaltyCards = SimulatePenaltyCards(HomeTeam, AwayTeam)[Footballer::EPenaltyCardType::Yellow].Y;

	HomeTeamStats.PostMatchEffectsByFootballer = CalculatePostMatchEffects(HomeTeam, HomeTeamStats.MinutesByFootballer, Score, true);
	AwayTeamStats.PostMatchEffectsByFootballer = CalculatePostMatchEffects(AwayTeam, AwayTeamStats.MinutesByFootballer, Score, false);

	PopulateMatchStats(HomeTeamStats, AwayTeamStats, &MatchHighlights, HomeTeam, AwayTeam);

	const float FieldTilt = CalculateFieldTilt(HomeTeamStats, HomeTeam, AwayTeam);
	
	HomeTeamStats.Corners = CalculateCorners(HomeTeam, AwayTeam, FieldTilt).X;
	AwayTeamStats.Corners = CalculateCorners(HomeTeam, AwayTeam, FieldTilt).Y;

	HomeTeamStats.Fouls = CalculateFouls(HomeTeam, AwayTeam).X;
	AwayTeamStats.Fouls = CalculateFouls(HomeTeam, AwayTeam).Y;

	HomeTeamStats.PassesCompleted = CalculatePassesCompleted(HomeTeam, AwayTeam).X;
	AwayTeamStats.PassesCompleted = CalculatePassesCompleted(HomeTeam, AwayTeam).Y;

	
	FMatchResult MatchResult;
	MatchResult.HomeTeam = HomeTeamStats;
	MatchResult.AwayTeam = AwayTeamStats;
	MatchResult.Highlights = MatchHighlights;
	MatchResult.FieldTilt = FieldTilt;

	FMatchInfo MatchInfo;
	MatchInfo.Results = MatchResult;
	MatchInfo.Attedances = SimulationConfig->CalculateAttendance(HomeTeam->OverallRating, AwayTeam->OverallRating);
	MatchInfo.Income = SimulationConfig->CalculateIncome(MatchInfo.Attedances);

	MatchInfo.DateAndHour = FDateTime::Now();
	MatchInfo.Country = ECountryCode::ES;
	MatchInfo.City = "Madrid";
	MatchInfo.Weather = static_cast<EWeather>(FMath::RandRange(0, static_cast<int32>(EWeather::MAX_COUNT) - 1));

	MatchInfo.Results.ManagerXPRnd = FMath::RandRange(0, 30);
	MatchInfo.Results.ManagerRivalryRnd = FMath::RandRange(0, 3);
	MatchInfo.Results.PreviousManagerXPRnd += MatchInfo.Results.ManagerXPRnd; //< Fastest Workaround to milestone 1. Please, change me :)
	
	HomeTeam->ApplyPostMatchEffects(HomeTeamStats.PostMatchEffectsByFootballer);
	AwayTeam->ApplyPostMatchEffects(AwayTeamStats.PostMatchEffectsByFootballer);

	return MatchInfo;
}

TMap<int32, int32> UBlackBoxSimulationSubsystem::CalculateMinutesByFootballer(const UTeam_Deprecated* Team)
{
	TMap<int32, int32> MinutesByFootballer;
	for (const TObjectPtr<UFootballerObject> FootballerObject : Team->Starters)
	{
		MinutesByFootballer.Add( FootballerObject->Data.Id, 90 );
	}

	return MinutesByFootballer;
}

void UBlackBoxSimulationSubsystem::PopulateMatchStats(FMatchStats& HomeStats, FMatchStats& AwayStats, const TArray<FMatchHighlight>* MatchHighlights, const UTeam_Deprecated* HomeTeam, const UTeam_Deprecated* AwayTeam)
{
	//Initialize Stats by footballer info 
	//TODO Sergio Take in consideration the Substitutes

	for (const TObjectPtr<UFootballerObject> Footballer : HomeTeam->Starters)
	{
		HomeStats.PeformanceByFootballer.Add(Footballer->Data.Id);
		HomeStats.PeformanceByFootballer[Footballer->Data.Id] = FMath::RandRange(0, 100);
		HomeStats.PlayingFootballers.Add(Footballer->Data);
	}

	for (const TObjectPtr<UFootballerObject> Footballer : AwayTeam->Starters)
	{
		AwayStats.PeformanceByFootballer.Add(Footballer->Data.Id);
		AwayStats.PeformanceByFootballer[Footballer->Data.Id] = FMath::RandRange(0, 100);
		AwayStats.PlayingFootballers.Add(Footballer->Data);
	}

	CalculateTeamAttributesToIncrease(HomeStats);
	CalculateTeamAttributesToIncrease(AwayStats);
}

float UBlackBoxSimulationSubsystem::CalculateTeamAttributesQuality(const UTeam_Deprecated* Team, const TArray<EFootballerAttributes>& Attributes, float Multiplier, const TArray<EFieldPosition>& IncluedPositions)
{
	float TotalQuality = 0.0f;
	float TotalStateValues = 0.0f;
	int32 FootballersCount = 0;

	for (const UFootballerObject* FObj : Team->Starters)
	{
		const FFootballerData& Footballer = FObj->Data;
		if (IncluedPositions.Contains(Footballer.SelectedFieldPosition))
		{
			for (EFootballerAttributes Attribute : Attributes)
			{
				TotalQuality += Footballer.Attributes[static_cast<int32>(Attribute)];
			}

			TotalQuality = TotalQuality * Multiplier;
			TotalQuality = TotalQuality / SimulationConfig->AttributeMaxValue;
			TotalQuality = TotalQuality / Attributes.Num();

			TotalStateValues = (Footballer.State.Morale + Footballer.State.Sharpness + Footballer.State.Condition) / 3.0f;
			TotalStateValues = TotalStateValues / SimulationConfig->StateMaxValue;

			FootballersCount++;
		}
	}

	return ((TotalQuality + TotalStateValues) / 2) / (FootballersCount);
}

float UBlackBoxSimulationSubsystem::CalculatePlayerAttributesQuality(const FFootballerData* Footballer, const TArray<EFootballerAttributes>& Attributes, float Multiplier, const TArray<EFieldPosition>& IncluedPositions)
{
	float TotalQuality = 0.0f;
	float TotalStateValues = 0.0f;

	if (IncluedPositions.Contains(Footballer->SelectedFieldPosition))
	{
		for (EFootballerAttributes Attribute : Attributes)
		{
			TotalQuality += Footballer->Attributes[static_cast<int32>(Attribute)];
		}

		TotalQuality = TotalQuality * Multiplier;
		TotalQuality = TotalQuality / SimulationConfig->AttributeMaxValue;
		TotalQuality = TotalQuality / Attributes.Num();

		TotalStateValues = (Footballer->State.Morale + Footballer->State.Sharpness + Footballer->State.Condition) / 3.0f;
		TotalStateValues = TotalStateValues / SimulationConfig->StateMaxValue;

	}

	return ((TotalQuality + TotalStateValues) / 2);
}

FVector2D UBlackBoxSimulationSubsystem::SimulatePossession( const UTeam_Deprecated* HomeTeam, const UTeam_Deprecated* AwayTeam )
{
	TArray<EFootballerAttributes> OffensePossesionAttributes = GetAttributesByPassingStyle(HomeTeam);

	float HomeDefenseMultiplier = DefaultWorkRateMultipliers[HomeTeam->GetTacticValue(ETacticGroup::DefaultWorkRate).Key] + ForceCounterAttackPossessionMultipliers[HomeTeam->GetTacticValue(ETacticGroup::ForceCounterAttack).Key] + SimulationConfig->PossessionDefenseMultiplier;
	float AwayDefenseMultiplier = DefaultWorkRateMultipliers[AwayTeam->GetTacticValue(ETacticGroup::DefaultWorkRate).Key] + ForceCounterAttackPossessionMultipliers[AwayTeam->GetTacticValue(ETacticGroup::ForceCounterAttack).Key] + SimulationConfig->PossessionDefenseMultiplier;

	// Calculate offensive and defensive quality of the teams
	float HomeOffensePossessionQuality = CalculateTeamAttributesQuality( HomeTeam, OffensePossesionAttributes, SimulationConfig->PossessionOffenseMultiplier, FieldPositions);
	float AwayOffensePossessionQuality = CalculateTeamAttributesQuality( AwayTeam, OffensePossesionAttributes, SimulationConfig->PossessionOffenseMultiplier, FieldPositions);

	float HomeDefensePossessionQuality = CalculateTeamAttributesQuality( HomeTeam, DefensePossesionAttributes, HomeDefenseMultiplier, FieldPositions);
	float AwayDefensePossessionQuality = CalculateTeamAttributesQuality( AwayTeam, DefensePossesionAttributes, AwayDefenseMultiplier, FieldPositions);

	// Calculate ball possession based on offensive and defensive quality
	float HomeTeamPossessionQuality = HomeOffensePossessionQuality / ( 1 + AwayDefensePossessionQuality );
	float AwayTeamPossessionQuality = AwayOffensePossessionQuality / ( 1 + HomeDefensePossessionQuality );

	//Mix Rating into the equation
	float HomeTeamRatingRatio = HomeTeam->OverallRating / AwayTeam->OverallRating;
	HomeTeamPossessionQuality *= HomeTeamRatingRatio;
	AwayTeamPossessionQuality *= (1.0f/HomeTeamRatingRatio);

	float RandomFactor = FMath::FRandRange( 1 - SimulationConfig->PossessionRandomFactor, 1 + SimulationConfig->PossessionRandomFactor );
	FVector2D Possession;
	Possession.X = ( HomeTeamPossessionQuality / ( HomeTeamPossessionQuality + AwayTeamPossessionQuality ) ) * RandomFactor;
	Possession.Y = 1.0f - Possession.X;



	return Possession;
}

FIntPoint UBlackBoxSimulationSubsystem::SimulateOpportunities(TArray<FMatchHighlight>& MatchHighlights, FVector2D TotalPossession, const UTeam_Deprecated* HomeTeam, const UTeam_Deprecated* AwayTeam)
{
	FIntPoint GoalOpportunities = { 0, 0 };

	float TotalHomePossession = TotalPossession.X;
	float TotalAwayPossession = TotalPossession.Y;
	
	float PossesionThreshold = (TotalHomePossession > TotalAwayPossession) ? TotalHomePossession : TotalAwayPossession;
	bool HomeHasMorePossession = (TotalHomePossession > TotalAwayPossession);

	for (float Minute = 1.0f; Minute <= 90.0f; Minute++) 
	{
		float RandomFactor = FMath::FRand();

		FMatchHighlight Opportunity;
		Opportunity.Minute = Minute;
		Opportunity.Type = EHighlightEvent::BallLoss;

		if ( RandomFactor < PossesionThreshold )
		{
			Opportunity.IsHomeTeam = HomeHasMorePossession;
		}
		else if ( RandomFactor <= 1 )
		{
			Opportunity.IsHomeTeam = !HomeHasMorePossession;
		}

		// Shot Calculation
		const UTeam_Deprecated* CurrentTeam = Opportunity.IsHomeTeam ? HomeTeam : AwayTeam;
		const UTeam_Deprecated* OtherTeam = Opportunity.IsHomeTeam ? AwayTeam : HomeTeam;
		float TeamRating = CurrentTeam->OverallRating;
		float RivalRating = OtherTeam->OverallRating;
		float ForceCounterAttackMultiplier = ForceCounterAttackShotsMultipliers[CurrentTeam->GetTacticValue(ETacticGroup::ForceCounterAttack).Key];
		float TeamFocusMultiplierResult = ( TeamFocusMultipliers[HomeTeam->GetTacticValue(ETacticGroup::TeamFocus).Key] + TeamFocusMultipliers[OtherTeam->GetTacticValue(ETacticGroup::TeamFocus).Key] ) / 2;

		float ShotProbability = FMath::FRandRange( 0, ( TeamRating + ( RivalRating * SimulationConfig->OpportunityMultiplier * TeamFocusMultiplierResult * ForceCounterAttackMultiplier )));

		if ( TeamRating < ShotProbability )
		{
			Opportunity.PerformingPlayer = *ChooseShootingPlayer(CurrentTeam);
			Opportunity.Type = EHighlightEvent::ShotMissed;
			
			if (Opportunity.IsHomeTeam)
			{
				GoalOpportunities.X += 1;
			}
			else 
			{
				GoalOpportunities.Y += 1;
			}
		}
		MatchHighlights.Add(Opportunity);
	}

	return GoalOpportunities;
}

float UBlackBoxSimulationSubsystem::CalculateFieldTilt(const FMatchStats& LocalTeamMatchStats, const UTeam_Deprecated* HomeTeam, const UTeam_Deprecated* AwayTeam)
{
	float MyTeamFocusValue = 0;
	switch (HomeTeam->GetTacticValue(ETacticGroup::TeamFocus).Key)
	{
		case ETacticValue::UltraDefensive:	MyTeamFocusValue = -0.05f; break;
		case ETacticValue::Defensive:		MyTeamFocusValue = -0.02f; break;
		case ETacticValue::Balanced:		MyTeamFocusValue =  0.00f; break;
		case ETacticValue::Offensive:		MyTeamFocusValue =  0.02f; break;
		case ETacticValue::AllOutAttack:	MyTeamFocusValue =  0.05f; break;

		default: UE_LOG(LogFootball, Error, TEXT("")); 
	}
	
	float RivalTeamFocusValue = 0;
	switch (AwayTeam->GetTacticValue(ETacticGroup::TeamFocus).Key)
	{
		case ETacticValue::UltraDefensive:	RivalTeamFocusValue = -0.05f; break;
		case ETacticValue::Defensive:		RivalTeamFocusValue = -0.02f; break;
		case ETacticValue::Balanced:		RivalTeamFocusValue =  0.00f; break;
		case ETacticValue::Offensive:		RivalTeamFocusValue =  0.02f; break;
		case ETacticValue::AllOutAttack:	RivalTeamFocusValue =  0.05f; break;

		default: UE_LOG(LogFootball, Error, TEXT("")); 
	}
	
	const float FieldTiltRndFactor = FMath::RandRange(-0.05f, 0.05f);
	return LocalTeamMatchStats.Possession * (1 + (MyTeamFocusValue - RivalTeamFocusValue) + FieldTiltRndFactor);
}

FIntPoint UBlackBoxSimulationSubsystem::CalculateCorners(const UTeam_Deprecated* HomeTeam, const UTeam_Deprecated* RivalTeam, const float FieldTilt)
{
	int32 HomeTeamBaseCorners = 0;
	switch (HomeTeam->GetTacticValue(ETacticGroup::ForceSetPieces).Key)
	{
		case ETacticValue::None:		HomeTeamBaseCorners = FMath::RandRange( 5,  7); break;
		case ETacticValue::FreeKicks:	HomeTeamBaseCorners = FMath::RandRange( 5,  7); break;
		case ETacticValue::Corners:		HomeTeamBaseCorners = FMath::RandRange(18, 12); break;
		case ETacticValue::Both:		HomeTeamBaseCorners = FMath::RandRange( 8, 17); break;

		default: UE_LOG(LogFootball, Error, TEXT("")); 
	}

	int32 RivalTeamBaseCorners = 0;
	switch (RivalTeam->GetTacticValue(ETacticGroup::ForceSetPieces).Key)
	{
		case ETacticValue::None:		RivalTeamBaseCorners = FMath::RandRange( 5,  7); break;
		case ETacticValue::FreeKicks:	RivalTeamBaseCorners = FMath::RandRange( 5,  7); break;
		case ETacticValue::Corners:		RivalTeamBaseCorners = FMath::RandRange(18, 12); break;
		case ETacticValue::Both:		RivalTeamBaseCorners = FMath::RandRange( 8, 17); break;

		default: UE_LOG(LogFootball, Error, TEXT("")); 
	}	
	
	FIntPoint Result;
	Result.X = FMath::RoundToInt32(FieldTilt * HomeTeamBaseCorners);
	Result.Y = FMath::RoundToInt32((1.0 - FieldTilt) * RivalTeamBaseCorners);
	
	return Result;
}

FIntPoint UBlackBoxSimulationSubsystem::CalculateFouls(const UTeam_Deprecated* HomeTeam, const UTeam_Deprecated* RivalTeam)
{
	// Calculate average
	float HomeAggression {};
	for(UFootballerObject* FootballerObject : HomeTeam->Starters)
	{
		//HomeAggression += FootballerObject->Data.Attributes[static_cast<int32>(EFootballerAttributes::Aggression)];
		HomeAggression += FootballerObject->Data.Attributes.NormalizeAttribute(static_cast<int32>(EFootballerAttributes::Aggression));
	}
	HomeAggression /= HomeTeam->Starters.Num();

	
	float RivalAggression {};
	for(UFootballerObject* FootballerObject : RivalTeam->Starters)
	{
		//RivalAggression += FootballerObject->Data.Attributes[static_cast<int32>(EFootballerAttributes::Aggression)];
		RivalAggression += FootballerObject->Data.Attributes.NormalizeAttribute(static_cast<int32>(EFootballerAttributes::Aggression));
	}
	RivalAggression /= RivalTeam->Starters.Num();

	float HomeBaseFouls = 0;
	switch (HomeTeam->GetTacticValue(ETacticGroup::TacklingStyle).Key)
	{
		case ETacticValue::Cautious:	HomeBaseFouls = FMath::RandRange( 0,  5); break;
		case ETacticValue::Balanced:	HomeBaseFouls = FMath::RandRange( 6, 12); break;
		case ETacticValue::Aggressive:	HomeBaseFouls = FMath::RandRange(13, 20); break;

		default: UE_LOG(LogFootball, Error, TEXT("")); 
	}

	float RivalBaseFouls = 0;
	switch (RivalTeam->GetTacticValue(ETacticGroup::TacklingStyle).Key)
	{
		case ETacticValue::Cautious:	RivalBaseFouls = FMath::RandRange( 0,  5); break;
		case ETacticValue::Balanced:	RivalBaseFouls = FMath::RandRange( 6, 12); break;
		case ETacticValue::Aggressive:	RivalBaseFouls = FMath::RandRange(13, 20); break;

		default: UE_LOG(LogFootball, Error, TEXT("")); 
	}

	const float HomeAggressionFactor  = HomeAggression;
	const float RivalAggressionFactor = RivalAggression;

	FIntPoint Result;
	Result.X = FMath::RoundToInt32(HomeBaseFouls  * HomeAggressionFactor);
	Result.Y = FMath::RoundToInt32(RivalBaseFouls * RivalAggressionFactor);
	return Result;
}

FIntPoint UBlackBoxSimulationSubsystem::CalculatePassesCompleted(const UTeam_Deprecated* HomeTeam, const UTeam_Deprecated* RivalTeam)
{
	float HomePassingQuality {};
	for(UFootballerObject* FootballerObject : HomeTeam->Starters)
	{
		HomePassingQuality +=
		(
			FootballerObject->Data.Attributes[static_cast<int32>(EFootballerAttributes::ShortPassing)]
			+ FootballerObject->Data.Attributes[static_cast<int32>(EFootballerAttributes::LongPassing)]
		);
	}

	float RivalPassingQuality {};
	for(UFootballerObject* FootballerObject : RivalTeam->Starters)
	{
		RivalPassingQuality +=
		(
			FootballerObject->Data.Attributes[static_cast<int32>(EFootballerAttributes::ShortPassing)]
			+ FootballerObject->Data.Attributes[static_cast<int32>(EFootballerAttributes::LongPassing)]
		);
	}

	int32 HomeBasePasses = 0;
	switch (HomeTeam->GetTacticValue(ETacticGroup::PassingStyle).Key)
	{
		case ETacticValue::Short:		HomeBasePasses = FMath::RandRange(275, 300); break;
		case ETacticValue::Balanced:	HomeBasePasses = FMath::RandRange(225, 274); break;
		case ETacticValue::Long:		HomeBasePasses = FMath::RandRange(200, 224); break;
	
		default: UE_LOG(LogFootball, Error, TEXT("")); 
	}

	int32 RivalBasePasses = 0;
	switch (RivalTeam->GetTacticValue(ETacticGroup::PassingStyle).Key)
	{
		case ETacticValue::Short:		RivalBasePasses = FMath::RandRange(275, 300); break;
		case ETacticValue::Balanced:	RivalBasePasses = FMath::RandRange(225, 274); break;
		case ETacticValue::Long:		RivalBasePasses = FMath::RandRange(200, 224); break;
		
		default: UE_LOG(LogFootball, Error, TEXT("")); 
	}	

	// @see https://nimblegiant.slack.com/archives/C054VQXQJP4/p1699346744643969?thread_ts=1699346413.289419&cid=C054VQXQJP4
	//
	// Ambos son valores constantes.
	// MaxPassingQuality es el máximo posible que puede tener un equipo (si cada jugador tuviera a 20 ambos atributos
	// relacionados con pases (=20*11)) MaxPasssesFromPassingQuality es cuántos pases, arbitrariamente, decidimos que
	// provengan, cómo máximo, de los atributos de pases. Pero de nuevo, es solo para ilustrar de dónde viene el factor.
	// Lo importante es que el factor es (también) siempre el mismo
	constexpr float PassingQualityFactor = 3520.f/300.f;
	
	FIntPoint Result;
	Result.X = HomeBasePasses  + (HomePassingQuality  / PassingQualityFactor);
	Result.Y = RivalBasePasses + (RivalPassingQuality / PassingQualityFactor);
	return Result;
}

FVector2d UBlackBoxSimulationSubsystem::SimulateExpectedGoals(TArray<FMatchHighlight>& MatchHighlights)
{
	float SUM_ShotOnTargetProbability_Home  = 0;
	float SUM_ShotOnTargetProbability_Rival = 0;

	for (const FMatchHighlight& Opportunity : MatchHighlights)
	{
		if (Opportunity.Type == EHighlightEvent::ShotMissed)
		{
			const float ShotOnTargetProbability = FMath::FRandRange(0, 1 + SimulationConfig->ShotRandomFactor);
			if (Opportunity.IsHomeTeam)
			{
				SUM_ShotOnTargetProbability_Home += ShotOnTargetProbability;
			}
			else
			{
				SUM_ShotOnTargetProbability_Rival += ShotOnTargetProbability;
			}
		}
	}

	FVector2d Result;
	Result.X = SUM_ShotOnTargetProbability_Home	 / 3.f;
	Result.Y = SUM_ShotOnTargetProbability_Rival / 3.f;
	
	return Result;
}

std::array<FIntPoint, 2> UBlackBoxSimulationSubsystem::SimulatePenaltyCards(const UTeam_Deprecated* HomeTeam, const UTeam_Deprecated* RivalTeam)
{
	std::array<FIntPoint, 2> Cards {};
	
	for(UFootballerObject* _ : HomeTeam->Starters)
	{
		if(FMath::RandRange(0.f, 1.f) <= 0.2)
		{
			if(FMath::RandRange(0.f, 1.f) <= 0.03)
			{
				Cards[Footballer::EPenaltyCardType::Red].X++;
			}
			else if(FMath::RandRange(0.f, 1.f) <= 0.17)
			{
				Cards[Footballer::EPenaltyCardType::Yellow].X++;
			}
		}
	}

	for(UFootballerObject* _ : RivalTeam->Starters)
	{
		if(FMath::RandRange(0.f, 1.f) <= 0.2)
		{
			if(FMath::RandRange(0.f, 1.f) <= 0.03)
			{
				Cards[Footballer::EPenaltyCardType::Red].Y++;
			}
			else if(FMath::RandRange(0.f, 1.f) <= 0.17)
			{
				Cards[Footballer::EPenaltyCardType::Yellow].Y++;
			}
		}
	}
	
	return Cards;
}

FIntPoint UBlackBoxSimulationSubsystem::SimulateShotsOnTarget( TArray<FMatchHighlight>& MatchHighlights, const UTeam_Deprecated* HomeTeam, const UTeam_Deprecated* AwayTeam )
{
	FIntPoint ShotsOnTarget = { 0, 0 };

	for (FMatchHighlight& Opportunity : MatchHighlights)
	{
		if ( Opportunity.Type == EHighlightEvent::ShotMissed )
		{
			float ShotQuality = CalculatePlayerAttributesQuality( &Opportunity.PerformingPlayer, ShotAttributes, SimulationConfig->ShotPrecisionMultiplier, FieldPositions );
			float ShotOnTargetProbability = FMath::FRandRange(0, 1 + SimulationConfig->ShotRandomFactor);

			if (ShotQuality > ShotOnTargetProbability)
			{
				Opportunity.Type = EHighlightEvent::ShotBlocked;
				if (Opportunity.IsHomeTeam)
				{
					ShotsOnTarget.X = ShotsOnTarget.X + 1;
				}
				else
				{
					ShotsOnTarget.Y = ShotsOnTarget.Y + 1;
				}
			}
		}

	}
	return ShotsOnTarget;
}

FIntPoint UBlackBoxSimulationSubsystem::SimulateGoals(TArray<FMatchHighlight>& MatchHighlights, const UTeam_Deprecated* HomeTeam, const UTeam_Deprecated* AwayTeam )
{
	FIntPoint Result = { 0, 0 };

	float HomeGoalkeeperQuality = CalculateTeamAttributesQuality(HomeTeam, GKAttributes, SimulationConfig->GoalkeeperMultiplier, GoalkeeperPosition );
	float AwayGoalkeeperQuality = CalculateTeamAttributesQuality(AwayTeam, GKAttributes, SimulationConfig->GoalkeeperMultiplier, GoalkeeperPosition );

	for (FMatchHighlight& Opportunity : MatchHighlights)
	{
		if (Opportunity.Type == EHighlightEvent::ShotBlocked)
		{
			if (Opportunity.IsHomeTeam)
			{
				float HomeGoalkeeperProbability = SimulationConfig->CalculateGoalkeeperProbability(HomeGoalkeeperQuality);
				float GoalProbability = FMath::FRand();

				if (HomeGoalkeeperProbability < GoalProbability)
				{
					Opportunity.Type = EHighlightEvent::Goal;
					Result.X = Result.X + 1;
				}
			}
			else 
			{
				float AwayGoalkeeperProbability = SimulationConfig->CalculateGoalkeeperProbability(AwayGoalkeeperQuality);
				float GoalProbability = FMath::FRand();

				if (AwayGoalkeeperProbability < GoalProbability)
				{
					Opportunity.Type = EHighlightEvent::Goal;
					Result.Y = Result.Y + 1;
				}
			}


		}
	}

	return Result;
}

TArray<EFootballerAttributes> UBlackBoxSimulationSubsystem::GetAttributesByPassingStyle(const UTeam_Deprecated* Team)
{
	ETacticValue Tactic = Team->GetTacticValue(ETacticGroup::PassingStyle).Key;

	switch (Tactic)
	{
	case ETacticValue::Long:
		return ShortPassingOffensePossesionAttributes;
		break;
	case ETacticValue::Short:
		return LongPassingOffensePossesionAttributes;
		break;
	case ETacticValue::Balanced:
	default:
		return BalancedPassingPossesionAttributes;
		break;
	}
}

const FFootballerData* UBlackBoxSimulationSubsystem::ChooseShootingPlayer(const UTeam_Deprecated* Team)
{
	float SumOfWeights = 0;

	for (const auto& PositionWeight : ShotsByPositionWeights)
	{
		if (Team->HasPositionInCurrentFormation(PositionWeight.Key))
		{
			SumOfWeights += PositionWeight.Value;
		}
	}

	float RandomValue = FMath::RandRange(0.0f, SumOfWeights);

	for (const auto& PositionWeight : ShotsByPositionWeights)
	{
		if (RandomValue < PositionWeight.Value)
		{
			for (const TObjectPtr<UFootballerObject>& Player : Team->Starters)
			{
				if (Player->GetSelectedFieldPosition() == PositionWeight.Key)
				{
					return &Player->Data;
				}
			}
		}
		RandomValue -= PositionWeight.Value;
	}

	UE_LOG(LogFootball, Error, TEXT("No valid player found to take the shot"));
	return &Team->Starters.Last()->Data;

};

TMap<int32, FPostMatchEffects> UBlackBoxSimulationSubsystem::CalculatePostMatchEffects(UTeam_Deprecated* Team, TMap<int32, int32> MinutesByFootballer, FIntPoint Score, bool IsHome)
{
	TMap<int32, FPostMatchEffects> Result;

	for (TObjectPtr<UFootballerObject> FootballerObject : Team->Starters)
	{
		FPostMatchEffects PostMatchEffects;

		int32 MinutesPlayed = MinutesByFootballer[FootballerObject->Data.Id];
		float FitnessValue = FootballerObject->Data.Attributes[static_cast<int32>(EFootballerAttributes::Fitness)];
		
		PostMatchEffects.Condition = SimulationConfig->CalculatePostMatchCondition( MinutesPlayed, FitnessValue );
		PostMatchEffects.Morale = SimulationConfig->CalculatePostMatchMorale( Score , IsHome );
		PostMatchEffects.Sharpness = SimulationConfig->CalculatePostMatchSharpness(MinutesPlayed);

		Result.Add( FootballerObject->Data.Id, PostMatchEffects );
	}

	return Result;
}

void UBlackBoxSimulationSubsystem::CalculateTeamAttributesToIncrease(FMatchStats& TeamStats)
{
	for (FFootballerData FootballerData : TeamStats.PlayingFootballers)
	{
		if (TeamStats.MinutesByFootballer.Contains(FootballerData.Id) && TeamStats.MinutesByFootballer[FootballerData.Id] > SimulationConfig->MinimumMinutesPlayedToProgress)
		{
			TMap<EFootballerAttributes, int32> Attributes = CalculateAttributesToIncrease(FootballerData, TeamStats.MinutesByFootballer);

			for (auto& AttributesPair : Attributes)
			{
				TeamStats.PostMatchEffectsByFootballer[FootballerData.Id].AttributesToIncrease.Add(AttributesPair.Key, AttributesPair.Value);
				EFootballerAttributes Key = AttributesPair.Key;
			}
		}
	}
}

TMap<EFootballerAttributes, int32> UBlackBoxSimulationSubsystem::CalculateAttributesToIncrease(FFootballerData FootballerData, TMap<int32, int32> MinutesByFootballer)
{
	TMap<EFootballerAttributes, int32> Result;
	int32 NumberOfAttributesToIncrese = 0;
	NumberOfAttributesToIncrese = GetNumberOfAttributesToIncrease();

	//IMPORTANT: The order of the properties must be the same that in the table!
	FName PositionName = FName(UEnum::GetDisplayValueAsText(FootballerData.SelectedFieldPosition).ToString());
	TArray<FString> PositionPropertiesWeightsValues = UDataTableFunctionLibrary::GetDataTableColumnAsString(SimulationConfig->PerformanceAttributesWeightsTable, PositionName);
	
	for (int32 i = 0; i < NumberOfAttributesToIncrese; i++)
	{
		TArray<int32> EqualWeightIndices;
		float TotalPropertiesWeight = FCString::Atof(*PositionPropertiesWeightsValues.Last());
		float RandomValue = FMath::RandRange(0.0f, TotalPropertiesWeight);

		for (int32 Index = 0; Index < FootballerData.Attributes.Num(); Index++)
		{
			float PropertyWeight = FCString::Atof(*PositionPropertiesWeightsValues[Index]);
			if (RandomValue < PropertyWeight)
			{
				EqualWeightIndices.Add(Index);
			}
			else
			{
				RandomValue -= PropertyWeight;
			}

			if (RandomValue <= 0)
			{
				break;
			}
		}

		int32 RandomIndex = 0;
		if (EqualWeightIndices.Num() > 0)
		{
			int32 WeightIndex =  FMath::RandRange(0, EqualWeightIndices.Num() - 1);
			RandomIndex = EqualWeightIndices[WeightIndex];
		}
		else
		{
			RandomIndex = FMath::RandRange(0, FootballerData.Attributes.Num());
		}

		int32 ValueToIncrease = FMath::RandRange(SimulationConfig->ValueToIncreaseRandomRange.X, SimulationConfig->ValueToIncreaseRandomRange.Y);
		Result.Add(static_cast<EFootballerAttributes>(RandomIndex), ValueToIncrease);
	}
	
	return Result;
}

//TODO: Maybe this function should also be in BP?
int32 UBlackBoxSimulationSubsystem::GetNumberOfAttributesToIncrease()
{
	float Probability = FMath::FRand();
	int32 NumberOfAttributesToIncrese = 0;

	if (Probability <= SimulationConfig->ThreeAttributeToIncreseHighProbability)
	{
		NumberOfAttributesToIncrese = 3;
	}
	else if (Probability <= SimulationConfig->TwoAttributeToIncreseProbability)
	{
		NumberOfAttributesToIncrese = 2;
	}
	else if (Probability <= SimulationConfig->OneAttributeToIncreseProbability)
	{
		NumberOfAttributesToIncrese = 1;
	}

	return NumberOfAttributesToIncrese;
}
