// Copyright, 2023, by NGD Studios AB. All rights reserved.

#pragma once

#include <CoreMinimal.h>
#include <Blueprint/UserWidget.h>

#include "QuickActionsButton.generated.h"

class UQuickActions;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FQuickActionsButtonEvent);

/**
 * Represent a QuickActions' button:
 *	1) Work-rate
 *	2) Shouts
 *	3) Emotes
 *
 *	Handles the animation and internal logic shared with his coordinator UQuickActions.
 *	
 *	Overriding K2_DisplayContent and K2_HideContent is expected. Besides that, this class
 *	assumes that UMG representation calls K2_FinishDisplayed and K2_FinishHidden by itself.
 *	
 * @see UQuickActions
 */
UCLASS()
class FOOTBALL_API UQuickActionsButton : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void InitializeButton(const UQuickActions* InQuickActionsReference);
	
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, DisplayName=DisplayContent)
	void K2_DisplayContent();

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, DisplayName=HideContent)
	void K2_HideContent();

protected:
	UFUNCTION(BlueprintCallable, DisplayName=FinishDisplayed)
	void K2_FinishDisplayed();

	UFUNCTION(BlueprintCallable, DisplayName=FinishHidden)
	void K2_FinishHidden();

	UFUNCTION(BlueprintCallable)
	const UQuickActions* GetQuickActionsReference() const;
	
protected:
	void NativeConstruct() override;
	
private:
	const UQuickActions* QuickActionsReference {};

	UPROPERTY(BlueprintAssignable, meta=(AllowPrivateAccess))
	FQuickActionsButtonEvent OnFinishDisplayed;

	UPROPERTY(BlueprintAssignable, meta=(AllowPrivateAccess))
	FQuickActionsButtonEvent OnFinishHidden;
};
