// Copyright, 2023, by NGD Studios AB. All rights reserved.

#pragma once

#include <CoreMinimal.h>
#include <Engine/DataAsset.h>
#include "AssetRegistry/AssetRegistryModule.h"
#include <Common/Logging.h>


#include "Misc/MessageDialog.h"
#include "Tactics.generated.h"

// PackagingResults: Warning: 'TacticGroup' and 'ETacticGroup' have the same name (TacticGroup) when exposed to Python.
// Rename one of them using 'ScriptName' meta-data.
//
// @see https://forums.unrealengine.com/t/logpython-warning/510331
UENUM(BlueprintType, meta=(ScriptName="ETacticGroup"))
enum class ETacticGroup : uint8
{
	Invalid,

	TeamFocus,
	DefaultWorkRate,
	CreativeFreedom,
	ForceSetPieces,
	PassingStyle,
	WorkRate,
	AttackingWidth,
	AttackingFocus,
	ForceCounterAttack,
	AdvanceApproach,
	FinalThird,
	OffsideTrap,
	DefenceFocus,
	TacklingStyle,
	MarkingStyle,
	DefensiveLine,

	MAX UMETA(Hidden),
};

// PackagingResults: Warning: 'TacticValue' and 'ETacticValue' have the same name (TacticValue) when exposed to Python.
// Rename one of them using 'ScriptName' meta-data.
//
// @see https://forums.unrealengine.com/t/logpython-warning/510331
UENUM(BlueprintType, meta=(ScriptName="ETacticValue"))
enum class ETacticValue : uint8
{
	None,
	UltraDefensive,
	Defensive,
	Balanced,
	Offensive,
	AllOutAttack,
	VeryLow,
	Low,
	High,
	VeryHigh,
	Creative,
	Disciplined,
	FreeKicks,
	Corners,
	Both,
	Short,
	Long,
	Narrow,
	Wide,
	VeryWide,
	Left,
	Right,
	BothSides,
	Center,
	Mixed,
	Yes,
	No,
	VerticalPasses,
	Dribbling,
	WaitForOpenings,
	Adapt,
	WorkIntoBox,
	EarlyCrosses,
	DeepCrosses,
	ShootOnSight,
	ManToMan,
	Zonal,
	Cautious,
	Aggressive,
	Higher,
	Lower,
	AsFormation,

	MAX UMETA(Hidden),
};
/**
 * Represents UI metadata for a tactic's values, such as its name and description.
 */
USTRUCT(BlueprintType)
struct FOOTBALL_API FTacticValue
{
	GENERATED_BODY()

	// The displayed name of the Tactic's value.
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FText DisplayName = INVTEXT("N/A");

	// A brief description of the Tactic's value.
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FText Description = INVTEXT("N/A");

	// The thumbnail image for this tactic's value.
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UTexture2D* Thumbnail {};

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	ETacticValue Key {};
};

/**
 * Represents all of the necessary data for a tactic.
 */
USTRUCT(BlueprintType)
struct FOOTBALL_API FTacticGroup
{
	GENERATED_BODY()

	// The name displayed for the tactic.
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FText DisplayName = INVTEXT("N/A");

	// A detailed description of the tactic.
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FText Description = INVTEXT("N/A");

	// A collection of values associated with this tactic.
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<FTacticValue> Values;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	ETacticGroup Key {};

	int32 SelectedIndex {};

	bool operator==(const FTacticGroup& Other) const
	{
		return DisplayName.ToString() == Other.DisplayName.ToString()
		    && Description.ToString() == Other.Description.ToString()
		    && Values.Num() == Other.Values.Num();
	}
};

/**
 * Represents a DataAsset version of FTacticGroup.
 * Acts as a data container for a single tactic.
 */
UCLASS()
class FOOTBALL_API UTacticGroupDataAsset : public UDataAsset
{
	GENERATED_BODY()

public:
	// Fetch the underlying FTacticGroup object.	
	const FTacticGroup& GetTacticGroup() const { return Tactic; } 
	
private:
	// Holds the instance of the Tactic object.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, DuplicateTransient, meta=(AllowPrivateAccess=true))
	FTacticGroup Tactic;
};

/**
 * Represents a predefined set of tactics.
 */
