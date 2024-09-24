// Copyright, 2023, by NGD Studios AB. All rights reserved.


#include "Football/Tutorial/Public/Actions/HideMessage.h"

#include <Blueprint/WidgetBlueprintLibrary.h>

#include <Football/UI/UserWidget/MatchHud/MatchHudWidget.h>
#include <Football/UI/UserWidget/MatchHud/QuickActions/QuickActions.h>


void UHideMessage::Do(const UObject* WorldContextObject)
{
	UMatchHudWidget* MatchWidget = nullptr;

	//@todo(jcastro): Bad performance, change this.
	//@todo(jcastro): Code duplicated in UShowMessage
	TArray<UUserWidget*> FoundUserWidgets;
	UWidgetBlueprintLibrary::GetAllWidgetsOfClass(WorldContextObject->GetWorld(), FoundUserWidgets, UMatchHudWidget::StaticClass(), false);

	if (FoundUserWidgets.Num() <= 0)
	{
		bCompleted = true;
		UE_LOG(LogTemp, Error, TEXT("Does not exist a viable widget to show the message"));
		return;
	}

	MatchWidget = Cast<UMatchHudWidget>(FoundUserWidgets[0]);

	if (IsValid(MatchWidget))
	{
		MatchWidget->K2_GetQuickActions()->K2_HideAssistantMessage();
		MatchWidget->K2_GetQuickActions()->K2_DisplayAssistantNotify(false);
		
		bCompleted = true;
	}
	else
	{
		bCompleted = false;
		UE_LOG(LogTemp, Error, TEXT("Does not exist a viable widget to hide the message"));
	}
}
