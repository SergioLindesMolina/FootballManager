// Copyright, 2023, by NGD Studios AB. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "TutorialCrafter/Public/TutorialAction.h"
#include "PointButton.generated.h"

class SFloatingImage;
class UWidget;
class SWidget;
class UInputSubsystem;
class AWidgetBlockerHub;

/**
 * Create a slate arrow to point a button, disable all the input from other widgets, and wait until the user interact with the button to finish
 */
UCLASS()
class FOOTBALL_API UPointButton : public UTutorialAction
{
	GENERATED_BODY()

public:

	void Do(const UObject* WorldContextObject) override;

	void Clear(const UObject* WorldContextObject) override;

	void AddArrowSlate(const FVector2D& TargetWidgetPoint, const float DesiredArrowOffset, const float DesiredArrowRotation);

	void UpdateArrowSlate(const FVector2D& TargetWidgetPoint, const float DesiredArrowOffset, const float DesiredArrowRotation);

	FVector2D GetWidgetPosition(UWidget* Widget);

	UFUNCTION()
	void OnFinishAction();

	void RemoveWidgetsBindings();	

	void PostInitProperties() override;

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UUserWidget> TargetWidgetParent;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName TargetWidgetName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float ArrowRotation = 0.f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float ArrowOffset = 50.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	FVector2D ArrowSize = FVector2D(50.f, 50.f);

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	bool bShouldDisableInput = true;

	FSlateBrush ArrowImage;

	UPROPERTY(Transient)
	UWidget* TargetWidget;

	UPROPERTY(Transient)
	UInputSubsystem* InputSubsystem;

	UPROPERTY(Transient)
	AWidgetBlockerHub* BlockerHub;
	
	TSharedPtr<SFloatingImage> ArrowSlate;

	UPROPERTY(Transient)
	const UWorld* CurrentWorld;	
};
