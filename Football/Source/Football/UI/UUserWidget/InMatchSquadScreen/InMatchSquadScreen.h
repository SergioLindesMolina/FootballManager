// Copyright, 2023, by NGD Studios AB. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InMatchSquadScreen.generated.h"

class UButton;
class UStringTable;

/**
 * 
 */
UCLASS()
class FOOTBALL_API UInMatchSquadScreen : public UUserWidget
{
	GENERATED_BODY()

protected:

	void NativeConstruct() override;

	void OnNativeWidgetBlocked(TSharedPtr<SWidget> InWidget);
	
	UFUNCTION(BlueprintImplementableEvent)
	void OnWidgetBlocked(UWidget* Widget, const FText& Message);

	UPROPERTY(meta =(BindWidget) ,BlueprintReadWrite)
	UButton* LineUp;

	UPROPERTY(meta =(BindWidget) ,BlueprintReadWrite)
	UButton* Tactics;

private:

	TMap<UWidget*, FString> WidgetBlockedMessages;

};
