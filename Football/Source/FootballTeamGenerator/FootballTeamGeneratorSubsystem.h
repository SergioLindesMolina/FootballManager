// Copyright, 2023, by NGD Studios AB. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include <Subsystems/GameInstanceSubsystem.h>
#include "FootballTeamGeneratorModule.h"

#include "FootballTeamGeneratorSubsystem.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class FOOTBALLTEAMGENERATOR_API UFootballTeamGeneratorSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category="FootballTeamGenerator|BlueprintFunctionLibrary")
	bool LoadTeamSpreadsheetFromDisk(const FString& Filename);

	UFUNCTION(BlueprintCallable, Category="FootballTeamGenerator|BlueprintFunctionLibrary")
	void GenerateTeamRandomly();
	
	UFUNCTION(BlueprintCallable, Category="FootballTeamGenerator|BlueprintFunctionLibrary")
	void ApplyFootballerEntityToFootballerCharacter(class AFootballerCharacter* FootballerCharacter, int32 Index);

	UFUNCTION(BlueprintCallable, Category="FootballTeamGenerator|BlueprintFunctionLibrary")
	void ReadFootballer(int32 Index, FString& OutSurname, FString& OutPositionString, int32& OutNumber, float& OutPerform, float& OutFatigue, int32& OutHappiness, bool& OutbHasRedAdmonition, int32& OutCountYellowAdmonition, bool& OutbIsInjured);
	
private:
	TUniquePtr<FTeam> Team;
};
