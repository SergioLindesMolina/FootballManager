// Copyright, 2023, by NGD Studios AB. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Components/TimelineComponent.h"
#include "Football/Team/TeamGenerator.h"
#include "Engine/EngineTypes.h"

#include "ManagerPlayerController.generated.h"

class AFieldZone;
class AFootballerChip;

/**
 * Manager actions, but backend actions are going through the Backend
 */

DECLARE_MULTICAST_DELEGATE_OneParam(FStatusEmptyChips, AActor* /*OverlappedActor*/);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FFormationChange);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnActorClicked, AFootballerChip*, Chip);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnActorDragStart, AFootballerChip*);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnActorDragEnd, AFootballerChip*);

UCLASS()
class FOOTBALL_API AManagerPlayerController : public APlayerController
{
	GENERATED_BODY()

protected:

	AManagerPlayerController();

	virtual void Tick(float DeltaTime) override;

	void HandleFieldZoneModeInput(const float UpRangeMultiplier);

	void HandleHighlight(FCollisionObjectQueryParams& ObjectQueryParams, FCollisionQueryParams& QueryParams, const float UpRangeMultiplier);

	void HandleLeftClickReleased(FCollisionObjectQueryParams& ObjectQueryParams, FCollisionQueryParams& QueryParams, const float UpRangeMultiplier);

	void HandleLeftClickPressed();

	void ChangeToNewFormation(AFieldZone* ResultFieldZoneActor);

	void SwapChips(AFootballerChip* ResultActor, AFieldZone* ResultFieldZoneActor);

public:

	UPROPERTY(BlueprintAssignable, Category = "FormationChange")
	FFormationChange OnFormationChange;

	FStatusEmptyChips OnStatusEmptyChips;

	UPROPERTY(BlueprintAssignable)
	FOnActorClicked OnActorClickedEvent;

	FOnActorDragStart OnActorDragStart;
	FOnActorDragEnd OnActorDragEnd;

private:

	AFieldZone* FieldZoneHighlighted = nullptr;

	struct FDragOperation
	{
		enum EChipDragState : uint8
		{
			None,
			Down,
			Drag
		} State = None;

		FVector2D StartMousePos;
		AActor* HitActor = nullptr;
		AFieldZone* HitFieldZone = nullptr;
	} DragOperation;
};
