// Copyright, 2023, by NGD Studios AB. All rights reserved.


#include "BlockMessage.h"
#include "Components/RichTextBlock.h"
#include "TimerManager.h"

void UBlockMessage::HideMessage()
{
	GetWorld()->GetTimerManager().ClearTimer(MessageTimer);
	
	check(IsValid(BlockedWidget));
	
	if (BlockedWidget->OnVisibilityChanged.IsAlreadyBound(this, &UBlockMessage::OnWidgetBlockedVisibilityChanged))
	{
		BlockedWidget->OnVisibilityChanged.RemoveDynamic(this, &UBlockMessage::OnWidgetBlockedVisibilityChanged);
		
		BlockedWidget = nullptr;
	}

	this->SetVisibility(ESlateVisibility::Collapsed);
}

void UBlockMessage::ShowMessage(const FText& Message, UUserWidget* InBlockedWidget)
{	
	RichTextBlockMessage->SetText(Message);
	this->SetVisibility(ESlateVisibility::SelfHitTestInvisible);

	GetWorld()->GetTimerManager().ClearTimer(MessageTimer);
	GetWorld()->GetTimerManager().SetTimer(MessageTimer, this, &UBlockMessage::HideMessage, MessageLifeTime);

	if (IsValid(BlockedWidget))
	{
		if (BlockedWidget->OnVisibilityChanged.IsAlreadyBound(this, &UBlockMessage::OnWidgetBlockedVisibilityChanged))
		{
			BlockedWidget->OnVisibilityChanged.RemoveDynamic(this, &UBlockMessage::OnWidgetBlockedVisibilityChanged);
			BlockedWidget = nullptr;
		}
	}

	check(IsValid(InBlockedWidget));
	BlockedWidget = InBlockedWidget;
	BlockedWidget->OnVisibilityChanged.AddUniqueDynamic(this, &UBlockMessage::OnWidgetBlockedVisibilityChanged);
}

void UBlockMessage::OnWidgetBlockedVisibilityChanged(ESlateVisibility NewVisibility)
{
	if (NewVisibility == ESlateVisibility::Collapsed || NewVisibility == ESlateVisibility::Hidden)
	{	
		HideMessage();
	}
}