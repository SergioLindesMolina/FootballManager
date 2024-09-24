// Copyright, 2023, by NGD Studios AB. All rights reserved.

#include "ManagerPlayerController.h"
#include "Football/Formation/FollowMouseComponent.h"
#include "Football/Formation/FieldZone.h"
#include "Football/Formation/FootballerChip.h"
#include <Components/WidgetComponent.h>
#include <Components/InputComponent.h>
#include "DrawDebugHelpers.h"
#include "Engine/Engine.h"

#include "Football/UI/UserWidget/Shared/FootballerProfile/FootballerProfile.h"

AManagerPlayerController::AManagerPlayerController()
{
	bShowMouseCursor = true;
}

void AManagerPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	constexpr float UpRangeMultiplier = 5000;
	constexpr float SphereRadius = 30;

	HandleFieldZoneModeInput(UpRangeMultiplier);

}

void AManagerPlayerController::HandleFieldZoneModeInput(const float UpRangeMultiplier)
{
	FCollisionObjectQueryParams ObjectQueryParams;
	FCollisionQueryParams QueryParams;

	if (UFootballerProfile::bDisplayWidget)
		return;

	if (WasInputKeyJustPressed(EKeys::LeftMouseButton))
	{
		HandleLeftClickPressed();
	}
	else if (WasInputKeyJustReleased(EKeys::LeftMouseButton) && IsValid(DragOperation.HitActor))
	{
		if (IsValid(FieldZoneHighlighted))
		{
			FieldZoneHighlighted->SetHightlight(false);
			FieldZoneHighlighted = nullptr;
		}

		HandleLeftClickReleased(ObjectQueryParams, QueryParams, UpRangeMultiplier);

		if (DragOperation.State == FDragOperation::Down)
		{
			if (AFootballerChip* ChipActor = Cast<AFootballerChip>(DragOperation.HitActor))
			{
				OnActorClickedEvent.Broadcast(ChipActor);
			}
		}
		else if (DragOperation.State == FDragOperation::Drag)
		{
			if (AFootballerChip* ChipActor = Cast<AFootballerChip>(DragOperation.HitActor))
			{
				OnActorDragEnd.Broadcast(ChipActor);
				if (UFollowMouseComponent* FollowMouseComp = DragOperation.HitActor->FindComponentByClass<UFollowMouseComponent>())
				{
					FollowMouseComp->StopTick(DragOperation.HitActor);
				}
			}
		}

		DragOperation.State = FDragOperation::None;
	}

	switch (DragOperation.State)
	{
	case FDragOperation::Down:
	{
		FVector2D MousePos;
		GetMousePosition(MousePos.X, MousePos.Y);
		if (FVector2D::DistSquared(MousePos, DragOperation.StartMousePos) > 10 * 10)
		{
			DragOperation.State = FDragOperation::Drag;

			AFootballerChip* Chip = Cast<AFootballerChip>(DragOperation.HitActor);

			//Set visible true Empty Chip here
			Chip->EmptyChip = GetWorld()->SpawnActor<AEmptyChip>(Chip->EmptyChipSubclass, Chip->GetActorLocation(), FRotator::ZeroRotator);
			Chip->FollowMouseComponent->InitializeTick(DragOperation.HitActor);

			OnActorDragStart.Broadcast(Chip);
		}
	} break;

	case FDragOperation::Drag:
		break;
	}

	HandleHighlight(ObjectQueryParams, QueryParams, UpRangeMultiplier);
}


