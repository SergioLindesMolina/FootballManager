// Copyright, 2023, by NGD Studios AB. All rights reserved.


#include "WidgetBlockerHub.h"
#include "UserInterface/Public/InputSubsystem.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Blueprint/UserWidget.h"
#include "BlockMessage.h"
#include "BlockedElementInteractions.h"
#include "Blueprint/SlateBlueprintLibrary.h"


AWidgetBlockerHub::AWidgetBlockerHub()
{
	PrimaryActorTick.bCanEverTick = false;
}

TArray<UWidget*> AWidgetBlockerHub::GetDefaultWidgetsWithInput()
{
	return DefaultWidgetsWithInput;
}

/*
*
* This approach is not well optimized because checks the blocked widget against all the user widgets in the viewport
* but the feature is only designed for the demo and only used when the player interact. For that reason
* the performance of the function is not a very important factor
*
*/
void AWidgetBlockerHub::OnWidgetBlocked(TSharedPtr<SWidget> WidgetClicked)
{
	TArray<UUserWidget*> FoundUserWidgets;
	UWidgetBlueprintLibrary::GetAllWidgetsOfClass(GetWorld(), FoundUserWidgets, UUserWidget::StaticClass(), false);

	for (UUserWidget* CurrentUserWidget : FoundUserWidgets)
	{
		UWidget* FoundWidget = CurrentUserWidget->GetWidgetHandle(WidgetClicked.ToSharedRef());
		if (FoundWidget)
		{
 			if (CurrentUserWidget->Implements<UBlockedElementInteractions>())
 			{
 				FText BlockMessage = IBlockedElementInteractions::Execute_GetBlockedWidgetText(CurrentUserWidget, FoundWidget);
 
 				if (!BlockMessage.IsEmpty())
 				{
 					ensureAlways(BlockMessageWidget);
 
 					BlockMessageWidget->ShowMessage(BlockMessage, CurrentUserWidget);
 
 					FVector2D AbsolutePosition = FoundWidget->GetCachedGeometry().GetAbsolutePositionAtCoordinates(FVector2D(1.f, 0.5f));
 					FVector2D WidgetViewportPositionNoDPI;
 					FVector2D WidgetViewportPositionWithDPI;
 					USlateBlueprintLibrary::AbsoluteToViewport(GetWorld(), AbsolutePosition, WidgetViewportPositionNoDPI,
 						WidgetViewportPositionWithDPI);
 
 					BlockMessageWidget->SetPositionInViewport(WidgetViewportPositionWithDPI, false);
 				}
 				else
 				{
 					UE_LOG(LogTemp, Error, TEXT("The widget %s implements the interface UIInteractions but does not have a message set"), *CurrentUserWidget->GetName());
 				}
 			}
		}
	}
}


void AWidgetBlockerHub::BeginPlay()
{
	Super::BeginPlay();

	UInputSubsystem* InputSubsystem = UGameInstance::GetSubsystem<UInputSubsystem>(GetWorld()->GetGameInstance());
	InputSubsystem->OnWidgetBlocked.AddUObject(this, &AWidgetBlockerHub::OnWidgetBlocked);

	ensureAlways(BlockMessageWidgetClass);
	BlockMessageWidget = CreateWidget<UBlockMessage>(GetWorld()->GetFirstPlayerController(), BlockMessageWidgetClass);
	BlockMessageWidget->AddToViewport(200);
	
}

void AWidgetBlockerHub::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	UE_LOG(LogTemp,Warning,TEXT("The widget blocker is being eliminated"));
}

