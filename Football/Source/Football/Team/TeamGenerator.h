#pragma once

#include <Engine/DataAsset.h>
#include <CoreMinimal.h>

#include <Football/CoreClasses/DataStructures/Footballer.h>
#include <Football/CoreClasses/FootballerObject.h>
#include <Football/CoreClasses/DataStructures/Tactics.h>
#include "Football/Match/MatchDefs.h"

#include "TeamGenerator.generated.h"

class UFootballer_Deprecated;
class USetPieceData;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnChangedLineUp);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnUpdateTeamRating);

constexpr uint8 MIN_TSHIRT_NUMBER = 1;
constexpr uint8 MAX_TSHIRT_NUMBER = 99;

UCLASS(BlueprintType)
class UTeam_Deprecated : public UObject
{
	GENERATED_BODY()

public:
	UTeam_Deprecated();

	UFUNCTION(BlueprintCallable)
	const TArray<FString> GetTacticsValuesDebug() const;

	UFUNCTION(BlueprintCallable)
	void ChangeFootballerPosition(UFootballerObject* Footballer, EFieldPosition NewPosition);

	UFUNCTION(BlueprintCallable)
	bool ChangeFootballerLineUp(UFootballerObject* Footballer, UFootballerObject* FootballerToSwap, EFootballerLineUp NewLineUp);

	//T must be a UFootballerObject or a reference wrapper to it
	template<typename T>
	float GetRatingNumber(const TArray<T>& TeamStarters) const;

	void GenerateRatingProperties();

	float GetOptimalRating() const;

	uint8 GetAvailableTshirtNumber();

	FTacticValue GetTacticValue(ETacticGroup TacticGroupEnum) const;

	void UpdateTacticGroup(ETacticGroup TacticGroupEnum, int32 NewIndex);

	bool HasPositionInCurrentFormation(EFieldPosition Position) const;

	void ApplyPostMatchEffects(TMap<int32, FPostMatchEffects> PostMatchEffectsByFootballer);

	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FOnChangedLineUp ChangedLineUp;

	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FOnUpdateTeamRating OnUpdateTeamRating;
	
	UPROPERTY(BlueprintReadWrite)
	FString Name;

	UPROPERTY(BlueprintReadWrite)
	FText FormationSelectedText;

	UPROPERTY(BlueprintReadWrite)
	float OverallRating = 20.f;

	UPROPERTY(BlueprintReadWrite)
	float OptimalRating = 20.f;

	UPROPERTY(BlueprintReadWrite)
	float RatingStars = 0.0f;

	UPROPERTY(BlueprintReadWrite)
	bool bIsCustomFormation = false;

	UPROPERTY(BlueprintReadWrite)
	ERatingLevel Level = ERatingLevel::Bronze;

	UPROPERTY(BlueprintReadWrite)
	ECountryCode Country = ECountryCode::US;

	//TODO David: use TStaticArray. Remove UPROPOERTY
	UPROPERTY(BlueprintReadOnly)
	TArray<UFootballerObject*> Starters;

	UPROPERTY(BlueprintReadOnly)
	TArray<UFootballerObject*> Substitutes;

	UPROPERTY(BlueprintReadOnly)
	TArray<UFootballerObject*> Reserves;

	UPROPERTY(BlueprintReadWrite)
	TArray<USetPieceData*> SetPiecesData;

	UPROPERTY(BlueprintReadWrite)
	TArray<uint8> TeamSelectedNumbers;

	UPROPERTY(BlueprintReadWrite)
	UDataTable* StarsAndLevelsTable;

	UPROPERTY(BlueprintReadWrite)
	UDataTable* RatingWeightsTable;

	UPROPERTY(BlueprintReadWrite)
	UDataTable* StartersPositionsTable;

	UPROPERTY(BlueprintReadWrite)
	TArray<FTacticGroup> TeamTactics;
};

struct FSubstitution
{
	UFootballer_Deprecated* In;
	UFootballer_Deprecated* Out;
};

USTRUCT(BlueprintType)
struct FFotballerNamesByCountryData : public FTableRowBase
{
	GENERATED_BODY();
	
	UPROPERTY(BlueprintReadOnly,EditDefaultsOnly)
	FString FootballerName;
	UPROPERTY(BlueprintReadOnly,EditDefaultsOnly)
	FString FootballerSurname;
	UPROPERTY(BlueprintReadOnly,EditDefaultsOnly)
	EFootballerGender Gender = EFootballerGender::Male;
	UPROPERTY(BlueprintReadOnly,EditDefaultsOnly)
	ECountryCode CountryCode = ECountryCode::US;
};

