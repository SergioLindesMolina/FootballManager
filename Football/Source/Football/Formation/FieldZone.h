// Copyright, 2023, by NGD Studios AB. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include <Football/Formation/GridGenerator/GridActor.h>
#include "FieldZone.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnRefreshTeamRating);

class UFollowMouseComponent;
class UStaticMeshComponent;
class UFootballer_Deprecated;
class UWidgetComponent;
class UTeam_Deprecated;
class UChipFootballerWidget;
class AFootballerChip;
class AEmptyChip;
class AGridGenerator;
class AGridActor;
class UMaterial;

enum class EFieldPosition : uint8;

UCLASS()
class FOOTBALL_API AFieldZone : public AActor
{

	GENERATED_BODY()
	
public:
	
	void AddChip(AFootballerChip* Chip, UTeam_Deprecated* InTeam);

	void RemoveChip(AActor* Actor);

	void RemoveAllChips();

	bool CheckAddChipToField();

	UFUNCTION()
	void ToogleFieldZoneVisibility(AFootballerChip* Chip);

	UFUNCTION()
	void ShowFieldZone(AFootballerChip* Chip);

	UFUNCTION()
	void HideFieldZone(AFootballerChip* Chip);

	int32 GetNumFootballersOnField();

	void SortChips();

	void MoveChipToGridActor(AFootballerChip* Chip, AGridActor* GridActor);

	void SetHightlight(bool Value);

	void SetGridGenerator(AGridGenerator* Grid);

	UPROPERTY(BlueprintAssignable)
	FOnRefreshTeamRating OnRefreshTeamRating;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EFieldPosition FootballerPosition;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widgets")
	UWidgetComponent* FieldZoneWidget;

	UPROPERTY(EditAnywhere)
	bool IsAnimationEnabled = false;

protected:

	AFieldZone();

	virtual void BeginPlay() override;

	TArray<AFootballerChip*> FootballerChips;

	AGridGenerator* GridGenerator;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<int32> GridIndices;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	UStaticMeshComponent* FieldMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UMaterial* OnMaterial;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UMaterial* OffMaterial;

	FTimerHandle MoveAnimationTimer;

	UPROPERTY(EditAnywhere, Category = "Lerp")
	float TimerInterval = 0.01f;

	UPROPERTY(EditAnywhere, Category = "Lerp")
	UCurveFloat* CurveFloat;

private:

	UFUNCTION()
	void MoveAnimation();

	void SetFieldZoneVisibility(bool bSetVisible);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Properties", meta = (AllowPrivateAccess = true))
	USceneComponent* SceneComp;

	bool isHighlighted = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widgets", meta = (AllowPrivateAccess = true))
	TSubclassOf<UUserWidget> FieldZoneWidgetClass;

	float AnimationCounter = 0.0f;

	AFootballerChip* ChipToMove = nullptr;
	AGridActor* GridPositionToMove = nullptr;
};
