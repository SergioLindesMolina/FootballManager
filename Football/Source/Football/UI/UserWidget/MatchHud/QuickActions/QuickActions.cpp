// Copyright, 2023, by NGD Studios AB. All rights reserved.

#include "QuickActions.h"

#include <EnhancedInputComponent.h>
#include <Blueprint/SlateBlueprintLibrary.h>
#include <Common/Logging.h>
#include <Football/CoreClasses/GameplayFramework/FootballPlayerController.h>

#include "GameFramework/HUD.h"
#include <UnrealImGui.h>

#include "Logging/StructuredLog.h"

void UQuickActions::NativeConstruct()
{
	// UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(GetWorld()->GetFirstPlayerController()->InputComponent);
	// for(const TUniquePtr<FEnhancedInputActionEventBinding>& Input : EnhancedInputComponent->GetActionEventBindings())
	// {
	// 	if(Input->GetAction()->GetName() == AFootballPlayerController::InputActionName_LeftMouseButton)
	// 	{
	// 		check(Input->GetAction());
	// 		EnhancedInputComponent->BindAction(Input->GetAction(), ETriggerEvent::Started, this, &UQuickActions::CheckIfMouseClickIsOutsideGeometry);
	// 		break;
	// 	}
	// }
	
	Super::NativeConstruct();
}

void UQuickActions::NativeDestruct()
{
	if(GetWorld()->GetFirstPlayerController())
	{
		UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(GetWorld()->GetFirstPlayerController()->InputComponent);
		check(EnhancedInputComponent);
		
		EnhancedInputComponent->ClearBindingsForObject(this);	
	}
	
	Super::NativeDestruct();
}

void UQuickActions::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	if(GetWorld()->GetFirstPlayerController()->WasInputKeyJustReleased(EKeys::LeftMouseButton))
	{
		CheckIfMouseClickIsOutsideGeometry();
	}
}

void UQuickActions::SetLockSelectIndex(const int32 Index, const bool bLocked)
{
	bLockSelectIndex[static_cast<size_t>(Index)] = bLocked;
}

void UQuickActions::SelectIndex(const int32 Index)
{
	UE_CLOG(bLockSelectIndex[static_cast<size_t>(Index)], LogFootball, Warning, TEXT("UQuickActions::SelectIndex(%d) locked"), Index);
	if(!bLockSelectIndex[static_cast<size_t>(Index)])
	{
		K2_OnSelectedIndex(Index);
	}
}

FVector2f UQuickActions::GetEllipseVertex(const float InAngle, const FVector2f& InCenter, const float InMajorAxis, const float InMinorAxis, const float InRotation, const float InRadius)
{
	return FVector2f(InCenter.X + InRadius * (InMajorAxis * cos(InAngle) * cos(InRotation) - InMinorAxis * sin(InAngle) * sin(InRotation)),
					 InCenter.Y + InRadius * (InMajorAxis * cos(InAngle) * sin(InRotation) + InMinorAxis * sin(InAngle) * cos(InRotation)));
}

FVector2f UQuickActions::GetEllipseNormal(const float Angle, const float MajorAxis, const float MinorAxis, const float Rotation)
{
	return FVector2f(MajorAxis * sin(Angle) * cos(Rotation) + MinorAxis * cos(Angle) * sin(Rotation),
					 MajorAxis * sin(Angle) * sin(Rotation) - MinorAxis * cos(Angle) * cos(Rotation));
}

float UQuickActions::ProjectMouseCoordToEllipseAngle(const FVector2D& MouseCoord, const FGeometry& Geometry, const float Rotation, const float MajorAxis, const float MinorAxis)
{
	FVector2D PixelPosition;
	FVector2D ViewportPosition;
	USlateBlueprintLibrary::LocalToViewport(this, Geometry, FVector2d::ZeroVector, PixelPosition, ViewportPosition);

	const float RotationRotated = Geometry.GetAccumulatedRenderTransform().GetMatrix().GetRotationAngle() - Rotation;
	
	const FVector2d MouseDirection = (MouseCoord - ViewportPosition).GetSafeNormal();
	FVector2d MouseDirectionRotated = {
		(MouseDirection.X * cos(RotationRotated) - MouseDirection.Y * sin(RotationRotated)) / MajorAxis,
		(MouseDirection.X * sin(RotationRotated) + MouseDirection.Y * cos(RotationRotated)) / MinorAxis
	};

	MouseDirectionRotated.Normalize();
	return FMath::Atan2(MouseDirectionRotated.Y, MouseDirectionRotated.X);
}

void UQuickActions::K2_SetupZoneLimit(UWidget* Widget)
{
	LimitWidget = Widget;
}

void UQuickActions::CheckIfMouseClickIsOutsideGeometry()
{
	check(LimitWidget && "K2_SetupZoneLimit must be called before CheckIfMouseClickIsOutsideGeometry");
	
	float MouseCoordX, MouseCoordY;
	GetWorld()->GetFirstPlayerController()->GetMousePosition(MouseCoordX, MouseCoordY);

	const FVector2f MouseCoord(MouseCoordX, MouseCoordY);
	const FVector2d Position = LimitWidget->GetTickSpaceGeometry().GetAbsolutePositionAtCoordinates(FVector2f{0, 0});
	const FVector2d Size     = LimitWidget->GetCachedGeometry().GetAbsoluteSize();

	FVector2D PixelPosition;
	FVector2D ViewportPosition;
	USlateBlueprintLibrary::AbsoluteToViewport(GetWorld(), Position, PixelPosition, ViewportPosition);

	const bool bOutsideX = MouseCoord.X < PixelPosition.X || MouseCoord.X >= PixelPosition.X + Size.X;
	const bool bOutsideY = MouseCoord.Y < PixelPosition.Y || MouseCoord.Y  > PixelPosition.Y + Size.Y;

	if(bOutsideX || bOutsideY)
	{
		K2_OnUnselected();
	}
}
