// Copyright, 2023, by NGD Studios AB. All rights reserved.

#include "TeamGenerator.h"

#include <Engine/AssetManager.h>
#include <Engine/StreamableManager.h>
#include <Templates/Tuple.h>
#include <Algo/RandomShuffle.h>
#include <Kismet/DataTableFunctionLibrary.h>

#include <numeric>
#include <algorithm>
#include <random>

#include "Football/UI/UserWidget/SquadScreen/SetPieces/SetPieces.h"
#include <Football/UtilsFunctionLibrary.h>
#include <Football/CoreClasses/FootballGameInstance.h>
#include <Football/CoreClasses/DataStructures/Tactics.h>


UTeam_Deprecated::UTeam_Deprecated() : Super() 
{
	Starters.SetNum(11);
	Substitutes.SetNum(7);
	Reserves.SetNum(7);

	//Starters + Substitutes
	for (int32 i = 0; i<18; i++)
	{	
		SetPiecesData.Add(NewObject<USetPieceData>(USetPieceData::StaticClass()));
	}
}

const TArray<FString> UTeam_Deprecated::GetTacticsValuesDebug() const
{
	TArray<FString> Result;
	for(const FTacticGroup& Tactic : TeamTactics)
	{
		Result.Add(FString::Printf(TEXT("Tactic Group : %s with value %s"), *Tactic.DisplayName.ToString(), *Tactic.Values[Tactic.SelectedIndex].DisplayName.ToString()));
	}

	return Result;
}

void UTeam_Deprecated::ChangeFootballerPosition(UFootballerObject* Footballer, EFieldPosition NewPosition)
{
	//Footballer->GenerateRatingProperties(RatingWeightsTable, StarsAndLevelsTable);
	Footballer->Data.SelectedFieldPosition = NewPosition;
	if(Footballer->Data.LineUpPosition != EFootballerLineUp::Starter)
	{
	Footballer->Data.Rating = Footballer->Data.CalculateFootballerRating(Footballer->Data.DesiredFieldPositions[0]);
	}
	else
	{
	Footballer->Data.Rating = Footballer->Data.CalculateFootballerRating(NewPosition);
	}
	Footballer->OnUpdateRating.Broadcast();
	GenerateRatingProperties();
}

bool UTeam_Deprecated::ChangeFootballerLineUp(UFootballerObject* Footballer, UFootballerObject* FootballerToSwap, EFootballerLineUp NewLineUp)
{
	TArray<UFootballerObject*>* NewLineUpArray = nullptr;

	switch(NewLineUp)
	{
		case EFootballerLineUp::Starter:
			NewLineUpArray = &Starters;
			break;
		case EFootballerLineUp::Substitute:
			NewLineUpArray = &Substitutes;
			break;
		case EFootballerLineUp::Reserve:
			NewLineUpArray = &Reserves;
			break;
		default:
			UE_LOG(LogTemp, Error, TEXT("Detected wrong lineup enum value %d"), NewLineUp);
			return false;
			break;
	}
	//Save index of 2 Chips
	int32 FootballerToSwapIndex = NewLineUpArray->Find(FootballerToSwap);
	int32 FootballerIndex = 0;

	NewLineUpArray->Remove(FootballerToSwap);

	//Remove from previous lineup
	switch(Footballer->Data.LineUpPosition)
	{
		case EFootballerLineUp::Starter:
			FootballerIndex = Starters.Find(Footballer);
			Starters.Remove(Footballer);
			Starters.Insert(FootballerToSwap, FootballerIndex);
			break;
		case EFootballerLineUp::Substitute:
			FootballerIndex = Substitutes.Find(Footballer);
			Substitutes.Remove(Footballer);
			Substitutes.Insert(FootballerToSwap, FootballerIndex);
			break;
		case EFootballerLineUp::Reserve:
			FootballerIndex = Reserves.Find(Footballer);
			Reserves.Remove(Footballer);
			Reserves.Insert(FootballerToSwap, FootballerIndex);
			break;
		default:
			UE_LOG(LogTemp, Error, TEXT("Detected wrong lineup enum value in footballer %d"), Footballer->Data.LineUpPosition);
			return false;
			break;
	}

	FootballerToSwap->Data.LineUpPosition = Footballer->Data.LineUpPosition;
	Footballer->Data.LineUpPosition = NewLineUp;

	NewLineUpArray->Insert(Footballer, FootballerToSwapIndex);

	return true;
}

template<typename T>
float UTeam_Deprecated::GetRatingNumber(const TArray<T>& TeamStarters) const
{
	static_assert(std::is_same<T, UFootballerObject*>() || std::is_same<T, TObjectPtr<UFootballerObject>>());

	float TotalFootballerRating = 0;
	for(const UFootballerObject* FObj : TeamStarters)
	{
		TotalFootballerRating += FObj->Data.Rating.Overall;
	}

	float TeamRating = TotalFootballerRating / MAX_STARTERS;

	return TeamRating;
}

void UTeam_Deprecated::GenerateRatingProperties()
{
	OverallRating = GetRatingNumber(Starters);
	OptimalRating = GetRatingNumber(Starters);
	Level = UUtilsFunctionLibrary::GetRatingLevel(StarsAndLevelsTable, OverallRating);
	RatingStars = UUtilsFunctionLibrary::GetRatingStars(StarsAndLevelsTable, OverallRating, Level);
	OnUpdateTeamRating.Broadcast();
}

