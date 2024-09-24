// Copyright, 2023, by NGD Studios AB. All rights reserved.


#include "PostMatchSplashScreen.h"
#include "Football/UI/UserWidget/PostMatch/PostMatchSplashScreenMVP.h"
#include "Football/Private/Common/Logging.h"

void UPostMatchSplashScreen::SetUpSplashScreen()
{
	if (MatchInfo.Results.HomeTeam.PlayingFootballers.IsEmpty() || MatchInfo.Results.AwayTeam.PlayingFootballers.IsEmpty())
	{
		UE_LOG(LogFootball, Error, TEXT("Match info is empty for pre match splash screen"));
		return;
	}

	CalculateTeamResaults();
	SetUpMVP();
}


void UPostMatchSplashScreen::CalculateTeamResaults()
{
	int32 HomeTeamGoals = MatchInfo.Results.HomeTeam.Goals;
	int32 AwayTeamGoals = MatchInfo.Results.AwayTeam.Goals;

	if (HomeTeamGoals == AwayTeamGoals)
	{
		K2_OnUpdateHomeTeam(MatchInfo.Results.HomeTeam.Name, HomeTeamGoals, BackgroundColors["Draw"], ScoreColors["Draw"]);
		K2_OnUpdateAwayTeam(MatchInfo.Results.AwayTeam.Name, AwayTeamGoals, BackgroundColors["Draw"], ScoreColors["Draw"]);
	}
	else if (HomeTeamGoals > AwayTeamGoals)
	{
		K2_OnUpdateHomeTeam(MatchInfo.Results.HomeTeam.Name, HomeTeamGoals, BackgroundColors["Wining"], ScoreColors["Wining"]);
		K2_OnUpdateAwayTeam(MatchInfo.Results.AwayTeam.Name, AwayTeamGoals, BackgroundColors["Losing"], ScoreColors["Losing"]);
	}
	else
	{
		K2_OnUpdateHomeTeam(MatchInfo.Results.HomeTeam.Name, HomeTeamGoals, BackgroundColors["Losing"], ScoreColors["Losing"]);
		K2_OnUpdateAwayTeam(MatchInfo.Results.AwayTeam.Name, AwayTeamGoals, BackgroundColors["Wining"], ScoreColors["Wining"]);
	}
}

void UPostMatchSplashScreen::SetUpMVP()
{
	check(MVP);

	struct FFooballerPerfomancePair
	{
		int32 Id = 0;
		int32 Performance = 0;
	};

	TArray<FFooballerPerfomancePair> HomeFootballers;
	TArray<FFooballerPerfomancePair> AwayFootballers;

	//TODO Sergio the arrays don't have the same elements that the maps there is one les footballer probably the last

	for (auto& Footballer : MatchInfo.Results.HomeTeam.PeformanceByFootballer)
	{
		FFooballerPerfomancePair NewFootballer;
		NewFootballer.Id = Footballer.Key;
		NewFootballer.Performance = Footballer.Value;
		HomeFootballers.Add(NewFootballer);
	}

	for (auto& Footballer : MatchInfo.Results.AwayTeam.PeformanceByFootballer)
	{
		FFooballerPerfomancePair NewFootballer;
		NewFootballer.Id = Footballer.Key;
		NewFootballer.Performance = Footballer.Value;
		AwayFootballers.Add(NewFootballer);
	}

	HomeFootballers.Sort([](const FFooballerPerfomancePair& A, const FFooballerPerfomancePair& B)
	{
		return A.Performance < B.Performance;
	});

	AwayFootballers.Sort([](const FFooballerPerfomancePair& A, const FFooballerPerfomancePair& B)
	{
			return A.Performance < B.Performance;
	});

	FFooballerPerfomancePair BestHomeFootballer = HomeFootballers.Pop();
	FFooballerPerfomancePair BestAwayFootballer = AwayFootballers.Pop();

	TArray<EHighlightEvent> GoalTypes = { EHighlightEvent::Goal };
	TArray<EHighlightEvent> ShotsTypes = { EHighlightEvent::Goal, EHighlightEvent::ShotBlocked, EHighlightEvent::ShotMissed };

	if (BestHomeFootballer.Performance > BestAwayFootballer.Performance)
	{
		FFootballerData* BestFootballer = MatchInfo.Results.HomeTeam.PlayingFootballers.FindByPredicate(
			[&](const FFootballerData& Footballer)
			{
				return Footballer.Id == BestHomeFootballer.Id;
			});

		MVP->UpdateMVP(*BestFootballer
			, MatchInfo.GetHighlightsCountMapByType(GoalTypes, true)[BestHomeFootballer.Id]
			, MatchInfo.GetHighlightsCountMapByType(ShotsTypes, true)[BestHomeFootballer.Id]
			, MatchInfo.Results.HomeTeam.PeformanceByFootballer[BestHomeFootballer.Id]
		);
	}
	else
	{
		FFootballerData* BestFootballer = MatchInfo.Results.AwayTeam.PlayingFootballers.FindByPredicate(
			[&](const FFootballerData& Footballer)
			{
				return Footballer.Id == BestAwayFootballer.Id;
			});

		MVP->UpdateMVP(*BestFootballer
			, MatchInfo.GetHighlightsCountMapByType(GoalTypes, false)[BestAwayFootballer.Id]
			, MatchInfo.GetHighlightsCountMapByType(ShotsTypes, false)[BestAwayFootballer.Id]
			, MatchInfo.Results.AwayTeam.PeformanceByFootballer[BestAwayFootballer.Id]
		);
	}
	
}
