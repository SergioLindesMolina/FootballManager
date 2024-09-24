// Copyright, 2023, by NGD Studios AB. All rights reserved.

#pragma once

#include <CoreMinimal.h>
#include <Components/Button.h>

#include "CaptainsFootballerCard.generated.h"

enum class EFieldPosition : uint8;


/**
 * 
 */
UCLASS()
class FOOTBALL_API UCaptainsFootballerCard : public UButton
{
	GENERATED_BODY()

protected:
	UCaptainsFootballerCard();

protected:
	// Begin UWidget interface
	TSharedRef<SWidget> RebuildWidget() override;
	void SynchronizeProperties() override;
	// End UWidget interface


#if WITH_EDITOR
	const FText GetPaletteCategory() override { return INVTEXT("Football"); }
#endif

public:
	
	UFUNCTION(BlueprintCallable)
	void SetCardName(const FText& InName);

	UFUNCTION(BlueprintCallable)
	void SetAfinity(const FText& InAfinity);

	UFUNCTION(BlueprintCallable)
	void SetSpecialTrait(const FText& InTeamLeader);

	UFUNCTION(BlueprintCallable)
	void SetTraitLevel(const FText& InTraitLevel);

	UFUNCTION(BlueprintCallable)
	void SetFieldPositions(const TArray<EFieldPosition>& InFieldPositions);

	UFUNCTION(BlueprintCallable)
	void SetBorderEnable(const bool BorderEnable);
	
protected:

	UPROPERTY(EditAnywhere, Category = "CaptainsFootballerCard|Appearance")
	FLinearColor CardBackgroundColor;

	UPROPERTY(EditAnywhere, Category = "CaptainsFootballerCard|Appearance")
	FSlateBrush PortraitBrush;

	UPROPERTY(EditAnywhere, Category = "CaptainsFootballerCard|Appearance")
	FSlateBrush BorderBrush;

	UPROPERTY(EditAnywhere, Category = "CaptainsFootballerCard|Appearance")
	FSlateBrush AfinityBrush;

	UPROPERTY(EditAnywhere, Category = "CaptainsFootballerCard|Appearance")
	FSlateBrush TeamLeaderBrush;

	UPROPERTY(EditAnywhere, Category = "CaptainsFootballerCard|Appearance")
	FSlateBrush TraitLevelBrush;

	UPROPERTY(EditAnywhere, Category = "CaptainsFootballerCard|Appearance")
	FTextBlockStyle NameTextBlockStyle;

	UPROPERTY(EditAnywhere, Category = "CaptainsFootballerCard|Appearance")
	FTextBlockStyle AfinityTextBlockStyle;

	UPROPERTY(EditAnywhere, Category = "CaptainsFootballerCard|Appearance")
	FTextBlockStyle TeamLeaderTextBlockStyle;

	UPROPERTY(EditAnywhere, Category = "CaptainsFootballerCard|Appearance")
	FTextBlockStyle TraitLevelTextBlockStyle;

	UPROPERTY(EditAnywhere, Category = "FootballerPosition|Appearance")
	FTextBlockStyle FootballerPositionTextBlockStyle;

	UPROPERTY(EditAnywhere, Category = "FootballerPosition|Appearance")
	TArray<EFieldPosition> FieldPositions;

	UPROPERTY(EditAnywhere, Category = "CaptainsFootballerCard|Appearance")
	FVector2D RatingSize;

	UPROPERTY(EditAnywhere, Category = "CaptainsFootballerCard|Appearance")
	FButtonStyle TraitButtonStyle;



	UPROPERTY(EditAnywhere, Category = "FootballerCard|Data")
	FText Name;

	UPROPERTY(EditAnywhere, Category = "FootballerCard|Data")
	FText Afinity;

	UPROPERTY(EditAnywhere, Category = "FootballerCard|Data")
	FText SpecialTrait;

	UPROPERTY(EditAnywhere, Category = "FootballerCard|Data")
	FText TraitLevel;

	UPROPERTY(EditAnywhere, Category = "FootballerCard|Data")
	bool bIsBorderEnable = false;

};
