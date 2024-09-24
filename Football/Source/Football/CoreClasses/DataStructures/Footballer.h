// Copyright, 2023, by NGD Studios AB. All rights reserved.

#pragma once

#include <CoreMinimal.h>

#include <array>
#include <Football/Data/Configurations/ISO316612.h>

/**
 * List of all footballer's attributes
 */
UENUM(BlueprintType)
enum class EFootballerAttributes : uint8
{
	Tackling,
	Marking,
	Heading,
	Positioning,
	ShortPassing,
	LongPassing,
	Dribbling,
	Shooting,
	Finishing,
	Control,
	Reflexes,
	Anticipation,
	RushingOut,
	AerialPlay,
	Handling,
	Reach,
	Passing,
	Throwing,
	Kicking,
	OneOnOnes,
	Speed,
	Fitness,
	Strength,
	Agility,
	JumpReach,
	Creativity,
	Discipline,
	Teamwork,
	Sacrifice,
	Aggression,

	MAX_COUNT
};




/** Color of medal  */
UENUM(BlueprintType)
enum class ERatingLevel : uint8
{
	Bronze,
	Silver,
	Gold,
	Platinum,

	MAX_COUNT
};

UENUM(BlueprintType)
enum class EFootballerGender : uint8 
{
	Other,
	Male,
	Female,
};

/** Represents the available positions for a footballer on the field */
UENUM(BlueprintType)
enum class EFieldPosition : uint8
{
	None,

	GK,			/*< GoalKeeper					*/
	DL,			/*< Left Defender				*/
	DC,			/*< Centre Defender				*/
	DR,			/*< Right Defender				*/
	DM,			/*< Defensive Midfielder		*/
	ML,			/*< Left Midfielder				*/
	MC,			/*< Centre Midfielder			*/
	MR,			/*< Right Midfielder			*/
	AML,		/*< Attacking Midfield Left		*/
	AMC,		/*< Attacking Midfield Centre	*/
	AMR,		/*< Attacking Midfield Right	*/
	ST,			/*< Striker						*/

	MAX_COUNT UMETA(Hidden)
};
ENUM_RANGE_BY_COUNT(EFieldPosition, EFieldPosition::MAX_COUNT);

/** Depending on the Field position, every footballer can have a different playing role */
UENUM(BlueprintType)
enum class EFootballerRole : uint8
{
	None,
	
	SweeperKeeper,
	BallPlayingGK,
	NoNonsenseDC,
	BallPlayingDC,
	Libero,
	FullBack,
	WingBack,
	BallWinningMidfielder,
	HalfBack,
	Anchor,
	DeepLyingPlaymaker,
	Regista,
	Mezzala,
	RoamingPlaymaker,
	BoxToBoxMidfielder,
	Carrilero,
	WidePlaymaker,
	DefensiveWinger,
	WideMidfielder,
	ShadowStriker,
	AdvancedPlaymaker,
	Trequartista,
	Enganche,
	InvertedWinger,
	InsideForward,
	Winger,
	DeepLyingForward,
	PressingForward,
	CompleteForward,
	TargetMan,
	FalseNine,
	Poacher,
	SecondStriker
};

/** Every footballer have one special trait assigned upon creation */
UENUM(BlueprintType)
enum class ESpecialTrait : uint8
{
	ComebackSpecialist,
	CreativeGenius,
	HighPerformer,
	MasterTactician,
	Maverick,
	Peacemaker,
	SetPieceSpecialist,
	TeamLeader,
	UnshakeableMind,

	MAX_COUNT UMETA(Hidden)
};

UENUM(BlueprintType)
enum class EPreferredFootType : uint8
{
	Both,
	Left,
	Right,

	MAX_COUNT UMETA(Hidden)
};

UENUM(BlueprintType)
enum class ECharacterType : uint8
{
	RegularCharacter,
	CaptainCharacter,
	ViceCaptainCharacter
};

UENUM(BlueprintType)
enum class EPersonalityType : uint8
{
	None,

	Charismatic,
	Confident,
	Caretaker,
	Analyst,
	Introvert,
	Willful,

	MAX_COUNT UMETA(Hidden)
};

UENUM(BlueprintType)
enum class EFootballerLineUp : uint8
{
	Starter,
	Substitute,
	Reserve
};

