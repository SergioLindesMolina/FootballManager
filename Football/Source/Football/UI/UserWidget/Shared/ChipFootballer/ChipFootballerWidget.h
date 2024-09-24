// Copyright, 2023, by NGD Studios AB. All rights reserved.

#pragma once

#include <CoreMinimal.h>
#include <Blueprint/UserWidget.h>

#include <Football/UI/UWidget/FootballerPosition/FootballerPosition.h>

#include <ChipFootballerWidget.generated.h>

/**
 * Use to set and show information on Chip Widget
 */

class UTextBlock;
class UImage;
class URatingBarWidget;
class UPenaltyCard;
class UColoredProgressbar;
class UFootballer_Deprecated;
class UFootballerObject;

enum class EFieldPosition : uint8;
enum class EChipFormationStatus : uint8;

UCLASS()
class FOOTBALL_API UChipFootballerWidget : public UUserWidget
{
	GENERATED_BODY()

	DECLARE_DELEGATE(FOnConstructedDelegate);

public:

	void NativeConstruct() override;

	void RefreshData();

	//TODO (David): Change to update all states and info, not only number and name
	void ShowWidgetData(const TArray<EFieldPosition>& ChipPositions, uint8 Number, const FString& DisplayName);

	void UpdateState();

	void ChangePosition(EFieldPosition InChipPosition);

	void CheckDesiredPosition(const EFieldPosition InChipPosition, const UFootballerObject* InFootballer);

	void HideExclamationIcon();

	UFUNCTION()
	void UpdateChipRating();

	void InitializeDelegate();

	FOnConstructedDelegate OnConstructedDelegate;

protected:

	UFootballerObject* GetInitialPositionFootballer(const TArray<UFootballerObject*>& FootballersRef, EFieldPosition TeamPosition, EChipFormationStatus ChipFormationStatus) const;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* FootballerNumber;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* FootballerName;

public:

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UImage* ExclamationIcon;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UImage* CaptainIcon;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UImage* InjuriesIcon;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UImage* BackgroundInjuriesIcon;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UImage* MoraleIcon;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UFootballerPosition* FootballerPosition;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	URatingBarWidget* RatingBar;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UPenaltyCard* PenaltyCard;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UColoredProgressbar* ConditionBar;

	UPROPERTY(BlueprintReadWrite)
	TObjectPtr<UFootballerObject> Footballer;
};