float UTeam_Deprecated::GetOptimalRating() const
{
	if(!StartersPositionsTable)
	{
		UE_LOG(LogTemp, Error, TEXT("StartersPositionsTable is null so was imposible to calculate the OptimalRating of the team"));
		return 0;
	}

	TArray<UFootballerObject*> TeamFootballers;
	TArray<UFootballerObject*> OptimalStarters;
	TeamFootballers.Reserve(MAX_STARTERS + MAX_SUBSTITUTES + Reserves.Num());
	TeamFootballers.Append(Starters);
	TeamFootballers.Append(Substitutes);
	TeamFootballers.Append(Reserves);

	TMap<EFieldPosition, TArray<UFootballerObject*>> FootballersByPositions;

	for(UFootballerObject* Footballer : TeamFootballers)
	{
		if(FootballersByPositions.Contains(Footballer->Data.SelectedFieldPosition))
		{
			TArray<UFootballerObject*>* FootballersWithCurrentPosition = &FootballersByPositions[Footballer->Data.SelectedFieldPosition];
			FootballersWithCurrentPosition->Add(Footballer);

			FootballersWithCurrentPosition->Sort([](const UFootballerObject& A, const UFootballerObject& B)
			{
				return A.Data.Rating.Overall < B.Data.Rating.Overall;
			});
		}
		else
		{
			FootballersByPositions.Add(Footballer->Data.SelectedFieldPosition, {Footballer});
		}
	}

	TArray<FName> StartersPositionsNames = StartersPositionsTable->GetRowNames();

	// Use Starters Positions Table to select the minimum viable amount of footballers necessary
	// of each position using the best footballers of the team in each position
	for(FName PositionName : StartersPositionsNames)
	{
		int32 PositionIndex = StaticEnum<EFieldPosition>()->GetValueByName(PositionName);

		if(PositionIndex != INDEX_NONE)
		{
			FTeamPositionsData* StartersPositionRow = StartersPositionsTable->FindRow<FTeamPositionsData>(PositionName, TEXT(__FILE__));

			for(int32 i = 0; i < StartersPositionRow->Min; i++)
			{
				if(FootballersByPositions[EFieldPosition(PositionIndex)].IsValidIndex(i))
				{
					UFootballerObject* SelectedFootballer = FootballersByPositions[EFieldPosition(PositionIndex)].Pop();
					TeamFootballers.RemoveSwap(SelectedFootballer);
					OptimalStarters.Add(SelectedFootballer);
				}
			}
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("Starters Position Table Contains a Row Name that is not equal to any value inside EFieldPosition"));
		}
	}

	/*
	* Order Footballers by rating and try to add them to the recently created starters array
	* using the data table as reference to know the max available of each position
	*/
	TeamFootballers.Sort([](const UFootballerObject& A, const UFootballerObject& B)
	{
		return A.Data.Rating.Overall > B.Data.Rating.Overall;
	});

	for(int32 i = 0; i < TeamFootballers.Num(); i++)
	{
		if(OptimalStarters.Num() >= MAX_STARTERS)
		{
			break;
		}

		TArray<UFootballerObject*> SamePositionFootballers = OptimalStarters.FilterByPredicate([&](const UFootballerObject* StarterFootballer)
		{
			return StarterFootballer->Data.SelectedFieldPosition == TeamFootballers[i]->Data.SelectedFieldPosition;
		});

		FName TeamFootballerPositionName = FName(UEnum::GetDisplayValueAsText(TeamFootballers[i]->Data.SelectedFieldPosition).ToString());
		FTeamPositionsData* StartersPositionRow = StartersPositionsTable->FindRow<FTeamPositionsData>(TeamFootballerPositionName, TEXT(__FILE__));

		if(SamePositionFootballers.Num() < StartersPositionRow->Max)
		{
			OptimalStarters.Add(TeamFootballers[i]);
			TeamFootballers.RemoveAt(i);
			i--;
		}
	}

	float CalculatedOptimalRating = GetRatingNumber(OptimalStarters);

	return CalculatedOptimalRating;
}

uint8 UTeam_Deprecated::GetAvailableTshirtNumber()
{
	TArray<uint8> AvalibleNumbers;
	AvalibleNumbers.Reserve(MAX_TSHIRT_NUMBER);
	for(uint8 i = 0; i < MAX_TSHIRT_NUMBER; ++i)
	{
		if(!TeamSelectedNumbers.Contains(i + 1))
			AvalibleNumbers.Emplace(i + 1);
	}

	checkf(!AvalibleNumbers.IsEmpty(), TEXT("There are not avalible numbers"));

	uint8 SelectedNumber = AvalibleNumbers[FMath::RandRange(0, AvalibleNumbers.Num() - 1)];

	TeamSelectedNumbers.AddUnique(SelectedNumber);

	return SelectedNumber;
}

FTacticValue UTeam_Deprecated::GetTacticValue(ETacticGroup TacticGroupEnum) const
{
	FTacticValue Result;
	Result.Key = ETacticValue::None;

	for(const FTacticGroup& Tactic : TeamTactics)
	{
		if(Tactic.Key == TacticGroupEnum)
		{
			Result = Tactic.Values[Tactic.SelectedIndex];
		}
	}

	return Result;
}

void UTeam_Deprecated::UpdateTacticGroup(ETacticGroup TacticGroup, int32 NewIndex)
{
	for(FTacticGroup& Tactic : TeamTactics)
	{
		if(Tactic.Key == TacticGroup)
		{
			Tactic.SelectedIndex = NewIndex;
		}
	}
}

bool UTeam_Deprecated::HasPositionInCurrentFormation(EFieldPosition Position) const
{
	// TODO Adrian: Catch this when the selected position is updated to avoid iterating through the Starters array each time
	for ( const UFootballerObject* FObj : Starters)
	{
		if ( FObj->GetSelectedFieldPosition() == Position )
		{
			return true;
		}
	}

	return false;
}

void UTeam_Deprecated::ApplyPostMatchEffects(TMap<int32, FPostMatchEffects> PostMatchEffectsByFootballer)
{
	//Starters of the game
	//TODO Adrian Add the subs if necessary
	for (UFootballerObject* FootballerObject : Starters)
	{
		FootballerObject->Data.State.Condition = FMath::Clamp(FootballerObject->Data.State.Condition - PostMatchEffectsByFootballer[FootballerObject->Data.Id].Condition ,0.f, 100.f );
		FootballerObject->Data.State.Morale = FMath::Clamp(FootballerObject->Data.State.Morale + PostMatchEffectsByFootballer[FootballerObject->Data.Id].Morale, 0.f, 100.f);
		FootballerObject->Data.State.Sharpness = FMath::Clamp(FootballerObject->Data.State.Sharpness + PostMatchEffectsByFootballer[FootballerObject->Data.Id].Sharpness, 0.f, 100.f);
		
		TMap<EFootballerAttributes, int32> AttributesToIncrease = PostMatchEffectsByFootballer[FootballerObject->Data.Id].AttributesToIncrease;
		for (const TPair<EFootballerAttributes, int32>& AttributePair : AttributesToIncrease)
		{
			EFootballerAttributes Attribute = AttributePair.Key;
			int32 IncreaseAmount = AttributePair.Value;
			FootballerObject->Data.Attributes[static_cast<int32>(Attribute)] += IncreaseAmount;
		}

	}
}

static bool IsPossibleToFollowMin(const TArray<int32>& MinValues, const int32 TotalPoints)
{
	int32 TotalMinValuesAmount = std::accumulate(MinValues.begin(), MinValues.end(), 0);
	return TotalMinValuesAmount <= TotalPoints;
}

static bool IsPossibleToFollowMax(const TArray<int32>& MaxValues, const int32 TotalPoints)
{
	int32 TotalMaxValuesAmount = std::accumulate(MaxValues.begin(), MaxValues.end(), 0);
	return TotalMaxValuesAmount >= TotalPoints;
}

