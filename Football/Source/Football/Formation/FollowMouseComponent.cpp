// Copyright, 2023, by NGD Studios AB. All rights reserved.

#include "FollowMouseComponent.h"

UFollowMouseComponent::UFollowMouseComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	SetComponentTickEnabled(false);
}

void UFollowMouseComponent::FollowMouse(AActor* ActorToMove)
{
	FVector MouseWorldPosition;
	FVector MouseWorldDirection;

	GetWorld()->GetFirstPlayerController()->DeprojectMousePositionToWorld(MouseWorldPosition, MouseWorldDirection);
	const float T = (ActorToMove->GetActorLocation().Z - MouseWorldPosition.Z) / MouseWorldDirection.Z;
	FVector IntersectionPoint = MouseWorldPosition + T * MouseWorldDirection;
	IntersectionPoint.Z = ActorToMove->GetActorLocation().Z;
	ActorToMove->SetActorLocation(IntersectionPoint);
}

void UFollowMouseComponent::SwapAnimationBetweenChips()
{
	SwapChipsCounterTime += GetWorld()->GetDeltaSeconds();
	//TODO: Check SwapChipsCounterTime value
	ClickedActor->SetActorLocation(FMath::Lerp(ClickedActor->GetActorLocation(), OverlappedPosition, CurveFloat->GetFloatValue(SwapChipsCounterTime)));
	OverlapActor->SetActorLocation(FMath::Lerp(OverlapActor->GetActorLocation(), ClickedPosition, CurveFloat->GetFloatValue(SwapChipsCounterTime)));

	FVector Position1 = FVector(ClickedActor->GetActorLocation().X, ClickedActor->GetActorLocation().Y, 0.0f);
	FVector Position2 = FVector(OverlapActor->GetActorLocation().X, OverlapActor->GetActorLocation().Y, 0.0f);

	//if(SwapChipsCounterTime >= 1 || )
	if(Position1.Equals(FVector(OverlappedPosition.X,OverlappedPosition.Y,0.0f), Tolerance) && Position2.Equals(FVector(ClickedPosition.X,ClickedPosition.Y,0.0f), Tolerance))
	{
		GetWorld()->GetTimerManager().ClearTimer(SwapChipsTimer);
		SwapChipsCounterTime = 0;
		ClickedActor->SetActorLocation(OverlappedPosition);
		OverlapActor->SetActorLocation(ClickedPosition);
		ClickedActor->SetActorEnableCollision(true);
		OverlapActor->SetActorEnableCollision(true);
	}
}

void UFollowMouseComponent::SwapAnimationToFieldZone()
{
	ChipToFieldZoneCounterTime += GetWorld()->GetDeltaSeconds();

	ClickedActor->SetActorLocation(FMath::Lerp(InitialLocation, ClickedPosition, CurveFloat->GetFloatValue(ChipToFieldZoneCounterTime)));

	FVector Position1 = FVector(ClickedActor->GetActorLocation().X, ClickedActor->GetActorLocation().Y,0.0f);
	FVector Position2 = FVector(ClickedPosition.X, ClickedPosition.Y,0.0f);

	UE_LOG(LogTemp, Log, TEXT("Position1 %f, %f - pos 2 %f, %f"), Position1.X, Position1.Y, Position2.X, Position2.Y);

	if(Position1.Equals(Position2,Tolerance))
	{
		GetWorld()->GetTimerManager().ClearTimer(ChipToFieldZoneTimer);
		ChipToFieldZoneCounterTime = 0;
		ClickedActor->SetActorLocation(ClickedPosition);
	}
}

void UFollowMouseComponent::InitializeTick(AActor* DetectedActor)
{
	HitActor = DetectedActor;
	InitialLocation = DetectedActor->GetActorLocation();
	DetectedActor->AddActorLocalOffset(FVector(0.0f, 0.0f, 100.0f));
	SetComponentTickEnabled(true);
}

void UFollowMouseComponent::StopTick(AActor* DetectedActor)
{
	DetectedActor->AddActorLocalOffset(FVector(0.0f, 0.0f, -100.0f));
	if(AddLerp)
	{
		ClickedActor = DetectedActor;
		ClickedPosition = InitialLocation;
		GetWorld()->GetTimerManager().SetTimer(ChipToFieldZoneTimer, this, &UFollowMouseComponent::SwapAnimationToFieldZone, TimerInterval, true);
	}
	else
	{
		DetectedActor->SetActorLocation(InitialLocation);
	}
	SetComponentTickEnabled(false);
}
//TODO: Change function name
void UFollowMouseComponent::StopTickForOverlap(AActor* DetectedActor, AActor* OverlappedActor, FVector HitActorInitialLocation)
{
	DetectedActor->AddActorLocalOffset(FVector(0.0f, 0.0f, -100.0f));

	AActor* DetectedActorParent = DetectedActor->GetAttachParentActor();
	AActor* OverlappedActorParent = OverlappedActor->GetAttachParentActor();

	DetectedActor->AttachToActor(OverlappedActorParent, FAttachmentTransformRules::KeepWorldTransform);
	OverlappedActor->AttachToActor(DetectedActorParent, FAttachmentTransformRules::KeepWorldTransform);

	if(AddLerp)
	{
		ClickedActor = DetectedActor;
		OverlapActor = OverlappedActor;
		ClickedPosition = HitActorInitialLocation;
		OverlappedPosition = OverlappedActor->GetActorLocation();
		GetWorld()->GetTimerManager().SetTimer(SwapChipsTimer, this, &UFollowMouseComponent::SwapAnimationBetweenChips, TimerInterval, true);
		ClickedActor->SetActorEnableCollision(false);
		OverlapActor->SetActorEnableCollision(false);
	}
	else
	{
		DetectedActor->SetActorLocation(OverlappedActor->GetActorLocation());
		OverlappedActor->SetActorLocation(HitActorInitialLocation);
	}
	SetComponentTickEnabled(false);

	//TODO Maybe this event mustn't stay here
	OnSwapedActorsEvent.Broadcast(DetectedActor);
}

FVector UFollowMouseComponent::GetInitialLocationOfActor() const
{
	return InitialLocation;
}

void UFollowMouseComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	FollowMouse(HitActor);
}