/*Structure used to decide the max and min number of players with a specific position like Goalkeeper or Striker */
USTRUCT(BlueprintType)
struct FTeamPositionsData : public FTableRowBase 
{
	GENERATED_BODY();

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	int32 Min = 0;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	int32 Max = 0;

	virtual void OnDataTableChanged(const UDataTable* InDataTable, const FName InRowName) override;

	virtual void OnPostDataImport(const UDataTable* InDataTable, const FName InRowName, TArray<FString>& OutCollectedImportProblems) override;
};

USTRUCT(BlueprintType)
struct FAdjacentPositionsData : public FTableRowBase
{
	GENERATED_BODY()

	//Name 
	//EFotballerPlayingPosition
	
	UPROPERTY(BlueprintReadOnly,EditDefaultsOnly)
	FString PositionsString;

	UPROPERTY(BlueprintReadOnly,EditDefaultsOnly, meta=(DataTableImportOptional))
	TArray<EFieldPosition> Positions;

	virtual void OnPostDataImport(const UDataTable* InDataTable, const FName InRowName, TArray<FString>& OutCollectedImportProblems) override;
};

USTRUCT(BlueprintType)
struct FRatingsWeightsData : public FTableRowBase
{
	GENERATED_BODY();

	//Name 
	//Properties Names

	UPROPERTY(BlueprintReadWrite,EditDefaultsOnly)
	float GK = 0;
	UPROPERTY(BlueprintReadWrite,EditDefaultsOnly)
	float DL = 0;
	UPROPERTY(BlueprintReadWrite,EditDefaultsOnly)
	float DC = 0;
	UPROPERTY(BlueprintReadWrite,EditDefaultsOnly)
	float DR = 0;
	UPROPERTY(BlueprintReadWrite,EditDefaultsOnly)
	float DM = 0;
	UPROPERTY(BlueprintReadWrite,EditDefaultsOnly)
	float ML = 0;
	UPROPERTY(BlueprintReadWrite,EditDefaultsOnly)
	float MC = 0;
	UPROPERTY(BlueprintReadWrite,EditDefaultsOnly)
	float MR = 0;
	UPROPERTY(BlueprintReadWrite,EditDefaultsOnly)
	float AML = 0;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	float AMC = 0;
	UPROPERTY(BlueprintReadWrite,EditDefaultsOnly)
	float AMR = 0;
	UPROPERTY(BlueprintReadWrite,EditDefaultsOnly)
	float ST = 0;	
};

USTRUCT(BlueprintType)
struct FStarsAndLevelsData : public FTableRowBase
{
	GENERATED_BODY();

	//Name is a EFootballerLevel

	UPROPERTY(BlueprintReadWrite,EditDefaultsOnly)
	float MinRating = 0;

	UPROPERTY(BlueprintReadWrite,EditDefaultsOnly)
	float MaxRating = 0;

	UPROPERTY(BlueprintReadWrite,EditDefaultsOnly)
	float StarCost = 0;

	void OnPostDataImport(const UDataTable* InDataTable, const FName InRowName, TArray<FString>& OutCollectedImportProblems) override;
};