/*
* The finality of this function is to ensure that the value of the current property is increase while there still exits points
* but that his value respect the max currently available for the property and that it ensure that the minimum value is assigned
* before all the points are spend
*
* TotalAvailablePoints: Total Amount of points to spend
*
* RangeControlPoins : Amount of points available to assign to a property passed his MinPropertyValue
*
*
*/
static int32 EnsurePoints(const int32 MinPropertyValue, const int32 MaxPropertyValue, int32 CurrentPropertyValue, int32& PassMinAvaliblePoints,
						  int32& TotalAvailablePoints)
{
	const int32 InitialPropertyValue = FMath::Max(CurrentPropertyValue, MinPropertyValue);
	//Find a new Max to ensure that the property don't select a value that will spend enough points to prevent another property of his minimum amount
	const int32 UpdatedPropertyMax = FMath::Min(MaxPropertyValue, InitialPropertyValue + PassMinAvaliblePoints);

	//To reduce iterations starting from the min property value ensure that the first pass at least assign the minim required
	const int32 AmountToAdd = FMath::RandRange(MinPropertyValue, UpdatedPropertyMax);
	for(int32 i = 0; i < AmountToAdd; i++)
	{
		if(CurrentPropertyValue >= UpdatedPropertyMax || TotalAvailablePoints <= 0)
			break;

		CurrentPropertyValue++;
		TotalAvailablePoints--;
		//Always that the current property is bigger than the minim value required is necessary to reduce the amount of PassMinAvaliblePoints
		if(CurrentPropertyValue > MinPropertyValue)
			PassMinAvaliblePoints--;
	}
	return CurrentPropertyValue;
}

/*
* The finality of this function is to extract each property value respecting the Min and Max values of a table for an specific amount of points
*
* MinLimits : Custom Min limits in case that the table values are not precise
* MaxLimits : Custom Max limits in case that the table values are not precise
*
*/
template<typename FTableRow>
static TArray<int32> GetTablePropertiesAmounts(const UDataTable* TableToExtractProperties, int32 PointsToSpend, TArray<int32> MinLimits = {}, TArray<int32> MaxLimits = {})
{
	TArray<int32> PropertiesValues;

	if(!TableToExtractProperties)
	{
		UE_LOG(LogTemp, Error, TEXT("The table pointer is null"));
		return PropertiesValues;
	}

	TArray<FName> TableNames = TableToExtractProperties->GetRowNames();
	int32 PropertyNumbers = TableNames.Num();

	int32 InitialMinLimitsLenght = MinLimits.Num();
	int32 InitialMaxLimitsLenght = MaxLimits.Num();

	PropertiesValues.SetNum(PropertyNumbers);

	int32 MinNecesaryPoints = 0;
	int32 PassMinAvaliblePoints = 0;

	TArray<int32> IndexesToTableProperties;

	for(int32 i = 0; i < PropertyNumbers; ++i)
	{
		if(InitialMinLimitsLenght == 0)
		{
			FTableRow* CurrentTableRow = TableToExtractProperties->FindRow<FTableRow>(TableNames[i], __FILE__);
			MinLimits.Add(CurrentTableRow->Min);
		}

		if(InitialMaxLimitsLenght == 0)
		{
			FTableRow* CurrentTableRow = TableToExtractProperties->FindRow<FTableRow>(TableNames[i], __FILE__);
			MaxLimits.Add(CurrentTableRow->Max);
		}

		MinNecesaryPoints += MinLimits[i];
		IndexesToTableProperties.Add(i);
	}

	if(!IsPossibleToFollowMin(MinLimits, PointsToSpend))
	{
		UE_LOG(LogTemp, Error,
			   TEXT("Is impossible to ensure that the MinLimits will be satisfied with the available points to spend check table or the amount of points passed"));
		return PropertiesValues;
	}

	//Points available to add over the minimum to the properties
	PassMinAvaliblePoints = FMath::Clamp(PointsToSpend - MinNecesaryPoints, 0, PointsToSpend);

	//Shuffle to add more randomness at the initial process
	Algo::RandomShuffle(IndexesToTableProperties);

	//Make a first pass where we try to fill all the points but exist the possibility that after this pass there still exist points
	//to expend for this reason is necessary to make a another pass later
	for(int32 i = 0; i < PropertyNumbers; ++i)
	{
		int32 Index = IndexesToTableProperties[i];

		PropertiesValues[Index] = EnsurePoints(MinLimits[Index], MaxLimits[Index], PropertiesValues[Index], PassMinAvaliblePoints, PointsToSpend);
	}

	//In case that there were still points left to add
	Algo::RandomShuffle(IndexesToTableProperties);

	if(IsPossibleToFollowMax(MaxLimits, PointsToSpend))
	{
		while(PointsToSpend > 0)
		{
			for(int32 i = 0; i < PropertyNumbers; i++)
			{
				int32 Index = IndexesToTableProperties[i];
				PropertiesValues[Index] = EnsurePoints(MinLimits[Index], MaxLimits[Index], PropertiesValues[Index], PassMinAvaliblePoints, PointsToSpend);
			}
			Algo::RandomShuffle(IndexesToTableProperties);
		}

	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Is not possible to spend all the points because the max limits are to small"));
	}

	return PropertiesValues;
}

/*Inside a team of footballers tries to find n numbers of footballers with the selected playing positions in case that not finding enough returns false */
static bool FindFootballersWithPosition(int32 NumberToFind, EFieldPosition PlayingPosition, const TArray<UFootballerObject*>& Team, TArray<UFootballerObject*>& Footballers)
{
	for(int32 i = 0; i < NumberToFind; i++)
	{
		bool bFound = false;
		for(UFootballerObject* Footballer : Team)
		{
			if(Footballer->Data.SelectedFieldPosition == PlayingPosition && !Footballers.Contains(Footballer))
			{
				Footballers.Add(Footballer);
				bFound = true;
				break;
			}
		}

		if(!bFound) return false;
	}

	return true;
}

