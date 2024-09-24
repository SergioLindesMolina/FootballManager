// Copyright, 2023, by NGD Studios AB. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Football/Team/TeamGenerator.h"

#include "FootballGameInstance.generated.h"

struct FMatchInfo;

/**
 * 
 */
UCLASS()
class FOOTBALL_API UFootballGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable)
	const FTeamGenerator& GetPlayerTeamGenerator() const { return PlayerTeamGenerator; }
	
	UFUNCTION(BlueprintCallable)
	const FTeamGenerator& GetRivalTeamGenerator() const	{ return RivalTeamGenerator; }
	
	UFUNCTION(BlueprintCallable)
	void SetPlayerTeamGenerator(const FTeamGenerator& NewTeamGenerator);
	
	UFUNCTION(BlueprintCallable)
	void SetRivalTeamGenerator(const FTeamGenerator& NewTeamGenerator);
	
	UFUNCTION(BlueprintCallable)
	void SetPlayerTeam(UTeam_Deprecated* Team);
	
	UFUNCTION(BlueprintCallable)
	void SetRivalTeam(UTeam_Deprecated* Team);

	UFUNCTION(BlueprintCallable)
	UTeam_Deprecated* GetPlayerTeam() const;

	UFUNCTION(BlueprintCallable)
	UTeam_Deprecated* GetRivalTeam() const;

	UFUNCTION(BlueprintCallable)
	FMatchInfo GetMatchInfo() const;

	UFUNCTION(BlueprintCallable)
	void SetMatchInfo(const FMatchInfo& MatchInfo);
	
	UFUNCTION(BlueprintCallable)
	void UpdatePlayerTactics(ETacticGroup TacticGroup, int32 NewIndex);

protected:
	void Init() override;
	void ReturnToMainMenu() override;
	
	ULocalPlayer* CreateInitialPlayer(FString& OutError) override;
	
private:
	void OnPreLoadMap(const FString& NewMap);
	static void PreSetupLoadingScreen();
	
	UPROPERTY()
	FTeamGenerator PlayerTeamGenerator;
	
	UPROPERTY()
	FTeamGenerator RivalTeamGenerator;

	UPROPERTY()
	UTeam_Deprecated* PlayerTeam {};

	UPROPERTY()
	UTeam_Deprecated* RivalTeam {};

	TSharedPtr<FMatchInfo> MatchInfo;
};
