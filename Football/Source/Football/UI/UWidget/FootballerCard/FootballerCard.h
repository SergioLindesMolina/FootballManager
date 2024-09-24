// Copyright, 2023, by NGD Studios AB. All rights reserved.

#pragma once

#include <CoreMinimal.h>
#include <Components/Button.h>

#include "FootballerCard.generated.h"

enum class EFieldPosition : uint8;
enum class EPreferredFootType : uint8;


/**
 * 
 */
UCLASS()
class FOOTBALL_API UFootballerCard : public UButton
{
	GENERATED_BODY()

protected:
	UFootballerCard();

protected:
	// Begin UWidget interface
	TSharedRef<SWidget> RebuildWidget() override;
	void SynchronizeProperties() override;
	void PostLoad() override;
	// End UWidget interface

	// UPanelWidget
	UClass* GetSlotClass() const override;
	void OnSlotAdded(UPanelSlot* Slot) override;
	// End UPanelWidget

#if WITH_EDITOR
	const FText GetPaletteCategory() override { return INVTEXT("Football"); }
#endif

public:
	UFUNCTION(BlueprintCallable)
	void SetCardBackgroundColor(const FLinearColor& CardBackgroundColor);
	
	UFUNCTION(BlueprintCallable)
	void SetNameBackgroundColor(const FLinearColor& NameBackgroundColor);
	
	UFUNCTION(BlueprintCallable)
	void SetCardName(const FText& Name);
	
	UFUNCTION(BlueprintCallable)
	void SetFieldPositions(const TArray<EFieldPosition>& FieldPositions);
	
	UFUNCTION(BlueprintCallable)
	void SetBorderVisible(bool bFocused);
	
	UFUNCTION(BlueprintCallable)
	void SetFeetVisible(bool bFeetVisible);

	UFUNCTION(BlueprintCallable)
	void SetFeet(EPreferredFootType Feet);
	
	UFUNCTION(BlueprintCallable)
	void SetBorderBrush(FSlateBrush Brush);

	UFUNCTION(BlueprintCallable)
	void SetPortraitBrush(FSlateBrush Brush);

	
protected:
	UPROPERTY(EditAnywhere, Category = "FootballerCard|Appearance")
	FLinearColor CardBackgroundColor;
	
	UPROPERTY(EditAnywhere, Category = "FootballerCard|Appearance")
	FLinearColor NameBackgroundColor;
	
	UPROPERTY(EditAnywhere, Category = "FootballerCard|Appearance")
	FTextBlockStyle NameTextBlockStyle;

	UPROPERTY(EditAnywhere, Category = "FootballerCard|Appearance")
	FText Name;

	UPROPERTY(EditAnywhere, Category = "FootballerCard|Appearance")
	EPreferredFootType Feet;
	
	UPROPERTY(EditAnywhere, Category = "FootballerCard|Appearance")
	FSlateBrush BorderBrush;

	UPROPERTY(EditAnywhere, Category = "FootballerCard|Appearance")
	FSlateBrush PortraitBrush;

	UPROPERTY(EditAnywhere, Category = "FootballerCard|Appearance")
	FSlateBrush FootLeftBrush;

	UPROPERTY(EditAnywhere, Category = "FootballerCard|Appearance")
	FSlateBrush FootRightBrush;
	
	UPROPERTY(EditAnywhere, Category = "FootballerCard|Appearance")
	FSlateBrush FootBothBrush;

	UPROPERTY(EditAnywhere, Category = "FootballerCard|Appearance")
	bool bFocused;

	UPROPERTY(EditAnywhere, Category = "FootballerCard|Appearance")
	bool bFeetVisible;

	UPROPERTY(EditAnywhere, Category = "FootballerPosition|Appearance")
	FTextBlockStyle FootballerPositionTextBlockStyle;

	UPROPERTY(EditAnywhere, Category = "FootballerPosition|Appearance")
	TArray<EFieldPosition> FieldPositions;
};
