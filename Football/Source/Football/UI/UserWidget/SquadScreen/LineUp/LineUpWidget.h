// Copyright, 2023, by NGD Studios AB. All rights reserved.

#pragma once

#include <CoreMinimal.h>
#include <Blueprint/UserWidget.h>

#include <UnrealImGui.h>

#include "LineUpWidget.generated.h"

constexpr uint8 NUM_STARTERS = 11;

class UFieldWidget;

UENUM(BlueprintType)
enum class EChipFormationStatus : uint8
{
	InitialPosition,
	AdjacentPosition,
	RandomPosition,
	FinalPosition
};

class AGridGenerator;
class AFootballerChip;
class AFieldZone;
class AEmptyChip;
class ASubstitutesPanel;
class AGridActor;
class UFootballerObject;
 
UCLASS()
class FOOTBALL_API ULineUpWidget : public UUserWidget
{
	GENERATED_BODY()
	
	DEFINE_IMGUI_SCREEN(ULineUpWidget)

protected:

	UFUNCTION(BlueprintCallable)
	void SetCurrentTeam(UTeam_Deprecated* InTeam, const FTeamTacticsData& TeamTacticsData, TArray<AFieldZone*> FieldZones, bool LoadDefault);

	void InitializeStarterChips(UTeam_Deprecated* InTeam);

	UFUNCTION(BlueprintCallable)
	void RefreshAllFootballers();

	AFootballerChip* CreateChip(UTeam_Deprecated* InTeam, UFootballerObject* Footballer);
	
	TArray<uint8> GetFormationData(const FTeamTacticsData& TeamTacticsData);

	void NativeConstruct() override;

private:
	#ifdef WITH_IMGUI
	void DrawImGuiScreen();
	#endif

protected:
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	AGridGenerator* GridGenerator;

	UPROPERTY(EditAnywhere)
	TSubclassOf<AFootballerChip> FootballerChipSubclass;

	EChipFormationStatus FormationStatus;

	UPROPERTY()
	TArray<AFootballerChip*> StarterChips;

	TArray<TObjectPtr<class UFootballerObject>> FootballersToFormation;
};
