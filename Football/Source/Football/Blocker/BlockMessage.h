// Copyright, 2023, by NGD Studios AB. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BlockMessage.generated.h"

class URichTextBlock;

/**
 * 
 */
UCLASS()
class FOOTBALL_API UBlockMessage : public UUserWidget
{
	GENERATED_BODY()

public: 
	
	UFUNCTION()
	void OnWidgetBlockedVisibilityChanged(ESlateVisibility NewVisibility);

	void HideMessage();

	void ShowMessage(const FText& Message, UUserWidget* InBlockedWidget);

private:

	UPROPERTY(meta = (BindWidget))
	URichTextBlock* RichTextBlockMessage;

	UPROPERTY(Transient)
	FTimerHandle MessageTimer;

	UPROPERTY(EditDefaultsOnly)
	float MessageLifeTime = 2;
	
	UUserWidget* BlockedWidget;

};
