// Copyright, 2023, by NGD Studios AB. All rights reserved.

#include "FootballTeamGeneratorModule.h"

FString FFootballTeamGeneratorModule::GenerateRandomName()
{
	static FString Names[20] = { "Jon", "Jorge", "Paco", "Pedro", "Ana", "María", "Luis", "Miguel", "Laura",
								 "Elena", "Carlos", "Sofía", "David", "Isabel", "Fernando", "Rosa", "Raúl",
								 "Carmen", "Manuel", "Beatriz" };
		
	return Names[FMath::Rand() % 20];
}

FString FFootballTeamGeneratorModule::GenerateRandomSurName()
{
	FString LastNames[] = { "García", "Rodríguez", "López", "Martínez", "Hernández", "González", "Pérez", "Sánchez",
							"Ramírez", "Flores", "Torres", "Rivera", "Vargas", "Castillo", "Romero", "Díaz",
							"Moreno", "Álvarez", "Rojas", "Núñez" };
		
	return LastNames[FMath::Rand() % 20];
}

FFootballerData FFootballTeamGeneratorModule::GenerateFootballerEntity()
{
	using namespace Footballer;
	FFootballerData Entity;

	Entity.DisplayName = FFootballerData::FFootballerName(
		FText::FromString(GenerateRandomName()),
		FText::FromString(GenerateRandomSurName())
	);

	for(int32 i = 0; i < static_cast<int32>(EFootballerAttributes::MAX_COUNT); i++)
	{
		Entity.Attributes[i] = FMath::Rand() % 100 + 1;
	}
		
	Entity.SelectedFieldPosition = EFieldPosition::DC;
	Entity.Rating.Level   = ERatingLevel::Gold;
	Entity.Rating.Stars   = 2.5f;

	Entity.State.PenaltyCards[EPenaltyCardType::Yellow] = 0;
	Entity.State.PenaltyCards[EPenaltyCardType::Red]    = 0;
		
	return Entity;
}

FTeam FFootballTeamGeneratorModule::GenerateTeam()
{
	FTeam::FFootballers Footballers;
	for(int32 i = 0; i < FTeam::TeamSize; i++)
	{
		Footballers[i] = MakeShared<FFootballerData>(GenerateFootballerEntity());
	}

	return FTeam(MoveTemp(Footballers));
}

IMPLEMENT_MODULE(FFootballTeamGeneratorModule, FootballTeamGenerator);
