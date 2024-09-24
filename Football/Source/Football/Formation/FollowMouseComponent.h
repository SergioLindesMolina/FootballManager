// Copyright, 2023, by NGD Studios AB. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "FollowMouseComponent.generated.h"

/**
 * Component for any Actor to follow the mouse
 */

DECLARE_MULTICAST_DELEGATE_OneParam(FOnSwapedActors, AActor* /*OverlappedActor*/)

class UCurveFloat;

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class FOOTBALL_API UFollowMouseComponent : public UActorComponent
{
	GENERATED_BODY()

protected:

	UFollowMouseComponent();

	UPROPERTY(EditAnywhere, Category = "Lerp")
	UCurveFloat* CurveFloat;

public:

	void InitializeTick(AActor* DetectedActor);

	void StopTick(AActor* DetectedActor);

	void StopTickForOverlap(AActor* DetectedActor, AActor* OverlappedActor, FVector HitActorInitialLocation);

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:

	FVector GetInitialLocationOfActor() const;

	void FollowMouse(AActor* ActorToMove);

	UFUNCTION()
	void SwapAnimationBetweenChips();

	UFUNCTION()
	void SwapAnimationToFieldZone();

public:

	FOnSwapedActors OnSwapedActorsEvent;

	FVector InitialLocation;

	FTimerHandle SwapChipsTimer;
	FTimerHandle ChipToFieldZoneTimer;

private:

	AActor* HitActor = nullptr;

	UPROPERTY(EditAnywhere, Category = "Lerp")
	bool AddLerp = true;

	UPROPERTY(EditAnywhere, Category = "Lerp")
	float TimerInterval = 0.02f;

	UPROPERTY(EditAnywhere, Category = "Lerp")
	float Tolerance = 1.0f;

	float SwapChipsCounterTime = 0.0f;
	float ChipToFieldZoneCounterTime = 0.0f;

	AActor* ClickedActor = nullptr;
	AActor* OverlapActor = nullptr;

	FVector ClickedPosition;
	FVector OverlappedPosition;

};