/*Extract from a team of footballers the necessary footballers to complete the formation of one of the data tables */
static void GenerateDefaultStartersLineUp(const UDataTable* ThreeDFormationsTable, const UDataTable* FourDFormationsTable, const UDataTable* FiveDFormationsTable,
										  TArray<UFootballerObject*>& TeamFootballers, TArray<UFootballerObject*>& StartersOutArray, FText& FormationSelected)
{
	bool FormationFound = false;
	int32 Counter = 0;
	while(!FormationFound)
	{
		if(Counter >= 1000)
		{
			UE_LOG(LogTemp, Error, TEXT("GenerateDefaultStartersLineUp has exceded the number of iterations inside the while loop"));
		}

		Counter++;
		FName TeamFormationName;
		TArray<FName> FormationsNames;

		FormationsNames.Append(ThreeDFormationsTable->GetRowNames());
		FormationsNames.Append(FourDFormationsTable->GetRowNames());
		FormationsNames.Append(FiveDFormationsTable->GetRowNames());

		std::default_random_engine RandomGenerator;

		RandomGenerator.seed(FMath::RandRange(0, 1000));

		std::shuffle(FormationsNames.GetData(), FormationsNames.GetData() + FormationsNames.Num(), RandomGenerator);

		TeamFormationName = FormationsNames[0];

		const UDataTable* FormationsTable = nullptr;

		if(ThreeDFormationsTable->GetRowNames().Contains(TeamFormationName))
		{
			FormationsTable = ThreeDFormationsTable;
		}
		else if(FourDFormationsTable->GetRowNames().Contains(TeamFormationName))
		{
			FormationsTable = FourDFormationsTable;
		}
		else if(FiveDFormationsTable->GetRowNames().Contains(TeamFormationName))
		{
			FormationsTable = FiveDFormationsTable;
		}
		else
		{
			//UE_LOG(LogTemp, Error, TEXT("Can't find a table containg the selected named formation %d"), TeamFormationName);
			checkNoEntry();
		}

		FTeamTacticsData* CurrentFormationData = FormationsTable->FindRow<FTeamTacticsData>(TeamFormationName, __FILE__);

		TArray<UFootballerObject*> PossibleStarters;

		//TODO David: Can we do this in a for loop?
		if(!FindFootballersWithPosition(CurrentFormationData->GK, EFieldPosition::GK, TeamFootballers, PossibleStarters)) continue;
		if(!FindFootballersWithPosition(CurrentFormationData->DC, EFieldPosition::DC, TeamFootballers, PossibleStarters)) continue;
		if(!FindFootballersWithPosition(CurrentFormationData->DL, EFieldPosition::DL, TeamFootballers, PossibleStarters)) continue;
		if(!FindFootballersWithPosition(CurrentFormationData->DR, EFieldPosition::DR, TeamFootballers, PossibleStarters)) continue;
		if(!FindFootballersWithPosition(CurrentFormationData->DM, EFieldPosition::DM, TeamFootballers, PossibleStarters)) continue;
		if(!FindFootballersWithPosition(CurrentFormationData->MC, EFieldPosition::MC, TeamFootballers, PossibleStarters)) continue;
		if(!FindFootballersWithPosition(CurrentFormationData->ML, EFieldPosition::ML, TeamFootballers, PossibleStarters)) continue;
		if(!FindFootballersWithPosition(CurrentFormationData->MR, EFieldPosition::MR, TeamFootballers, PossibleStarters)) continue;
		if(!FindFootballersWithPosition(CurrentFormationData->AMC, EFieldPosition::AMC, TeamFootballers, PossibleStarters)) continue;
		if(!FindFootballersWithPosition(CurrentFormationData->AML, EFieldPosition::AML, TeamFootballers, PossibleStarters)) continue;
		if(!FindFootballersWithPosition(CurrentFormationData->AMR, EFieldPosition::AMR, TeamFootballers, PossibleStarters)) continue;
		if(!FindFootballersWithPosition(CurrentFormationData->ST, EFieldPosition::ST, TeamFootballers, PossibleStarters)) continue;

		FormationFound = true;

		FormationSelected = FText::FromName(TeamFormationName);
		for(UFootballerObject* Footballer : PossibleStarters)
		{
			int32 TeamFootballersIndex = TeamFootballers.Find(Footballer);

			UFootballerObject* FootballerToAdd = TeamFootballers[TeamFootballersIndex];
			FootballerToAdd->Data.LineUpPosition = EFootballerLineUp::Starter;
			StartersOutArray.Add(FootballerToAdd);
			TeamFootballers.RemoveAtSwap(TeamFootballersIndex);
		}
	}
}


static void AssignPositions(FFootballerData* Footballer, EFieldPosition Position, const UDataTable* AdjacentPositionsTable, float FootballerAdjacentPositionPercentage)
{
	check(AdjacentPositionsTable);

	Footballer->SelectedFieldPosition = Position;
	Footballer->DesiredFieldPositions.Add(Position);

	if(Position == EFieldPosition::GK)
	{
		return;
	}

	constexpr int32 MAX_TRIES_ASSIGN_POSITION = 3;

	for(int32 i = 1; i < MAX_TRIES_ASSIGN_POSITION; i++)
	{
		// 50 % Change in every try to add an additional position to the footballer
		if(FMath::RandRange(0.f, 1.f) <= FootballerAdjacentPositionPercentage)
		{
			FName StartingPosName = FName(UEnum::GetDisplayValueAsText(Position).ToString());
			TArray<EFieldPosition> AdjacentPositions = AdjacentPositionsTable->FindRow<FAdjacentPositionsData>(StartingPosName, TEXT(__FILE__))->Positions;

			AdjacentPositions = AdjacentPositions.FilterByPredicate([&](EFieldPosition AdjPosition)
			{
				return !Footballer->DesiredFieldPositions.Contains(AdjPosition);
			}
			);

			if(AdjacentPositions.Num() > 0)
			{
				EFieldPosition SelectedPosition = AdjacentPositions[FMath::RandRange(0, AdjacentPositions.Num() - 1)];
				Footballer->DesiredFieldPositions.Add(SelectedPosition);
			}
		}
	}
}

static void AssignRandomRole(FFootballerData* Footballer, const UDataTable* PositionToRolesTable)
{
	check(PositionToRolesTable);
	TArray<EFootballerRole> Roles = UUtilsFunctionLibrary::GetPossibleRoles(PositionToRolesTable, Footballer->SelectedFieldPosition);
	Footballer->Role = Roles[FMath::RandRange(0, Roles.Num() - 1)];
}

static void GeneratePerfomanceProperties(FFootballerData* Footballer, const UDataTable* RatingWeightsTable, float RatingTarget)
{
	//IMPORTANT: The order of the properties must be the same that in the table!
	FName PositionName = FName(UEnum::GetDisplayValueAsText(Footballer->SelectedFieldPosition).ToString());
	TArray<FString> PositionPropertiesWeightsValues = UDataTableFunctionLibrary::GetDataTableColumnAsString(RatingWeightsTable, PositionName);

	//Keeps increasing the properties from 0 until the desired rating is achieved skipping the properties with 0 weight to avoid 
	//having rating in useless properties for the footballer selected position
	float CurrentRating = 0;
	while(FMath::Abs(RatingTarget - CurrentRating) >= 1)
	{
		for(int32 i = 0; i < Footballer->Attributes.Num(); i++)
		{
			float PropertyWeight = FCString::Atof(*PositionPropertiesWeightsValues[i]);
			float TotalPropertiesWeight = FCString::Atof(*PositionPropertiesWeightsValues.Last());

			if(PropertyWeight == 0) continue;

			// The max value used is the desired rating plus an offset to give place a more diversity of values in the every rating range 
			float MaxPropertyValue = FMath::Clamp(RatingTarget * 1.5f, 0, 160) * (PropertyWeight / TotalPropertiesWeight);
			float CurrentPropertyValue = Footballer->Attributes[i] * (PropertyWeight / TotalPropertiesWeight);

			if(CurrentPropertyValue == MaxPropertyValue) continue;

			float MaxRatingAmountToAdd = MaxPropertyValue - CurrentPropertyValue;
			//Gives more weight to lower amounts to reduce the possibility of having a lot of disparity between properties and 
			// to try to give to all properties some kind of value 
			float PropertyRatingAmountToAdd = FMath::Min3(FMath::RandRange(0.f, MaxRatingAmountToAdd), FMath::RandRange(0.f, MaxRatingAmountToAdd), FMath::RandRange(0.f, MaxRatingAmountToAdd));

			//Ensure that the current rating is never bigger that the rating target
			if(CurrentRating + PropertyRatingAmountToAdd > RatingTarget)
			{
				PropertyRatingAmountToAdd -= FMath::Abs(RatingTarget - (CurrentRating + PropertyRatingAmountToAdd));
			}

			Footballer->Attributes[i] += PropertyRatingAmountToAdd / (PropertyWeight / TotalPropertiesWeight);
			CurrentRating += PropertyRatingAmountToAdd;

			if(FMath::Abs(RatingTarget - CurrentRating) < 1) break;
		}
	}
}