UENUM(BlueprintType)
enum class ERelationshipType : uint8
{
	Affinity,
	Rivalry
};

UENUM(BlueprintType)
enum class EContractStatus : uint8
{
	Active,
	NeedsRenewal,
	OnTransferList,
	Finished
};

namespace Footballer
{
	/**
	 * Kind of admonitions cards
	 */
	enum EPenaltyCardType : int32
	{
		Yellow,
		Red,

		MAX_COUNT
	};

	enum EMorale : uint8
	{
		VeryHappy,
		Happy,
		Normal,
		Sad,
		VerySad
	};
}

struct FOOTBALL_API FFootballerAppearance
{
	USkeletalMesh* BodyMesh {};
	USkeletalMesh* HeadMesh {};
	UMaterial* BodyMaterial {};
	UMaterial* HeadMaterial {};

	enum EFootballerBlendshape : int32
	{
		Eyes,
		Jaw,

		MAX_COUNT
	};
	
	using FBlendshapes = std::array<float, MAX_COUNT>;
	FBlendshapes Blendshapes;
};

struct FOOTBALL_API FFootballerData
{
	//~=================================================================================================================
	// STRUCTS
	//~=================================================================================================================
	
	struct FFootballerRating
	{
		float Stars							{};		// 0 to 5
		float Overall						{};		// 0 to 160
		float Potential						{};		// 0 to 160
		ERatingLevel Level					{};

		float MapOverallToStars() const
		{
			return (Overall / 160.f) * 5;
		}

		float MapPotentialToStars() const
		{
			return (Potential / 160.f) * 5;
		}
	};

	struct FPhysicalFeatures
	{
		float Height					 	{};		// Centimeters
		float Weight					 	{};		// Grams
		EPreferredFootType PreferredFoot 	{};
		EFootballerGender Gender		 	{};
	};

	struct FState
	{
		using FPenaltyCards = TStaticArray<int32, Footballer::EPenaltyCardType::MAX_COUNT>; 
		
		float Condition						{};		// 0 to 100
		float Morale						{};		// 0 to 100
		float Sharpness						{};		// 0 to 100
		int32 Injured						{};		// 0 to 2
		FDateTime InjuredEndDate			{};
		FPenaltyCards PenaltyCards			{};		// 1 Red = 5 Yellow
		FDateTime PenaltyCardsBanedEndDate	{};
	};

	struct FStats
	{
		struct FCurrentSeason
		{
			int32 MatchesPlayed {};						// ???
			int32 GoalsScored {};						// ???
			int32 MostGoalsInOneMatch {};				// ???
			int32 SeasonsInClub {};						// ???	
		} CurrentSeason;

		struct FAllSeasons
		{
			int32 MatchesPlayed {};						// ???
			int32 GoalsScored {};						// ???
			int32 MostGoalsInOneMatch {};				// ???
			int32 SeasonsInClub {};						// ???
		} AllSeasons;
	};

	struct FFootballerRelationship
	{
		int32 FootballerId					{};
		ERelationshipType Type				{};
		float Value							{};		// ???
	};

	struct FTeamDynamics
	{
		float AffinityWithManager			{};		// 0 to 10
		float AlignmentWithTeam				{};		// 0 to 10
		EPersonalityType PersonalityType	{};
		TArray<FFootballerRelationship> RelationshipsWithOtherFootballers;
	};

	struct FContract
	{
		inline static constexpr int32 SEASON_DURATION_DAYS = 70;
		
		FDateTime StartSeason;
		FDateTime ExpirySeason;
		FDateTime LastUpdateMarketValue;
		int64 Salary						{};		// 1 = Footballcoin
		int64 MarketValue					{};		// 1 = Footballcoin
		EContractStatus Status				{};

		int32 CalculateRemainingSeasons() const
		{
			const auto DeltaSeason  = ExpirySeason - StartSeason;
			return FMath::RoundToInt32(DeltaSeason.GetDays() / static_cast<float>(SEASON_DURATION_DAYS));
		}
	};

	struct FFootballerName
	{
		enum class EDisplayName : int32
		{
			FirstName,
			LastName
		};

