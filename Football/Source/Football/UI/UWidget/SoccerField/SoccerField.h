// Copyright, 2023, by NGD Studios AB. All rights reserved.

#pragma once

#include <Components/Widget.h>
#include <Football/CoreClasses/DataStructures/Footballer.h>

#include "SoccerField.generated.h"

enum class EFieldPosition : uint8;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FInteractablePositionClicked_Blueprint, EFieldPosition, FieldPosition, bool, bSelected);


UCLASS()
class FOOTBALL_API USoccerField : public UWidget
{
	GENERATED_BODY()
	
protected:
	// Begin UWidget interface
	TSharedRef<SWidget> RebuildWidget() override;
	void SynchronizeProperties() override;
	void ReleaseSlateResources(bool bReleaseChildren) override;
	// End UWidget interface

	#if WITH_EDITOR
	const FText GetPaletteCategory() override { return FText::FromString("Football"); }
	#endif

public:
	UFUNCTION(BlueprintCallable)
	void ClearInteractablePosition();
	
	UFUNCTION(BlueprintCallable)
	void AddInteractablePosition(EFieldPosition FieldPosition);

	UFUNCTION(BlueprintCallable)
	void InteractablePositionClicked(EFieldPosition FieldPosition, bool bSelected);

	UFUNCTION(BlueprintCallable)
	void ChangeInteractablePositionsStatus(EFieldPosition FieldPosition, bool bSelected);

	UFUNCTION(BlueprintCallable)
	void ChangeAllInteractablePositionsStatus(bool bSelected);

	UFUNCTION(BlueprintCallable)
	void SetPossessionValues(const FVector2f& PossessionValues);
	
protected:
	UPROPERTY(EditAnywhere, Category=Appearance)
	UMaterialInterface* SoccerMaterial = LoadObject<UMaterialInterface>(nullptr, TEXT("/UserInterface/M_SoccerField.M_SoccerField"));

	UPROPERTY(EditAnywhere, Category=Appearance)
	FButtonStyle FieldPositionButtonDefaultStyle = *LoadObject<USlateWidgetStyleAsset>(nullptr, TEXT("/UserInterface/SoccerFieldProfiler/Style_FieldPositionButtonDefault.Style_FieldPositionButtonDefault"))->GetStyle<FButtonStyle>();

	UPROPERTY(EditAnywhere, Category=Appearance)
	FButtonStyle FieldPositionButtonSelectedStyle = *LoadObject<USlateWidgetStyleAsset>(nullptr, TEXT("/UserInterface/SoccerFieldProfiler/Style_FieldPositionButtonSelected.Style_FieldPositionButtonSelected"))->GetStyle<FButtonStyle>();
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Appearance)
	TArray<EFieldPosition> FieldPositions;

	/** Possession Values */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Appearance)
	FVector2f PossessionValues;

	/** Possession Color Left */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Appearance)
	FLinearColor PossessionColorLeft = FColor::FromHex("#9BFF8DFF");

	/** Possession Color Middle */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Appearance)
	FLinearColor PossessionColorMiddle = FColor::FromHex("#4A7844FF");
	
	/** Possession Color Right */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Appearance)
	FLinearColor PossessionColorRight = FColor::FromHex("#9BFF8DFF");

	/** Lattice Amount */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Appearance)
	float LatticeAmount = 0.2f;

	/** Lattice Size */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Appearance)
	int32 LatticeSize = 8;

	/** Should draw a adjacent shadow? */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Appearance)
	bool bDrawShadow = true;

	/** If draw shadow, how much offset should be displaced */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Appearance)
	FVector2f ShadowOffset {.05f, .05f};
	
protected:
	TSharedPtr<class SSoccerField> MySoccerField;

public:
	UPROPERTY(BlueprintAssignable)
	FInteractablePositionClicked_Blueprint OnInteractablePositionClicked;
};

