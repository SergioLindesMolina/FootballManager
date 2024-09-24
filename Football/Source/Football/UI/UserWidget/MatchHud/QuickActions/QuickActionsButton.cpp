// Copyright, 2023, by NGD Studios AB. All rights reserved.


#include "QuickActionsButton.h"
#include "QuickActions.h"

void UQuickActionsButton::InitializeButton(const UQuickActions* InQuickActionsReference)
{
	QuickActionsReference = InQuickActionsReference;
}

void UQuickActionsButton::K2_FinishDisplayed()
{
	if(OnFinishDisplayed.IsBound())
	{
		OnFinishDisplayed.Broadcast();
	}
}

void UQuickActionsButton::K2_FinishHidden()
{
	if(OnFinishHidden.IsBound())
	{
		OnFinishHidden.Broadcast();
	}
}

const UQuickActions* UQuickActionsButton::GetQuickActionsReference() const
{
	check(QuickActionsReference);
	return QuickActionsReference;
}

void UQuickActionsButton::NativeConstruct()
{
	Super::NativeConstruct();
}