void AManagerPlayerController::HandleLeftClickPressed()
{
	DragOperation = FDragOperation();

	constexpr float UpRangeMultiplier = 5000;
	static FVector MouseWorldLocation, MouseWorldDirection;
	if(DeprojectMousePositionToWorld(MouseWorldLocation, MouseWorldDirection))
	{
		FCollisionObjectQueryParams ObjectQueryParams;
		FCollisionQueryParams QueryParams;
		TArray<FHitResult> HitResults;
		ObjectQueryParams.AddObjectTypesToQuery(ECC_WorldDynamic);

		if(GetWorld()->LineTraceMultiByObjectType(HitResults, MouseWorldLocation, MouseWorldLocation + MouseWorldDirection * UpRangeMultiplier, ObjectQueryParams, QueryParams))
		{
			//DrawDebugLine(GetWorld(),MouseWorldLocation, MouseWorldLocation + MouseWorldDirection * UpRangeMultiplier,FColor::Red,true);
			AActor* HitActor = nullptr;

			for(const FHitResult& Hit : HitResults)
			{
				if(Hit.GetActor()->GetClass()->IsChildOf(AFootballerChip::StaticClass()))
				{
					HitActor = Hit.GetActor();
					//Set Chip Opacity to 80%
					HitActor->FindComponentByClass<UWidgetComponent>()->SetTintColorAndOpacity(FLinearColor(1.0f, 1.0f, 1.0f, 0.80f));
				}
			}

			if(HitActor)
			{
				//Start Drag or click operation
				GetMousePosition(DragOperation.StartMousePos.X, DragOperation.StartMousePos.Y);
				DragOperation.HitActor = HitActor;
				DragOperation.State = FDragOperation::Down;
				AFootballerChip* Chip = Cast<AFootballerChip>(HitActor);
				DragOperation.HitFieldZone = Chip->CurrentFieldZone;
			}
		}
	}
}

void AManagerPlayerController::HandleLeftClickReleased(FCollisionObjectQueryParams& ObjectQueryParams, FCollisionQueryParams& QueryParams, const float UpRangeMultiplier)
{
	AActor* HitActor = DragOperation.HitActor;
	AFieldZone* HitFieldZone = DragOperation.HitFieldZone;
	TArray<FHitResult> HitResults;
	AFieldZone* ResultFieldZone = nullptr;
	AFootballerChip* ResultChip = nullptr;
	AFootballerChip* ChipActor = Cast<AFootballerChip>(HitActor);
	if(ChipActor->EmptyChip != NULL)
	{
		ChipActor->EmptyChip->K2_DestroyActor();
	}

	ObjectQueryParams.AddObjectTypesToQuery(ECC_WorldDynamic);
	QueryParams.AddIgnoredActor(HitActor);

	if(GetWorld()->LineTraceMultiByObjectType(HitResults, HitActor->GetActorLocation() + HitActor->GetActorUpVector() * UpRangeMultiplier, HitActor->GetActorLocation() + HitActor->GetActorUpVector() * UpRangeMultiplier * -1, ObjectQueryParams, QueryParams))
	{
		for(const FHitResult& Hit : HitResults)
		{
			if(Hit.GetActor()->GetClass()->IsChildOf(AFootballerChip::StaticClass()))
			{
				ResultChip = Cast<AFootballerChip>(Hit.GetActor());
			}
			else if(Hit.GetActor()->GetClass()->IsChildOf(AFieldZone::StaticClass()))
			{
				ResultFieldZone = Cast<AFieldZone>(Hit.GetActor());
			}
		}
	}

	if(ResultChip)
	{
		if(ResultFieldZone)
		{
			ResultFieldZone = ResultChip->CurrentFieldZone;
			SwapChips(ResultChip, ResultFieldZone);
			DragOperation.HitActor = nullptr;
		}
		else
		{
			ResultFieldZone = ResultChip->CurrentFieldZone;
			SwapChips(ResultChip, ResultFieldZone);
			DragOperation.HitActor = nullptr;
		}
	}
	else if(ResultFieldZone && ResultFieldZone != HitFieldZone && ChipActor->IsOnField())
	{
		ChangeToNewFormation(ResultFieldZone);
		HitFieldZone = nullptr;
		DragOperation.HitActor = nullptr;
	}

	if(HitActor)
	{
		HitActor->FindComponentByClass<UWidgetComponent>()->SetTintColorAndOpacity(FLinearColor(1.0f, 1.0f, 1.0f, 1.0f));
	}
}

