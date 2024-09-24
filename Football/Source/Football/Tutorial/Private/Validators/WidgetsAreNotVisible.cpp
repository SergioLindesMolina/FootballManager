// Copyright, 2023, by NGD Studios AB. All rights reserved.


#include "Football/Tutorial/Public/Validators/WidgetsAreNotVisible.h"
#include "TutorialCrafter/Public/TutorialHub.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Blueprint/UserWidget.h"
#include "Engine/World.h"
#include "Football/UtilsFunctionLibrary.h"
#include "EngineUtils.h"



bool UWidgetsAreNotVisible::Check(const UObject* WorldContextObject)
{
	bool Result = true;

	TActorIterator<ATutorialHub> It(WorldContextObject->GetWorld());
	ATutorialHub* TutorialHub = *It;

	for (const FWidgetHandler& Widget : WidgetsToFind)
	{
		TArray<UUserWidget*> FoundUserWidgets;
		UWidgetBlueprintLibrary::GetAllWidgetsOfClass(WorldContextObject->GetWorld(), FoundUserWidgets, Widget.ContainerClass, false);

		for (UUserWidget* UserWidget : FoundUserWidgets)
		{			
			if (UWidget* FoundWidget = UserWidget->GetWidgetFromName(Widget.Name))
			{								
				if (UUtilsFunctionLibrary::IsWidgetVisibleOnScreen(FoundWidget))
				{
					if (TutorialHub)
					{
						TutorialHub->OnValidatorWidget(false, UserWidget);
					}
					return false;
				}
			}
		}
	}

	if (TutorialHub)
	{
		TutorialHub->OnValidatorWidget(true, nullptr);
	}

	return Result;
}
