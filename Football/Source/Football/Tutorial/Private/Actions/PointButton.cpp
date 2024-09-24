// Copyright, 2023, by NGD Studios AB. All rights reserved.


#include "Football/Tutorial/Public/Actions/PointButton.h"
#include "Football/Blocker/BlockedElementInteractions.h"
#include "Football/Blocker/WidgetBlockerHub.h"
#include "TutorialCrafter/Public/TutorialHub.h"
#include "UserInterface/Public/UWidget/ActionButton.h"
#include "UserInterface/Public/Slate/FloatingImage/SFloatingImage.h"
#include "UserInterface/Public/InputSubsystem.h"
#include "UserInterface/Public/UserInterfaceBFL.h"
#include "Blueprint/UserWidget.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Blueprint/SlateBlueprintLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/UserInterfaceSettings.h"


void UPointButton::Do(const UObject* WorldContextObject)
{
	if (!IsValid(InputSubsystem))
	{
		InputSubsystem = UGameInstance::GetSubsystem<UInputSubsystem>(GetWorld()->GetGameInstance());
	}

	CurrentWorld = WorldContextObject->GetWorld();

	if (!IsValid(TargetWidget))
	{
		TArray<AActor*> WidgetBlockerHubArray;
		UGameplayStatics::GetAllActorsOfClass(CurrentWorld, AWidgetBlockerHub::StaticClass(), WidgetBlockerHubArray);

		if (WidgetBlockerHubArray.Num() > 0)
		{
			if (WidgetBlockerHubArray.Num() > 1)
			{
				UE_LOG(LogTemp, Warning, TEXT(" There are more than one WidgetBlockerHub in the level"));
			}
			BlockerHub = Cast<AWidgetBlockerHub>(WidgetBlockerHubArray.Pop());
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT(" There is not one WidgetBlockerHub in the level"));
		}

		TArray<UUserWidget*> FoundUserWidgets;
		UWidgetBlueprintLibrary::GetAllWidgetsOfClass(this, FoundUserWidgets, TargetWidgetParent, false);

		for (UUserWidget* UserWidget : FoundUserWidgets)
		{
			TargetWidget = UserWidget->GetWidgetFromName(TargetWidgetName);

			if (TargetWidget->Implements<UBlockedElementInteractions>())
			{
				TargetWidget = IBlockedElementInteractions::Execute_GetButton(TargetWidget);
			}

			if (IsValid(TargetWidget))
			{
				AddArrowSlate(GetWidgetPosition(TargetWidget), ArrowOffset, ArrowRotation);

				if (TargetWidget->IsA<UActionButton>())
				{
					UActionButton* TargetActionButton = Cast<UActionButton>(TargetWidget);
					TargetActionButton->OnClicked.AddUniqueDynamic(this, &UPointButton::OnFinishAction);
				}
				else if (TargetWidget->IsA<UButton>())
				{
					UButton* TargetButton = Cast<UButton>(TargetWidget);
					TargetButton->OnClicked.AddUniqueDynamic(this, &UPointButton::OnFinishAction);

				}
				else
				{
					checkNoEntry();
				}

				if (bShouldDisableInput)
				{
					InputSubsystem->RestrictInputToWidgets({TargetWidget->GetCachedWidget()});
				}
				else
				{
					//TODO Sergio temporal fix until new block widget strategy
					check(BlockerHub);
					TArray<UWidget*> DefaultWidgetsWithInput = BlockerHub->GetDefaultWidgetsWithInput();

					DefaultWidgetsWithInput.Add(TargetWidget);
					UUserInterfaceBFL::RestrictInputToWidgets(CurrentWorld, DefaultWidgetsWithInput);					
				}
			}
			else
			{
				UE_LOG(LogTemp, Error, TEXT("Couldn't find a widget with the name %s "), *TargetWidgetName.ToString());
			}
		}
	}
	else
	{
		UpdateArrowSlate(GetWidgetPosition(TargetWidget), ArrowOffset, ArrowRotation);
	}
	
}


void UPointButton::Clear(const UObject* WorldContextObject)
{
	OnFinishAction();
}

void UPointButton::UpdateArrowSlate(const FVector2D& TargetWidgetPoint, const float DesiredArrowOffset, const float DesiredArrowRotation)
{
	//TargetWidgetPoint does does not take in consideration the DPIScale because SetScreenPosition does so the offset added to the position need to 
	//take in consideration the DPIScale before adding it to the position TargetWidgetPoint
	check(ArrowSlate.IsValid());

	FVector2D ViewportSize;
	CurrentWorld->GetGameViewport()->GetViewportSize(ViewportSize);
	float DpiScaleBasedOnSize = GetDefault<UUserInterfaceSettings>()->GetDPIScaleBasedOnSize(FIntPoint(ViewportSize.X, ViewportSize.Y));

	ArrowImage.SetImageSize(ArrowSize);
	ArrowSlate->SetImage(&ArrowImage);
	FVector2D SizeOffset = FVector2D(ArrowSize.X * -0.5f, ArrowSize.Y * -0.5f) * DpiScaleBasedOnSize;
	FVector2D DistanceOffset = (DesiredArrowOffset * DpiScaleBasedOnSize) * FVector2D(0.f, -1.0f).GetRotated(DesiredArrowRotation);
	ArrowSlate->SetScreenPosition(TargetWidgetPoint + SizeOffset + DistanceOffset);

	ArrowSlate->SetRotation(DesiredArrowRotation);
}