static void SetRandomSpecialTrait(FFootballerData* Footballer)
{
	Footballer->SpecialTraitLevel = 1;
	Footballer->TraitPoints = 0;
	Footballer->SpecialTrait = ESpecialTrait(FMath::RandRange(0, static_cast<int32>(ESpecialTrait::MAX_COUNT) - 1));
}

static void GenerateCountryAndName(FFootballerData* Footballer, const UDataTable* NamesByCountryTable, ECountryCode Country)
{
	checkf(NamesByCountryTable, TEXT("Names by Country Table is null when trying to generate names"));

	switch (Country)
	{
		case ECountryCode::ES: Footballer->Nationality = FFootballerData::FCountryCode("esp"); break; 
		case ECountryCode::US: Footballer->Nationality = FFootballerData::FCountryCode("usa"); break; 
		case ECountryCode::GB: Footballer->Nationality = FFootballerData::FCountryCode("gbr"); break;
		case ECountryCode::BR: Footballer->Nationality = FFootballerData::FCountryCode("bra"); break;
	}
	
	Footballer->DisplayName = FFootballerData::FFootballerName(
		FText::FromString(UTeamGeneratorFunctionLibrary::GetRandomName(NamesByCountryTable, Country, Footballer->PhysicalFeatures.Gender)),
		FText::FromString(UTeamGeneratorFunctionLibrary::GetRandomSurname(NamesByCountryTable, Country, Footballer->PhysicalFeatures.Gender))
	);
}

static void GenerateTeamTactics(const FString& PresetsPath, TArray<FTacticGroup>& TeamTactics)
{
	//Get all the presets in the path 
	TArray<UTacticPresetDataAsset*> Presets = UTacticsFunctionLibraryBFL::GetTacticPresetDataAssetFromFolder(PresetsPath);

	//Select one of the presets
	int32 SelectedPresetIndex = FMath::RandRange(0, Presets.Num() - 1);

	TeamTactics.Empty();

	if(Presets.Num() > 0)
	{
		UE_LOG(LogFootball, Display, TEXT("Tactics Preset Loaded = %s"), *Presets[SelectedPresetIndex]->GetTacticPreset().DisplayName.ToString());
		for(const auto& [DataAsset, OverrideIndex] : Presets[SelectedPresetIndex]->GetTacticPreset().OverrideValues)
		{
			FTacticGroup TacticGroupTooAdd;

			TacticGroupTooAdd = DataAsset->GetTacticGroup();
			TacticGroupTooAdd.SelectedIndex = OverrideIndex;

			TeamTactics.Add(TacticGroupTooAdd);
		}
	}
}

void UTeamGeneratorFunctionLibrary::SetTeamGeneratorsToDefaultValues(UGameInstance* InGameInstance)
{
	check(InGameInstance);

	FSoftObjectPath PlayerTeamGeneratorPath = FSoftObjectPath(TEXT("/Script/Football.TeamGeneratorData'/Game/Football/UI/Widgets/Manager/TeamGenerators/DA_PlayerTeamGenerator.DA_PlayerTeamGenerator'"));
	FSoftObjectPath RivalTeamGeneratorPath = FSoftObjectPath(TEXT("/Script/Football.TeamGeneratorData'/Game/Football/UI/Widgets/Manager/TeamGenerators/DA_RivalTeamGenerator.DA_RivalTeamGenerator'"));

	UTeamGeneratorData* PlayerTeamGeneratorDefaults = UAssetManager::GetStreamableManager().LoadSynchronous<UTeamGeneratorData>(PlayerTeamGeneratorPath);
	UTeamGeneratorData* RivalTeamGeneratorDefaults = UAssetManager::GetStreamableManager().LoadSynchronous<UTeamGeneratorData>(RivalTeamGeneratorPath);

	if(ensureAlways(PlayerTeamGeneratorDefaults))
	{
		UFootballGameInstance* GameInstance = Cast<UFootballGameInstance>(InGameInstance);

		GameInstance->SetPlayerTeamGenerator(PlayerTeamGeneratorDefaults->TeamGenerator);
		UAssetManager::GetStreamableManager().Unload(PlayerTeamGeneratorPath);
	}

	if(ensureAlways(RivalTeamGeneratorDefaults))
	{
		UFootballGameInstance* GameInstance = Cast<UFootballGameInstance>(InGameInstance);

		GameInstance->SetRivalTeamGenerator(RivalTeamGeneratorDefaults->TeamGenerator);
		UAssetManager::GetStreamableManager().Unload(RivalTeamGeneratorDefaults);
	}
}

void UTeamGeneratorFunctionLibrary::SortFootballersByFieldPositions(TArray<UFootballerObject*>& TeamFootballers)
{
	TArray<UFootballerObject*> OrderedFootballers;

	for (int32 i = 1; i < static_cast<int32>(EFieldPosition::MAX_COUNT); i++)
	{
		EFieldPosition CurrentFootballerPosition = EFieldPosition(i);

		for (UFootballerObject* Footballer : TeamFootballers)
		{
			if (Footballer->Data.SelectedFieldPosition == CurrentFootballerPosition)
			{
				OrderedFootballers.Add(Footballer);
			}
		}
	}

	TeamFootballers = OrderedFootballers;

}

bool ExtractFormationTextFromTeamTacticDatatable(const TArray<UFootballerObject*>& TeamFootballers, const UDataTable* Datatable, FText& FormationText)
{
	bool FormationFound = false;
	
	for (const FName& FormationName : Datatable->GetRowNames())
	{
		FTeamTacticsData* CurrentFormationData = Datatable->FindRow<FTeamTacticsData>(FormationName, __FILE__);
		TArray<UFootballerObject*> PossibleStarters;

		//TODO David: Can we do this in a for loop?
		if (!FindFootballersWithPosition(CurrentFormationData->GK, EFieldPosition::GK, TeamFootballers, PossibleStarters)) continue;
		if (!FindFootballersWithPosition(CurrentFormationData->DC, EFieldPosition::DC, TeamFootballers, PossibleStarters)) continue;
		if (!FindFootballersWithPosition(CurrentFormationData->DL, EFieldPosition::DL, TeamFootballers, PossibleStarters)) continue;
		if (!FindFootballersWithPosition(CurrentFormationData->DR, EFieldPosition::DR, TeamFootballers, PossibleStarters)) continue;
		if (!FindFootballersWithPosition(CurrentFormationData->DM, EFieldPosition::DM, TeamFootballers, PossibleStarters)) continue;
		if (!FindFootballersWithPosition(CurrentFormationData->MC, EFieldPosition::MC, TeamFootballers, PossibleStarters)) continue;
		if (!FindFootballersWithPosition(CurrentFormationData->ML, EFieldPosition::ML, TeamFootballers, PossibleStarters)) continue;
		if (!FindFootballersWithPosition(CurrentFormationData->MR, EFieldPosition::MR, TeamFootballers, PossibleStarters)) continue;
		if (!FindFootballersWithPosition(CurrentFormationData->AMC, EFieldPosition::AMC, TeamFootballers, PossibleStarters)) continue;
		if (!FindFootballersWithPosition(CurrentFormationData->AML, EFieldPosition::AML, TeamFootballers, PossibleStarters)) continue;
		if (!FindFootballersWithPosition(CurrentFormationData->AMR, EFieldPosition::AMR, TeamFootballers, PossibleStarters)) continue;
		if (!FindFootballersWithPosition(CurrentFormationData->ST, EFieldPosition::ST, TeamFootballers, PossibleStarters)) continue;

		FormationFound = true;
		FormationText = FText::FromName(FormationName);
		break;
	}

	return FormationFound;

}

