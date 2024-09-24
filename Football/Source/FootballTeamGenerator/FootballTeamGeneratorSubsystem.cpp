// Copyright, 2023, by NGD Studios AB. All rights reserved.

#include "FootballTeamGeneratorSubsystem.h"

#include <Football/CoreClasses/DataStructures/Footballer.h>
#include <Football/CoreClasses/GameEntities/FootballerCharacter.h>
#include <Common/Logging.h>

#include "Internationalization/Regex.h"


bool UFootballTeamGeneratorSubsystem::LoadTeamSpreadsheetFromDisk(const FString& Filename)
{
	FString CSVBody;
	if (ensure(FFileHelper::LoadFileToString(CSVBody, *(FPaths::ProjectContentDir() / "Football" / "Teams" / Filename + ".csv"))))
	{
		TArray<FString> Rows;
		CSVBody.ParseIntoArrayLines(Rows);

		if(Rows.Num() - 1 != FTeam::TeamSize)
		{
			//UE_LOG(LogFootballTeamGenerator, Error, TEXT("Mismatch number of row in CSV and FTeam::TeamSize = %d/%d"), Rows.Num() - 1, FTeam::TeamSize);
			return false;
		}

		using namespace Footballer;
		FTeam::FFootballers Footballers;

		static const TMap<FString, EFieldPosition> PositionMap =
		{
			{ "GK", 	EFieldPosition::GK	},
			{ "DL", 	EFieldPosition::DL	},
			{ "DC", 	EFieldPosition::DC	},
			{ "DR", 	EFieldPosition::DR	},
			{ "DM", 	EFieldPosition::DM	},
			{ "ML", 	EFieldPosition::ML	},
			{ "MC", 	EFieldPosition::MC	},
			{ "MR", 	EFieldPosition::MR	},
			{ "AML", 	EFieldPosition::AML	},
			{ "AMC", 	EFieldPosition::AMC	},
			{ "AMR", 	EFieldPosition::AMR	},
			{ "ST",		EFieldPosition::ST	}
		};

		static const TMap<FString, ERatingLevel> RatingLevelMap =
		{
			{ "Bronze",   ERatingLevel::Bronze	 },
			{ "Silver",   ERatingLevel::Silver	 },
			{ "Gold",	  ERatingLevel::Gold	 },
			{ "Platinum", ERatingLevel::Platinum }
		};

		for (int32 i = 0; i < FTeam::TeamSize; i++)
		{
			enum { Number, Name, Surname, Positions, Level, Stars, Rating, StatsBegin, MAX_COLUMNS };
			
			// Skip the header row by starting at index 1
			TArray<FString> Columns;
			Rows[i+1].ParseIntoArray(Columns, TEXT(","), true);

			// This CSV parser expect the next columns:
			//	1. MAX_COLUMNS
			//	4. FFootballerEntity::MAX_COUNT stats
			static constexpr uint32 ExpectedColumnCount = (MAX_COLUMNS - 1) + static_cast<uint32>(EFootballerAttributes::MAX_COUNT);
			if(Columns.Num() != ExpectedColumnCount)
			{
				//UE_LOG(LogFootballTeamGenerator, Error, TEXT("Mismatch number of columns in CSV. Read: %d. Expected: %d"), Columns.Num(), ExpectedColumnCount);
				return false;
			}

			FFootballerData Footballer;
			Footballer.Number   = FCString::Atoi(*(Columns[Number]));
			Footballer.DisplayName.FirstName = FText::FromString(Columns[Name]);
			Footballer.DisplayName.LastName  = FText::FromString(Columns[Surname]);
			
			Footballer.State.Condition  = FMath::FRand();
			Footballer.State.Morale   = static_cast<EMorale>(FMath::Rand() % 5);
			Footballer.State.Injured = FMath::RandBool();
			Footballer.State.PenaltyCards[EPenaltyCardType::Red]    = FMath::Rand() % 1;
			Footballer.State.PenaltyCards[EPenaltyCardType::Yellow] = FMath::Rand() % 2;

			// Parse the string value from the CSV into the enum value of the FootballerEntity
			if(ensureAlways(PositionMap.Contains(Columns[Positions])))
			{
				Footballer.SelectedFieldPosition = PositionMap[Columns[Positions]];
			}

			// Parse tier
			if(ensureAlways(RatingLevelMap.Contains(Columns[Level])))
			{
				Footballer.Rating.Level = RatingLevelMap[Columns[Level]];
			}

			// Parse stars
			Footballer.Rating.Stars = FCString::Atof(*(Columns[Stars]));

			// Parse rating
			Footballer.Rating.Overall = FCString::Atof(*(Columns[Rating]));

			// // Parse the Rating value from the CSV into the enumc and float values of the FootballerEntity
			// FRegexMatcher RatingMatcher(FRegexPattern("^\\s*(.*?)\\s*\\(\\s*(-?[0-9]*\\.?[0-9]+)\\s*\\)\\s*$"), Columns[Rating]);
			// if (ensureAlways(RatingMatcher.FindNext())
			// {
			// 	const FString RatingLevel = RatingMatcher.GetCaptureGroup(1);
			// 	const FString RatingStars = RatingMatcher.GetCaptureGroup(2);
			// 	
			// 	if(ensureAlways(RatingTierMap.Contains(RatingLevel)))
			// 	{
			// 		Footballer.RatingTier  = RatingTierMap[RatingLevel];
			// 		Footballer.RatingStars = FCString::Atof(*RatingStars);
			// 	}
			// }
			
			// Initialize the stat values of the FootballerEntity
			for (int32 j = 0; j < static_cast<uint32>(EFootballerAttributes::MAX_COUNT); j++)
			{
				Footballer.Attributes[j] = FCString::Atof(*Columns[StatsBegin + j]);
			}

			Footballers[i] = MakeShared<FFootballerData>(Footballer);
		}

		Team = MakeUnique<FTeam>(MoveTemp(Footballers));
		return true;
	}

	return false;
}