USTRUCT(BlueprintType)
struct FOOTBALL_API FTacticPreset
{
	typedef TMap<UTacticGroupDataAsset*, int32> FOverrides;
	
	GENERATED_BODY()

	// The name displayed for the tactic preset.
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FText DisplayName;

	// A detailed description of the tactic preset.
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FText Description;	

	// The thumbnail image for this tactic preset.
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UTexture2D* Thumbnail {};
	
	//
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TMap<UTacticGroupDataAsset*, int32> OverrideValues;

};

/**
 * Represents a DataAsset version of FTacticPreset.
 * Acts as a data container for a predefined set of tactics.
 */
UCLASS()
class FOOTBALL_API UTacticPresetDataAsset : public UDataAsset
{
	GENERATED_BODY()

public:
	// Fetch the underlying FTacticPreset object.
	const FTacticPreset& GetTacticPreset() const { return TacticPreset; }

	// Fetch the underlying FTacticPreset object.
	FTacticPreset& GetTacticPreset() { return TacticPreset; } 
	
private:
	// Holds the instance of the Tactic Preset object.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, DuplicateTransient, meta=(AllowPrivateAccess=true))
	FTacticPreset TacticPreset;
};


UCLASS()
class UTacticsFunctionLibraryBFL : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
		
	//~=================================================================================================================
	// Helpers
	//~=================================================================================================================

	UFUNCTION(BlueprintPure)
	static TArray<UTacticGroupDataAsset*> GetTacticGroupDataAssetsFromFolder(const FString& Path)
	{
		const auto& AssetRegistryModule = FModuleManager::LoadModuleChecked<FAssetRegistryModule>("AssetRegistry");
		TArray<FAssetData> AssetsInFolder;
		AssetRegistryModule.Get().GetAssetsByPath(*Path, AssetsInFolder, /*bRecursive:*/ true);

		TArray<UTacticGroupDataAsset*> TacticGroupDataAssets;
		for (const FAssetData& AssetData : AssetsInFolder)
		{
			TacticGroupDataAssets.Add(Cast<UTacticGroupDataAsset>(AssetData.GetAsset()));
		}

		return TacticGroupDataAssets;
	};

	UFUNCTION(BlueprintPure)
	static TArray<UTacticPresetDataAsset*> GetTacticPresetDataAssetFromFolder(const FString& Path)
	{
		const auto& AssetRegistryModule = FModuleManager::LoadModuleChecked<FAssetRegistryModule>("AssetRegistry");
		TArray<FAssetData> AssetsInFolder;
		AssetRegistryModule.Get().GetAssetsByPath(*Path, AssetsInFolder, /*bRecursive:*/ true);

		TArray<UTacticPresetDataAsset*> TacticPresetDataAsset;
		TacticPresetDataAsset.Reserve(AssetsInFolder.Num());

		for (const FAssetData& AssetData : AssetsInFolder)
		{
			check(AssetData.GetAsset());

	#if !UE_BUILD_SHIPPING
			if (AssetData.GetAsset()->IsA<UObjectRedirector>())
			{
				UE_LOG(LogFootball, Error, TEXT("Attempted to read a UTacticPresetDataAsset, but received a UObjectRedirector instead."));
				continue;
			}
	#endif

			check(AssetData.GetAsset()->IsA<UTacticPresetDataAsset>());
			TacticPresetDataAsset.Add(Cast<UTacticPresetDataAsset>(AssetData.GetAsset()));
		}

		#if WITH_EDITOR
		if(!GEngine->IsEditor())
		{
			// Playing in Standalone
			// FAssetRegistryModule does not work correctly in Standalone mode. Since Tactics utilizes this method
			// to dynamically load tactics, we prevent its use.
			//
			// Perhaps we should reconsider how tactics load the tactics in order to avoid this workaround?
			FMessageDialog::Open(EAppMsgType::Ok, INVTEXT("Due to the UE-41270 error, this project cannot be used in Standalone mode"));
			FPlatformMisc::RequestExit(false);
			return TacticPresetDataAsset;
		}
		#endif


		check(!TacticPresetDataAsset.IsEmpty());
		return TacticPresetDataAsset;
	}
};