FVector2D UPointButton::GetWidgetPosition(UWidget* Widget)
{
	check(IsValid(Widget));

	//Widget->GetTickSpaceGeometry() Returns the geometry of the widget always in Desktop / Screen space 
	//Is necessary to convert the position to viewport coordinates before trying to use it for changing the position of a widget 
	//in a RenderTransform
	const FGeometry& WidgetGeometry = Widget->GetTickSpaceGeometry();
	FVector2D WidgetCenterPoint = WidgetGeometry.GetAbsolutePositionAtCoordinates(FVector2D(0.5f, 0.5f));

	FVector2D WidgetViewportPositionNoDPI;
	FVector2D WidgetViewportPositionWithDPI;
	USlateBlueprintLibrary::AbsoluteToViewport(this, WidgetCenterPoint, WidgetViewportPositionNoDPI,
		WidgetViewportPositionWithDPI);

	return WidgetViewportPositionNoDPI;
}

void UPointButton::OnFinishAction()
{	
	if ((ArrowSlate.IsValid()))
	{
		CurrentWorld->GetGameViewport()->RemoveViewportWidgetContent(ArrowSlate.ToSharedRef());
	}
	
	RemoveWidgetsBindings();
	
	if (bShouldDisableInput)
	{		
		check(BlockerHub);

		TArray<UWidget*> DefaultWidgetsWithInput = BlockerHub->GetDefaultWidgetsWithInput();

		if (DefaultWidgetsWithInput.Num() > 0)
		{
			UUserInterfaceBFL::RestrictInputToWidgets(CurrentWorld, DefaultWidgetsWithInput);
		
		}
		else
		{
			InputSubsystem->ClearInputRestriction();
		}
	}
	else
	{
		check(BlockerHub);

		TArray<UWidget*> DefaultWidgetsWithInput = BlockerHub->GetDefaultWidgetsWithInput();

		DefaultWidgetsWithInput.Remove(TargetWidget);

		if (DefaultWidgetsWithInput.Num() > 0)
		{
			UUserInterfaceBFL::RestrictInputToWidgets(CurrentWorld, DefaultWidgetsWithInput);
			
		}
		
	}
	
	TargetWidget = nullptr;
	bCompleted = true;
}

void UPointButton::RemoveWidgetsBindings()
{
	if (IsValid(TargetWidget))
	{
		if (TargetWidget->IsA<UActionButton>())
		{
			UActionButton* TargetActionButton = Cast<UActionButton>(TargetWidget);
			if (TargetActionButton->OnClicked.IsBound())
			{
				TargetActionButton->OnClicked.RemoveDynamic(this, &UPointButton::OnFinishAction);
			}
		}
		else if (TargetWidget->IsA<UButton>())
		{
			UButton* TargetButton = Cast<UButton>(TargetWidget);
			if (TargetButton->OnClicked.IsBound())
			{
				TargetButton->OnClicked.RemoveDynamic(this, &UPointButton::OnFinishAction);
			}
		}
	}	
}

//TODO Sergio Ask if this is the correct location to set the Texture of the propertie
void UPointButton::PostInitProperties()
{
	Super::PostInitProperties();

	FString ArrowImageTexturePath = "/Script/Engine.Texture2D'/Game/Football/Maps/Demo/LockerRoom/T_DemoArrow.T_DemoArrow'";
	UTexture2D* ArrowTexture = LoadObject<UTexture2D>(nullptr, *ArrowImageTexturePath);	

	if (IsValid(ArrowTexture))
	{
		ArrowImage.SetResourceObject(ArrowTexture);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Couldn't find the arrow texture at path %s "), *ArrowImageTexturePath);
	}

}

void UPointButton::AddArrowSlate(const FVector2D& TargetWidgetPoint, const float DesiredArrowOffset, const float DesiredArrowRotation)
{
	if (!ArrowSlate.IsValid())
	{
		ArrowSlate = SNew(SFloatingImage);
	}
	
	CurrentWorld->GetGameViewport()->AddViewportWidgetContent(ArrowSlate.ToSharedRef(), 100);
	
	UpdateArrowSlate(TargetWidgetPoint, DesiredArrowOffset, DesiredArrowRotation);		
}