USTRUCT(Blueprintable)
struct FTeamGenerator 
{
	GENERATED_BODY();

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Configuration")
	bool bIsRivalTeam = false;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, meta=(EditCondition="!bIsRivalTeam"), Category = "Configuration")
	FString TeamName;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Configuration")
	ECountryCode TeamCountry = ECountryCode::US;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Configuration")
	float MinTeamRating = 30.f;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Configuration")
	float MaxTeamRating = 50.f;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Configuration")
	float FootballersRatingVariance = 10.0f;
	
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Configuration/Footballers", meta = (Tooltip = "Minimun Number of Footballers for the team"))
	uint8 MinFootballers = 22;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Configuration/Footballers", meta = (Tooltip = "Maximum Number of Footballers for the team"))
	uint8 MaxFootballers = 24;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Configuration/Footballers", meta = (Tooltip = "Minum Age of Footballers for the team"))
	uint8 MinFootballersAge = 18;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Configuration/Footballers", meta = (Tooltip = "Maximum Age of Footballers for the team"))
	uint8 MaxFootballersAge = 31;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Configuration/Footballers", meta = (Tooltip = "Minum Height of Footballers for the team"))
	uint8 MinFootballersHeight = 165;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Configuration/Footballers", meta = (Tooltip = "Maximum Height of Footballers for the team"))
	uint8 MaxFootballersHeight = 200;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Configuration/Footballers", meta = (Tooltip = "Minum Weight of Footballers for the team"))
	uint8 MinFootballersWeight = 65;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Configuration/Footballers", meta = (Tooltip = "Maximum Weight of Footballers for the team"))
	uint8 MaxFootballersWeight = 93;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Configuration/Footballers", meta = (Tooltip = "Percentage of Footballers that will have the same country that the team",
		ClampMin = 0.0f, ClampMax = 1.0f))
	float SameCountryPercentage = 0.8f;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Configuration/Footballers", meta = (Tooltip = "Percentage of Footballers that will have a role assign",
		ClampMin = 0.0f, ClampMax = 1.0f))
	float FootballersRolesPercentage = 0.5f;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Configuration/Footballers", meta = (Tooltip = "Probability to Add an aditional Adjacent Position to each Footballer",
		ClampMin = 0.0f, ClampMax = 1.0f))
	float FootballersAdjacentPositionsPercentage = 0.5f;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Configuration/Footballers", meta = (Tooltip = "Percentage of Footballers that will have a special trait assign",
		ClampMin = 0.0f, ClampMax = 1.0f))
	float FootballersSpecialTraitPercentage = 1.f;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, meta = (RequiredAssetDataTags = 
	"RowStructure=/Script/Football.TeamPositionsData"))
	UDataTable* TeamFootballersPositionsTable = nullptr;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, meta = (RequiredAssetDataTags =
		"RowStructure=/Script/Football.PlayingPositionToRoleData"));
	UDataTable* FootballersRolesTable = nullptr;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, meta = (RequiredAssetDataTags =
		"RowStructure=/Script/Football.AdjacentPositionsData"))
	UDataTable* AdjacentPositionsTable = nullptr;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, meta = (RequiredAssetDataTags =
		"RowStructure=/Script/Football.StarsAndLevelsData"))
	UDataTable* LevelsAndStarsTable = nullptr;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, meta = (RequiredAssetDataTags =
		"RowStructure=/Script/Football.RatingsWeightsData"))
	UDataTable* RatingWeightsTable = nullptr;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, meta = (RequiredAssetDataTags =
		"RowStructure=/Script/Football.FotballerNamesByCountryData"));
	UDataTable* NamesByCountryTable = nullptr;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, meta = (RequiredAssetDataTags =
		"RowStructure=/Script/Football.TeamPositionsData"));
	UDataTable* StartersPositionsTable = nullptr;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, meta = (RequiredAssetDataTags =
		"RowStructure=/Script/Football.TeamTacticsData"));
	UDataTable* ThreeDFormationsTable = nullptr;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, meta = (RequiredAssetDataTags =
		"RowStructure=/Script/Football.TeamTacticsData"));
	UDataTable* FourDFormationsTable = nullptr;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, meta = (RequiredAssetDataTags =
		"RowStructure=/Script/Football.TeamTacticsData"));
	UDataTable* FiveDFormationsTable = nullptr;
};

UCLASS(BlueprintType)
class FOOTBALL_API UTeamGeneratorData : public UDataAsset
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Configuration")
	FTeamGenerator TeamGenerator;
};

/**
* Function library that will hold function related to team generation
*/
UCLASS()
class UTeamGeneratorFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	
	UFUNCTION(BlueprintCallable)
	static void SetTeamGeneratorsToDefaultValues(UGameInstance* InGameInstance);

	UFUNCTION(BlueprintCallable)
	static void SortFootballersByFieldPositions(TArray<UFootballerObject*>& TeamFootballers); 

	UFUNCTION(BlueprintCallable)
	static FText GetTeamFormationText(const TArray<UFootballerObject*>& TeamFootballers, const UDataTable* ThreeDFormationsTable, const UDataTable* FourDFormationsTable, const UDataTable* FiveDFormationsTable);

	//Generate a team with where all the team configuration data is inside the generator object
	static UTeam_Deprecated* GenerateTeamWithGenerator(const FTeamGenerator& GeneratorData);

	//Try to get a boolean value from a tuple containing an specific amounts of True and False values
	//In each try if the selected value is a True and the number is greater than 0 return true else return false
	//in case that the selected value is a False if the number is greater than 0 return false else return true. 
	//If Both are 0 return true
	static bool TryTrueYesNoCounter(TTuple<uint8, uint8>* Counter);

	static FString GetRandomName(const UDataTable* NamesByCountryTable, ECountryCode CountryCode, EFootballerGender Gender);

	static FString GetRandomSurname(const UDataTable* NamesByCountryTable, ECountryCode CountryCode, EFootballerGender Gender);
};