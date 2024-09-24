// Copyright, 2023, by NGD Studios AB. All rights reserved.


#include "Football/Tutorial/Public/Actions/ShowMessage.h"

#include <Blueprint/WidgetBlueprintLibrary.h>

#include <Football/UI/UserWidget/MatchHud/MatchHudWidget.h>
#include <Football/UI/UserWidget/MatchHud/QuickActions/QuickActions.h>


void UShowMessage::Do(const UObject* WorldContextObject)
{	
	UMatchHudWidget* MatchWidget = nullptr;

	if (!IsValid(MatchWidget))
	{
		//@todo(jcastro): Bad performance, change this.
		TArray<UUserWidget*> FoundUserWidgets;
		UWidgetBlueprintLibrary::GetAllWidgetsOfClass(WorldContextObject->GetWorld(), FoundUserWidgets, UMatchHudWidget::StaticClass(), false);

		if (FoundUserWidgets.IsEmpty())
		{
			bCompleted = true;
			UE_LOG(LogTemp, Error, TEXT("Does not exist a viable widget to show the message"));
			return;
		}

		MatchWidget = Cast<UMatchHudWidget>(FoundUserWidgets[0]);
	}

	if (ensure(IsValid(MatchWidget)))
	{
		// // We auto-hide only when Time is greater than zero.
		// if(Time > 0)
		// {
		// 	FTimerDelegate Delegate;
		// 	Delegate.BindUObject(this, &UShowMessage::HiddeDisplayMessage, const_cast<const UMatchHudWidget*>(MatchWidget));
		// 	GetWorld()->GetTimerManager().SetTimer(DisplayMessageTimerHandle, Delegate, Time, false);	
		// }

		MatchWidget->K2_GetQuickActions()->K2_DisplayAssistantMessage(Message, Time);
		MatchWidget->K2_GetQuickActions()->K2_DisplayAssistantNotify(true);
		
		bCompleted = true;
	}
	else
	{
		bCompleted = false;
		UE_LOG(LogTemp, Error, TEXT("Does not exist a viable widget to show the message"));
	}
}

void UShowMessage::HiddeDisplayMessage(const UMatchHudWidget* MatchWidget) const
{
	MatchWidget->K2_GetQuickActions()->K2_HideAssistantMessage();
	MatchWidget->K2_GetQuickActions()->K2_DisplayAssistantNotify(false);
}