void AManagerPlayerController::SwapChips(AFootballerChip* ResultActor, AFieldZone* ResultFieldZoneActor)
{
	AActor* HitActor = DragOperation.HitActor;
	AFieldZone* HitFieldZone = DragOperation.HitFieldZone;

	AFootballerChip* ChipHit = Cast<AFootballerChip>(HitActor);
	AFootballerChip* ChipResult = ResultActor;

	ChipHit->FollowMouseComponent->SetComponentTickEnabled(false);
	ChipResult->FollowMouseComponent->StopTickForOverlap(HitActor, ResultActor, ChipHit->FollowMouseComponent->InitialLocation);

	if(ResultFieldZoneActor == nullptr && HitFieldZone == nullptr)
	{
		ChipHit->SetIsOnField(false);
		ChipResult->SetIsOnField(false);
	}
	else if(HitFieldZone == nullptr)
	{
		ResultFieldZoneActor->RemoveChip(ChipResult);
		ResultFieldZoneActor->AddChip(ChipHit, ChipHit->FootballerCurrentTeam);
		ChipResult->SetIsOnField(false);
	}
	else if(ResultFieldZoneActor == nullptr)
	{
		HitFieldZone->RemoveChip(ChipHit);
		HitFieldZone->AddChip(ChipResult, ChipResult->FootballerCurrentTeam);
		ChipHit->SetIsOnField(false);
	}
	else
	{
		AFieldZone* ResultFieldZone = ResultFieldZoneActor;
		ResultFieldZone->RemoveChip(ResultActor);

			HitFieldZone->RemoveChip(HitActor);
			HitFieldZone->AddChip(ChipResult, ChipResult->FootballerCurrentTeam);

		ResultFieldZone->AddChip(ChipHit, ChipHit->FootballerCurrentTeam);

		if(IsValid(FieldZoneHighlighted))
		{
			FieldZoneHighlighted->SetHightlight(false);
			FieldZoneHighlighted = nullptr;
		}
	}
}

void AManagerPlayerController::ChangeToNewFormation(AFieldZone* ResultFieldZoneActor)
{

	AFieldZone* HitFieldZone = DragOperation.HitFieldZone;
	AFootballerChip* ChipActor = Cast<AFootballerChip>(DragOperation.HitActor);
	AFieldZone* ResultFieldZone = ResultFieldZoneActor;

	ChipActor->FollowMouseComponent->SetComponentTickEnabled(false);

	if(ChipActor && ChipActor->IsOnField() && ResultFieldZone->CheckAddChipToField() && HitFieldZone->FootballerPosition != EFieldPosition::GK)
	{
		HitFieldZone->RemoveChip(ChipActor);
		HitFieldZone->SortChips();
		ResultFieldZone->AddChip(ChipActor, ChipActor->FootballerCurrentTeam);
		ResultFieldZone->SortChips();

		if(IsValid(FieldZoneHighlighted))
		{
			FieldZoneHighlighted->SetHightlight(false);
			FieldZoneHighlighted = nullptr;
		}
		OnFormationChange.Broadcast();
	}
	else
	{
		ChipActor->FollowMouseComponent->StopTick(ChipActor);
	}
}

void AManagerPlayerController::HandleHighlight(FCollisionObjectQueryParams& ObjectQueryParams, FCollisionQueryParams& QueryParams, const float UpRangeMultiplier)
{
	if (DragOperation.State == FDragOperation::Drag)
	{
		AActor* HitActor = DragOperation.HitActor;

		if (IsValid(HitActor))
		{
			TArray<FHitResult> HitResults;
			ObjectQueryParams.AddObjectTypesToQuery(ECC_WorldDynamic);
			QueryParams.AddIgnoredActor(HitActor);

			if (GetWorld()->LineTraceMultiByObjectType(HitResults, HitActor->GetActorLocation() + HitActor->GetActorUpVector() * UpRangeMultiplier, HitActor->GetActorLocation() + HitActor->GetActorUpVector() * UpRangeMultiplier * -1, ObjectQueryParams, QueryParams))
			{
				for (FHitResult HitResult : HitResults)
				{
					if (HitResult.GetActor()->GetClass()->IsChildOf(AFieldZone::StaticClass()))
					{
						AFieldZone* FieldZone = Cast<AFieldZone>(HitResult.GetActor());
						//if (HitFieldZone != FieldZone)
						//{
						if (IsValid(FieldZoneHighlighted))
						{
							if (FieldZoneHighlighted != FieldZone)
							{
								FieldZoneHighlighted->SetHightlight(false);
								FieldZone->SetHightlight(true);
								FieldZoneHighlighted = FieldZone;
							}
						}
						else
						{
							FieldZoneHighlighted = FieldZone;
							FieldZoneHighlighted->SetHightlight(true);
						}

						return;
						//}
					}
				}
				if (IsValid(FieldZoneHighlighted))
				{
					FieldZoneHighlighted->SetHightlight(false);
					FieldZoneHighlighted = nullptr;
				}
			}
		}
	}
}

