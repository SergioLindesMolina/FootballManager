// Copyright, 2023, by NGD Studios AB. All rights reserved.


#include "InMatchSquadScreen.h"
#include "Components/Button.h"
#include "Internationalization/StringTable.h"
#include "Kismet/KismetStringTableLibrary.h"
#include "UserInterface/Public/InputSubsystem.h"


void UInMatchSquadScreen::NativeConstruct()
{
	Super::NativeConstruct();

	UInputSubsystem* InputSubsystem = UGameInstance::GetSubsystem<UInputSubsystem>(GetWorld()->GetGameInstance());

	InputSubsystem->OnWidgetBlocked.AddUObject(this, &UInMatchSquadScreen::OnNativeWidgetBlocked);

	WidgetBlockedMessages.Add(LineUp, UKismetStringTableLibrary::GetTableEntrySourceString(FName("/Game/Football/Localization/MainStringTable.MainStringTable"), "Demo.Block.Lineup"));
	WidgetBlockedMessages.Add(Tactics, UKismetStringTableLibrary::GetTableEntrySourceString(FName("/Game/Football/Localization/MainStringTable.MainStringTable"), "Demo.Block.Tactics"));

}


void UInMatchSquadScreen::OnNativeWidgetBlocked(TSharedPtr<SWidget> InWidget)
{
	for (const auto& Element : WidgetBlockedMessages)
	{
		if ([&](){return Element.Key->GetCachedWidget() == InWidget;}())
		{
			OnWidgetBlocked(Element.Key, FText::FromString(Element.Value));
		}
	}
}