FText UTeamGeneratorFunctionLibrary::GetTeamFormationText(const TArray<UFootballerObject*>& TeamFootballers, const UDataTable* ThreeDFormationsTable, const UDataTable* FourDFormationsTable, const UDataTable* FiveDFormationsTable)
{
	bool FormationFound = false;
	FText FormationSelected;

	if (ExtractFormationTextFromTeamTacticDatatable(TeamFootballers, ThreeDFormationsTable, FormationSelected))
	{
	}
	else if(ExtractFormationTextFromTeamTacticDatatable(TeamFootballers, FourDFormationsTable, FormationSelected))
	{
	}
	else if(ExtractFormationTextFromTeamTacticDatatable(TeamFootballers, FiveDFormationsTable, FormationSelected))
	{
	}
	else
	{
		FormationSelected = FText::FromString("Custom");
	}

	return FormationSelected;
}

UTeam_Deprecated* UTeamGeneratorFunctionLibrary::GenerateTeamWithGenerator(const FTeamGenerator& GeneratorData)
{
	const int MaxRating = 160;
	const int MinRating = 0;

	UTeam_Deprecated* Team = NewObject<UTeam_Deprecated>();

	if(GeneratorData.bIsRivalTeam)
	{
		Team->Name = FString(TEXT("RIVAL ")) + FString::FromInt(FMath::RandRange(1, 100));

	}
	else
	{
		Team->Name = GeneratorData.TeamName;
	}

	Team->Country = GeneratorData.TeamCountry;

	Team->OverallRating = FMath::RoundToInt(FMath::RandRange(GeneratorData.MinTeamRating, GeneratorData.MaxTeamRating));

	Team->StarsAndLevelsTable = GeneratorData.LevelsAndStarsTable;

	Team->RatingWeightsTable = GeneratorData.RatingWeightsTable;

	Team->StartersPositionsTable = GeneratorData.StartersPositionsTable;

	uint8 Footballers = FMath::RandRange(GeneratorData.MinFootballers, GeneratorData.MaxFootballers);
	/*Starters + Substitutes is always 18*/
	constexpr uint8 StartersSubstitutes = 18;
	uint8 Reservers = Footballers - StartersSubstitutes;

	Team->Starters.SetNum(0);
	Team->Substitutes.SetNum(0);
	Team->Reserves.SetNum(0);

	uint8 SameNationalityFootballers = FMath::RoundToInt(Footballers * FMath::Clamp(GeneratorData.SameCountryPercentage, 0.f, 1.f));
	uint8 SpecialTraitFootballers = FMath::RoundToInt(Footballers * FMath::Clamp(GeneratorData.FootballersSpecialTraitPercentage, 0.f, 1.f));
	uint8 RolesFootballers = FMath::RoundToInt(Footballers * FMath::Clamp(GeneratorData.FootballersRolesPercentage, 0.f, 1.f));

	/*TTuple<int32 Yes,int32 No>*/
	TTuple<uint8, uint8> SameNationalityFootballersCounter = MakeTuple(SameNationalityFootballers, Footballers - SameNationalityFootballers);
	TTuple<uint8, uint8> SpecialTraitsFootballersCounter = MakeTuple(SpecialTraitFootballers, Footballers - SpecialTraitFootballers);
	TTuple<uint8, uint8> RolesFootballersCounter = MakeTuple(RolesFootballers, Footballers - RolesFootballers);

	//Add Tactics to the team 
	const FString DefaultPlayerPresetFolderPath = "/Game/Football/UI/Widgets/SquadScreen/Tactics/Tactics/PlayerDefault";
	const FString PresetFoldersPath = "/Game/Football/UI/Widgets/SquadScreen/Tactics/Tactics/Presets";

	if(GeneratorData.bIsRivalTeam)
	{
		GenerateTeamTactics(PresetFoldersPath, Team->TeamTactics);
	}
	else
	{
		GenerateTeamTactics(DefaultPlayerPresetFolderPath, Team->TeamTactics);
	}


	//Creating Positions Array

	UDataTable* PositionsTable = GeneratorData.TeamFootballersPositionsTable;

	checkf(PositionsTable, TEXT("The DataTable Team Positions is null and can not create the team position array"));

	//Create and array of Team Positions where later they can be extracted to assign at the footballers
	TArray<EFieldPosition> TeamAvaliblePositions;
	TArray<FName> PositionsNames = PositionsTable->GetRowNames();

	TArray<int32> NumberOfPositionsToCreate;
	NumberOfPositionsToCreate = GetTablePropertiesAmounts<FTeamPositionsData>(PositionsTable, Footballers);

	for(int32 i = 0; i < NumberOfPositionsToCreate.Num(); i++)
	{
		for(int32 j = 0; j < NumberOfPositionsToCreate[i]; j++)
		{
			TeamAvaliblePositions.Add(EFieldPosition(i + 1));
		}
	}


	//Find ratings of footballers that gives the desired rating of the team
	//Use variance to offset the ratings and accumulate the offset for the last rating to give more disparity 
	TArray<int32> TeamAvalibleRatings;
	int32 AcumulatedOffset = 0;

	for(int32 i = 0; i < Footballers; i++)
	{
		int32 CurrentOffset = FMath::RandRange(-GeneratorData.FootballersRatingVariance, GeneratorData.FootballersRatingVariance);
		if(Team->OverallRating + CurrentOffset > MaxRating)
		{
			CurrentOffset = CurrentOffset - ((Team->OverallRating + CurrentOffset) - MaxRating);
		}
		else if(Team->OverallRating + CurrentOffset < MinRating)
		{
			CurrentOffset = CurrentOffset + FMath::Abs(Team->OverallRating + CurrentOffset);
		}

		TeamAvalibleRatings.Add(Team->OverallRating + CurrentOffset);
		AcumulatedOffset += CurrentOffset;
	}

	//Distribute the accumulated offset between the footballers
	while(FMath::Abs(AcumulatedOffset) > 0)
	{
		for(int32 i = 0; i < Footballers; i++)
		{
			if(TeamAvalibleRatings[i] != MinRating && TeamAvalibleRatings[i] != MaxRating)
			{
				TeamAvalibleRatings[i] -= 1 * FMath::Sign(AcumulatedOffset);
				AcumulatedOffset -= 1 * FMath::Sign(AcumulatedOffset);
			}
		}
	}

	int32 AllFootballersRatings = 0;
	for(int32 Rating : TeamAvalibleRatings)
	{
		AllFootballersRatings += Rating;
	}

	int32 AchivedRating = AllFootballersRatings / TeamAvalibleRatings.Num();

	checkf(AchivedRating == Team->OverallRating, TEXT("The Ratings of the footballers dosen't match the rating of the team"));
	checkf(TeamAvalibleRatings.Num() == Footballers, TEXT("There are not enough ratings to continue check TeamAvalibleRatings"));
	checkf(TeamAvaliblePositions.Num() == Footballers, TEXT("There are not enough positions to continue check NumberOfPostionsToCreate"));


	//Initialize all information relevant to a footballer
	/*
	* 1 Footballer Position and Role
	* 2 Footballer Performance Attributes
	* 3 Special Traits
	* 4 General Information
	* 5 Physical Features
	* 6 State
	* 7 Team Dynamics
	* 8 Contract
	* 9 History/Stats
	* 10 Footballer Rating
	*/

	TArray<UFootballerObject*> TeamFootballers;

	for(int32 i = 0; i < Footballers; i++)
	{
		//TODO David: Make a Footballers Factory object, think about the proper outer for those
		UFootballerObject* CurrentFootballer = NewObject<UFootballerObject>();

		//Next gen id generator ;)
		CurrentFootballer->Data.Id = i + 1;

		// 1 Position/Role
		AssignPositions(&CurrentFootballer->Data, TeamAvaliblePositions[i], GeneratorData.AdjacentPositionsTable, GeneratorData.FootballersAdjacentPositionsPercentage);

		if(TryTrueYesNoCounter(&RolesFootballersCounter))
		{
			AssignRandomRole(&CurrentFootballer->Data, GeneratorData.FootballersRolesTable);
		}
		else
		{
			CurrentFootballer->Data.Role = EFootballerRole::None;
		}

		// 2 Performance Attributes

		GeneratePerfomanceProperties(&CurrentFootballer->Data, GeneratorData.RatingWeightsTable, TeamAvalibleRatings[i]);

		// 3 Special Trait
		if(TryTrueYesNoCounter(&SpecialTraitsFootballersCounter))
		{
			SetRandomSpecialTrait(&CurrentFootballer->Data);
		}

		// 4 General Information
		CurrentFootballer->Data.Number = Team->GetAvailableTshirtNumber();
		//TODO Sergio This value should be initialized ?
		CurrentFootballer->Data.AgeOfRetirement = FMath::RandRange(35, 40);

		//Gender must be set before Generating the name and country of the footballer
		CurrentFootballer->Data.PhysicalFeatures.Gender = EFootballerGender::Male;

		bool IsSameNationality = TryTrueYesNoCounter(&SameNationalityFootballersCounter);
		if(IsSameNationality)
		{
			GenerateCountryAndName(&CurrentFootballer->Data, GeneratorData.NamesByCountryTable, Team->Country);
		}
		else
		{
			uint8 Index = FMath::RandRange(0, (uint8) ECountryCode::MAX - 1);
			while(Index == (uint8) Team->Country)
			{
				Index = FMath::RandRange(0, (uint8) ECountryCode::MAX - 1);
			}
			GenerateCountryAndName(&CurrentFootballer->Data, GeneratorData.NamesByCountryTable, ECountryCode(Index));
		}

		CurrentFootballer->Data.Age = FMath::RandRange(GeneratorData.MinFootballersAge, GeneratorData.MaxFootballersAge);
		CurrentFootballer->Data.CharacterType = ECharacterType::RegularCharacter;
		CurrentFootballer->Data.CharacterTypePriority = 0;

		// 5 Physical Features
		CurrentFootballer->Data.PhysicalFeatures.Height = FMath::RandRange(GeneratorData.MinFootballersHeight, GeneratorData.MaxFootballersHeight);
		CurrentFootballer->Data.PhysicalFeatures.Weight = FMath::RandRange(GeneratorData.MinFootballersWeight, GeneratorData.MaxFootballersWeight);
		CurrentFootballer->Data.PhysicalFeatures.PreferredFoot = EPreferredFootType(FMath::RandRange(0, (uint8) EPreferredFootType::MAX_COUNT - 1));
		//TODO Appearance ?????????		

		// 6 State
		CurrentFootballer->Data.State.Condition = 100;
		CurrentFootballer->Data.State.Morale = FMath::RandRange(30, 100);
		CurrentFootballer->Data.State.Sharpness = FMath::RandRange(30, 100);
		CurrentFootballer->Data.State.PenaltyCards[0] = 0;
		CurrentFootballer->Data.State.PenaltyCards[1] = 0;
		CurrentFootballer->Data.State.Injured = false;

		// 7 Team Dynamics
		CurrentFootballer->Data.TeamDynamics.AffinityWithManager = FMath::RandRange(2, 6);
		CurrentFootballer->Data.TeamDynamics.AlignmentWithTeam = FMath::RandRange(5, 8);
		CurrentFootballer->Data.TeamDynamics.PersonalityType = EPersonalityType(FMath::RandRange(1, static_cast<int32>(EPersonalityType::MAX_COUNT) - 1));

		// 8 Contract
		CurrentFootballer->Data.Contract.StartSeason = FDateTime::Now();
		CurrentFootballer->Data.Contract.ExpirySeason = FDateTime::Now() + FTimespan::FromDays(FMath::RandRange(365, 3650));
		CurrentFootballer->Data.Contract.Status = EContractStatus::Active;
		CurrentFootballer->Data.Contract.Salary = FMath::RandRange(2000, 10000000);
		CurrentFootballer->Data.Contract.MarketValue = FMath::RandRange(50000, 100000000);
		CurrentFootballer->Data.Contract.LastUpdateMarketValue = FDateTime::Now();

		// 9 History/Stats

		// 10 Footballer Rating
		CurrentFootballer->Data.Rating = CurrentFootballer->Data.CalculateFootballerRating(CurrentFootballer->Data.SelectedFieldPosition);
		//CurrentFootballer->GenerateRatingProperties(GeneratorData.RatingWeightsTable, GeneratorData.LevelsAndStarsTable);

		TeamFootballers.Add(CurrentFootballer);
	}

	TeamFootballers.Sort([](const UFootballerObject& A, const UFootballerObject& B)
	{
		return A.Data.Rating.Overall < B.Data.Rating.Overall;
	});


	GenerateDefaultStartersLineUp(GeneratorData.ThreeDFormationsTable, GeneratorData.FourDFormationsTable, GeneratorData.FiveDFormationsTable, TeamFootballers, Team->Starters, Team->FormationSelectedText);

	for(int32 i = 0; i < MAX_SUBSTITUTES; i++)
	{
		UFootballerObject* SelectedFootballer = TeamFootballers.Pop(true);
		SelectedFootballer->Data.LineUpPosition = EFootballerLineUp::Substitute;
		Team->Substitutes.Add(SelectedFootballer);
	}

	for(int32 i = 0; i < Reservers; ++i)
	{
		UFootballerObject* SelectedFootballer = TeamFootballers.Pop(true);
		SelectedFootballer->Data.LineUpPosition = EFootballerLineUp::Reserve;
		Team->Reserves.Add(SelectedFootballer);
	}

	Team->GenerateRatingProperties();

	UTeamGeneratorFunctionLibrary::SortFootballersByFieldPositions(Team->Starters);
	UTeamGeneratorFunctionLibrary::SortFootballersByFieldPositions(Team->Substitutes);
	UTeamGeneratorFunctionLibrary::SortFootballersByFieldPositions(Team->Reserves);

	return Team;
}