		FText FirstName = FText::AsCultureInvariant("N/A");
		FText LastName  = FText::AsCultureInvariant("N/A");
		EDisplayName SelectedDisplayName = EDisplayName::LastName;

		FFootballerName() = default;
		FFootballerName(const FText& InFirstName, const FText& InLastName)
		: FirstName(InFirstName), LastName(InLastName), SelectedDisplayName(EDisplayName::LastName) {}

		FText GetDisplayName() const
		{
			return SelectedDisplayName == EDisplayName::FirstName ? FirstName : LastName;
		}
	};

	struct FCountryCode
	{
		FName ISO_3166_12 {};
	
		explicit FCountryCode(const FName& ISO)
		{
			ISO_3166_12 = ISO;
		}

		explicit FCountryCode()
		{
			ISO_3166_12 = "Default";
		}
	
		const FISO316612* LoadISO() const
		{
			const UDataTable* DataTable = LoadObject<UDataTable>(nullptr, TEXT("/Game/Football/DataTables/DT_ISO316612.DT_ISO316612"));
			check(DataTable);

			const FISO316612* ISO316612 = DataTable->FindRow<FISO316612>(ISO_3166_12, __FILE__);
			check(ISO316612 && !ISO316612->ISO.IsEmpty());
			
			return ISO316612;
		}
	};

	struct FAttributes
	{
		float& operator[](const int32 Index)
		{
			return Array[Index];
		}

		float operator[](const int32 Index) const
		{
			return Array[Index];
		}

		int32 Num() const
		{
			return Array.Num();
		}

		float NormalizeAttribute(const int32 Index) const
		{
			return (*this)[Index] / 160.f;
		}
		
	private:
		TStaticArray<float, static_cast<uint32>(EFootballerAttributes::MAX_COUNT)> Array;
	};

	
	//~=================================================================================================================
	// TYPEDEFS
	//~=================================================================================================================
	//using FAttributes = TStaticArray<float, static_cast<uint32>(EFootballerAttributes::MAX_COUNT)>;

	//~=================================================================================================================
	// VALUES
	//~=================================================================================================================

	uint32 Id										{};
	uint8 Number									{};		// 0 to 99
	FFootballerName DisplayName						{};

	ECharacterType CharacterType					{};
	int32 CharacterTypePriority						{};		// ???

	float Age										{};		// 0 to 99
	int32 AgeOfRetirement							{};		// 0 to 99
	FCountryCode Nationality						{};

	TArray<EFieldPosition> DesiredFieldPositions	{};
	EFieldPosition SelectedFieldPosition			{};
	EFootballerRole Role							{};

	//todo: mover a struct
	ESpecialTrait SpecialTrait						{};
	int32 SpecialTraitLevel							{};		// ??
	int32 TraitPoints								{};		// ??

	FFootballerAppearance Appearance				{};
	FAttributes Attributes							{};		// 0 to 160
	FState State									{};
	FStats Stats									{};
	FTeamDynamics TeamDynamics						{};
	FContract Contract								{};
	
	FPhysicalFeatures PhysicalFeatures				{};

	FFootballerRating Rating						{};

	EFootballerLineUp LineUpPosition				{};

	FString CustomNotes								{};

	//~=================================================================================================================
	// GETTERS
	//~=================================================================================================================
	FFootballerRating CalculateFootballerRating(const EFieldPosition FieldPosition) const;

	static EFootballerAttributes ToAttribute(int32 Index) { return static_cast<EFootballerAttributes>(Index); }
	static int32 ToIndex(EFootballerAttributes Attribute) { return static_cast<int32>(Attribute); }

	bool operator==(const FFootballerData& Other) const
	{
		return Id == Other.Id;
	}
	
	bool operator!=(const FFootballerData& Other) const
	{
		return !(*this == Other);
	}
};

/**
 * 
 */
class FOOTBALL_API FTeam
{
public:
	inline static constexpr int32 TeamSize = 18;
	using FFootballers = std::array<TSharedPtr<FFootballerData>, TeamSize>;

	explicit FTeam(FFootballers&& InFootballers) : Footballers(MoveTemp(InFootballers)) {} 
	
	const FFootballerData* GetFootballer(const int32 Index) const
	{
		return Footballers[Index].Get();	
	}
	
private:
	FString TeamName;
	FFootballers Footballers;
};
