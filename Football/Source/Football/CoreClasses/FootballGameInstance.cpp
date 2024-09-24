// Copyright, 2023, by NGD Studios AB. All rights reserved.


#include "FootballGameInstance.h"

#include <Slate/LoadingScreen/SLoadingScreenWidget.h>
#include <Common/Logging.h>

#include "CursorSubsystem.h"
#include "Kismet/GameplayStatics.h"
#include "MoviePlayer.h"
#include "Components/AudioComponent.h"
#include "Football/Match/MatchDefs.h"
#include "Football/Team/TeamGenerator.h"

void UFootballGameInstance::Init()
{
	Super::Init();

	GetMoviePlayer()->OnPrepareLoadingScreen().AddStatic(&UFootballGameInstance::PreSetupLoadingScreen);
	FCoreUObjectDelegates::PreLoadMap.AddUObject(this, &UFootballGameInstance::OnPreLoadMap);
	
	const UCursorSubsystem* CursorSubsystem = UGameInstance::GetSubsystem<UCursorSubsystem>(this);
	CursorSubsystem->ApplyHardwareCursor(UCursorSubsystem::ECursorSubsystemType::Default, TEXT("FootballCursor.ani"));

	UTeamGeneratorFunctionLibrary::SetTeamGeneratorsToDefaultValues(this);
}

void UFootballGameInstance::ReturnToMainMenu()
{
	Super::ReturnToMainMenu();
	UGameplayStatics::OpenLevel(this, "Football/Maps/MainMenu");
}

ULocalPlayer* UFootballGameInstance::CreateInitialPlayer(FString& OutError)
{
	ULocalPlayer* LocalPlayer = Super::CreateInitialPlayer(OutError);
	{
		
	}
	return LocalPlayer;
}

void UFootballGameInstance::SetPlayerTeamGenerator(const FTeamGenerator& NewTeamGenerator)
{
	PlayerTeamGenerator = NewTeamGenerator;
}

void UFootballGameInstance::SetRivalTeamGenerator(const FTeamGenerator& NewTeamGenerator)
{
	RivalTeamGenerator = NewTeamGenerator;
}

void UFootballGameInstance::SetMatchInfo(const FMatchInfo& InMatchInfo)
{
	MatchInfo = MakeShared<FMatchInfo>(InMatchInfo);
}

void UFootballGameInstance::UpdatePlayerTactics(ETacticGroup TacticGroup, int32 NewIndex)
{
	PlayerTeam->UpdateTacticGroup( TacticGroup, NewIndex );
}

void UFootballGameInstance::SetPlayerTeam(UTeam_Deprecated* Team)
{
	PlayerTeam = Team;
}

void UFootballGameInstance::SetRivalTeam(UTeam_Deprecated* Team)
{
	RivalTeam = Team;
}

UTeam_Deprecated* UFootballGameInstance::GetPlayerTeam() const
{
	return PlayerTeam;
}

UTeam_Deprecated* UFootballGameInstance::GetRivalTeam() const
{
	return RivalTeam;
}

FMatchInfo UFootballGameInstance::GetMatchInfo() const
{
	check(MatchInfo.IsValid());
	return *MatchInfo.Get();
}

void UFootballGameInstance::OnPreLoadMap(const FString& NewMap)
{
	
}

void UFootballGameInstance::PreSetupLoadingScreen()
{
	if (IsMoviePlayerEnabled())
	{
		FLoadingScreenAttributes LoadingScreen;
		LoadingScreen.MinimumLoadingScreenDisplayTime	= -1;
		LoadingScreen.bAutoCompleteWhenLoadingCompletes	= true;
		LoadingScreen.bMoviesAreSkippable				= false;
		LoadingScreen.bWaitForManualStop				= false;
		LoadingScreen.bAllowInEarlyStartup				= false;
		LoadingScreen.bAllowEngineTick					= false;
		LoadingScreen.PlaybackType						= MT_Normal;
		
		LoadingScreen.WidgetLoadingScreen = SNew(SLoadingScreenWidget);
	
		GetMoviePlayer()->SetupLoadingScreen(LoadingScreen);
	}
}