bool UTeamGeneratorFunctionLibrary::TryTrueYesNoCounter(TTuple<uint8, uint8>* Counter)
{
	bool Result = true;


	//Randomly select a value of the tuple to try to extract the value
	if(FMath::RandRange(0.0f, 1.0f) > 0.5f)
	{
		if(Counter->Value > 0)
		{
			--Counter->Value;
			Result = false;
		}
		else
		{
			--Counter->Key;
			Result = true;
		}
	}
	else
	{
		if(Counter->Key > 0)
		{
			--Counter->Key;
			Result = true;
		}
		else
		{
			--Counter->Value;
			Result = false;
		}
	}

	return Result;
}

static const FFotballerNamesByCountryData* GetRandomRow(const UDataTable* NamesByCountryTable, ECountryCode CountryCode, EFootballerGender Gender)
{
	TArray<FName> RowIndentifiers = NamesByCountryTable->GetRowNames();
	TArray<FFotballerNamesByCountryData*> CountryNameRows;

	for(FName RowIdentifier : RowIndentifiers)
	{
		FFotballerNamesByCountryData* CurrentRow = NamesByCountryTable->FindRow<FFotballerNamesByCountryData>(RowIdentifier, __FILE__);
		if(CurrentRow->CountryCode == CountryCode && CurrentRow->Gender == Gender)
		{
			CountryNameRows.Add(CurrentRow);
		}
	}

	checkf(CountryNameRows.Num() > 0, TEXT("There are no names for the selected country code"));

	int32 Index = FMath::RandRange(0, CountryNameRows.Num() - 1);

	return CountryNameRows[Index];
}