void UFootballTeamGeneratorSubsystem::GenerateTeamRandomly()
{
	FTeam::FFootballers Footballers;
	for(int32 i = 0; i < FTeam::TeamSize; i++)
	{
		Footballers[i] = MakeShared<FFootballerData>(FFootballTeamGeneratorModule::GenerateFootballerEntity());
	}

	Team = MakeUnique<FTeam>(MoveTemp(Footballers));
}

void UFootballTeamGeneratorSubsystem::ApplyFootballerEntityToFootballerCharacter(AFootballerCharacter* FootballerCharacter, const int32 Index)
{
	FootballerCharacter->UpdateFootballerEntity(*Team->GetFootballer(Index));
}

void UFootballTeamGeneratorSubsystem::ReadFootballer(const int32 Index, FString& OutSurname, FString& OutPositionString, int32& OutNumber, float& OutPerform, float& OutFatigue, int32& OutHappiness, bool& OutbHasRedAdmonition, int32& OutCountYellowAdmonition, bool& OutbIsInjured)
{
	if(ensure(Team.IsValid()))
	{
		using namespace Footballer;
		static const TMap<EFieldPosition, FString> PositionMap =
		{
			{ EFieldPosition::GK, 	"GK"  },
			{ EFieldPosition::DL, 	"DL"  },
			{ EFieldPosition::DC, 	"DC"  },
			{ EFieldPosition::DR, 	"DR"  },
			{ EFieldPosition::DM, 	"DM"  },
			{ EFieldPosition::ML, 	"ML"  },
			{ EFieldPosition::MC, 	"MC"  },
			{ EFieldPosition::MR, 	"MR"  },
			{ EFieldPosition::AML,	"AML" },
			{ EFieldPosition::AMC,	"AMC" },
			{ EFieldPosition::AMR,	"AMR" },
			{ EFieldPosition::ST,	"ST"  }
		};

		const FFootballerData* FootballerData = Team->GetFootballer(Index);
		
		OutSurname					= FootballerData->DisplayName.LastName.ToString();
		OutPositionString			= PositionMap[FootballerData->SelectedFieldPosition];
		OutNumber					= FootballerData->Number;
		OutPerform					= FootballerData->Rating.Overall;
		OutFatigue					= FootballerData->State.Condition;
		OutHappiness				= static_cast<int32>(FootballerData->State.Morale);
		OutbHasRedAdmonition		= FootballerData->State.PenaltyCards[EPenaltyCardType::Red] > 0;		
		OutCountYellowAdmonition	= FootballerData->State.PenaltyCards[EPenaltyCardType::Yellow];
		OutbIsInjured				= static_cast<bool>(FootballerData->State.Injured);
	}
}
