﻿// Copyright, 2023, by NGD Studios AB. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"
#include "Layout/Margin.h"
#include "Components/PanelSlot.h"

#include "FootballerCardSlot.generated.h"

class SFootballerCard;

/**
 * 
 */
UCLASS()
class FOOTBALL_API UFootballerCardSlot : public UPanelSlot
{
	GENERATED_UCLASS_BODY()

public:
	UE_DEPRECATED(5.1, "Direct access to Padding is deprecated. Please use the getter or setter.")
	/** The padding area between the slot and the content it contains. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Getter, Setter, BlueprintSetter="SetPadding", Category="Layout|Button Slot")
	FMargin Padding;

	UE_DEPRECATED(5.1, "Direct access to HorizontalAlignment is deprecated. Please use the getter or setter.")
	/** The alignment of the object horizontally. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Getter, Setter, BlueprintSetter="SetHorizontalAlignment", Category="Layout|Button Slot")
	TEnumAsByte<EHorizontalAlignment> HorizontalAlignment;

	UE_DEPRECATED(5.1, "Direct access to VerticalAlignment is deprecated. Please use the getter or setter.")
	/** The alignment of the object vertically. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Getter, Setter, BlueprintSetter="SetVerticalAlignment", Category="Layout|Button Slot")
	TEnumAsByte<EVerticalAlignment> VerticalAlignment;

public:

	FMargin GetPadding() const;

	UFUNCTION(BlueprintCallable, Category="Layout|Button Slot")
	void SetPadding(FMargin InPadding);

	EHorizontalAlignment GetHorizontalAlignment() const;

	UFUNCTION(BlueprintCallable, Category="Layout|Button Slot")
	void SetHorizontalAlignment(EHorizontalAlignment InHorizontalAlignment);

	EVerticalAlignment GetVerticalAlignment() const;

	UFUNCTION(BlueprintCallable, Category="Layout|Button Slot")
	void SetVerticalAlignment(EVerticalAlignment InVerticalAlignment);

	// UPanelSlot interface
	void SynchronizeProperties() override;
	// End of UPanelSlot interface

	/** Builds the underlying slot for the slate button. */
	void BuildSlot(const TSharedRef<SFootballerCard>& InButton);

	void ReleaseSlateResources(bool bReleaseChildren) override;

private:

	/** A pointer to the button to allow us to adjust the size, padding...etc at runtime. */
	TWeakPtr<SFootballerCard> Button;
};