FString UTeamGeneratorFunctionLibrary::GetRandomName(const UDataTable* NamesByCountryTable, ECountryCode CountryCode, EFootballerGender Gender)
{
	return GetRandomRow(NamesByCountryTable, CountryCode, Gender)->FootballerName;
}

FString UTeamGeneratorFunctionLibrary::GetRandomSurname(const UDataTable* NamesByCountryTable, ECountryCode CountryCode, EFootballerGender Gender)
{
	return GetRandomRow(NamesByCountryTable, CountryCode, Gender)->FootballerSurname;
}

template<typename TEnum>
static bool IsNameInTheSameOrderThatEnum(const TArray<FName>& RowNames, const FName NameToCheck, FString& ErrorMessage)
{
	int32 NameToCheckIndex = RowNames.Find(NameToCheck);
	int32 CorrectIndexEnum = StaticEnum<TEnum>()->GetIndexByNameString(NameToCheck.ToString(), EGetByNameFlags::CaseSensitive);

	if(CorrectIndexEnum == INDEX_NONE)
	{
		ErrorMessage = FString::Format(
			TEXT("The position with name {0} does not exit in the enum {1} ,CHANGE IT !!"),
			{NameToCheck.ToString(), StaticEnum<TEnum>()->GetName()});
		return false;
	}

	//Enums start with the value of 1 for that reason we add 1 to the index that we have find
	if(UEnum::GetDisplayValueAsText(TEnum(NameToCheckIndex + 1)).ToString() != NameToCheck.ToString())
	{
		ErrorMessage = FString::Format(
			TEXT("The position {0} is in number {1} but should be in {2} to match the Enum {3} ,CHANGE IT !!"),
			{NameToCheck.ToString(), NameToCheckIndex + 1, CorrectIndexEnum , StaticEnum<TEnum>()->GetName()});
		return false;
	}

	return true;
}

template<typename TEnum>
static bool DoesNameExistsInEnum(const FName Name, FString& ErrorMessage)
{
	if(StaticEnum<TEnum>()->GetValueByName(Name) == INDEX_NONE)
	{
		ErrorMessage = FString::Format(TEXT("The name {0} does not exit in the struct {1} check Names Column"),
									   {Name.ToString(), StaticEnum<TEnum>()->GetName()});
		return false;
	}

	return true;
}

template<typename T>
static void EnsureMinValueIsLowerThanMax(T& Min, T& Max)
{
	T CurrentMin = Min;
	T CurrentMax = Max;

	if(CurrentMin > CurrentMax)
	{
		Max = CurrentMin;
		Min = CurrentMax;
		UE_LOG(LogTemp, Error, TEXT("Min value must be equal or less than Max value"));
	}
}

void FTeamPositionsData::OnDataTableChanged(const UDataTable* InDataTable, const FName InRowName)
{
	FTeamPositionsData* CurrentRow = InDataTable->FindRow<FTeamPositionsData>(InRowName, TEXT(__FILE__));
	EnsureMinValueIsLowerThanMax(CurrentRow->Min, CurrentRow->Max);
}

void FTeamPositionsData::OnPostDataImport(const UDataTable* InDataTable, const FName InRowName, TArray<FString>& OutCollectedImportProblems)
{
	FString Message;
	if(!IsNameInTheSameOrderThatEnum<EFieldPosition>(InDataTable->GetRowNames(), InRowName, Message))
	{
		OutCollectedImportProblems.Add(Message);
	}
}

void FAdjacentPositionsData::OnPostDataImport(const UDataTable* InDataTable, const FName InRowName, TArray<FString>& OutCollectedImportProblems)
{
	FString Message;
	if(!IsNameInTheSameOrderThatEnum<EFieldPosition>(InDataTable->GetRowNames(), InRowName, Message))
	{
		OutCollectedImportProblems.Add(Message);
	}

	TArray<FString> PosStrings;
	InDataTable->FindRow<FAdjacentPositionsData>(InRowName, TEXT(""))->PositionsString.ParseIntoArray(PosStrings, TEXT(","), true);

	for(FString PosString : PosStrings)
	{
		int32 EnumIndex = StaticEnum<EFieldPosition>()->GetValueByNameString(PosString, EGetByNameFlags::CaseSensitive);
		Positions.Add(EFieldPosition(EnumIndex));
	}
}

void FStarsAndLevelsData::OnPostDataImport(const UDataTable* InDataTable, const FName InRowName, TArray<FString>& OutCollectedImportProblems)
{
	FString Message;
	if(!DoesNameExistsInEnum<ERatingLevel>(InRowName, Message))
	{
		OutCollectedImportProblems.Add(Message);
	}
}
