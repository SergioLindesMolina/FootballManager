// Copyright, 2023, by NGD Studios AB. All rights reserved.

#pragma once

#include <CoreMinimal.h>
#include <Components/Widget.h>

#include <Football/CoreClasses/DataStructures/Footballer.h>

#include "FootballerPosition.generated.h"

class UStringTable;

/**
 * 
 */
UCLASS()
class FOOTBALL_API UFootballerPosition : public UWidget
{
	GENERATED_BODY()

protected:
	UFootballerPosition();
	
	TSharedRef<SWidget> RebuildWidget() override;
	void ReleaseSlateResources(bool bReleaseChildren) override;
	void SynchronizeProperties() override;

#if WITH_EDITOR
	const FText GetPaletteCategory() override { return INVTEXT("Football"); }
#endif

public:
	UFUNCTION(BlueprintCallable)
	void SetFieldPositions(const TArray<EFieldPosition>& InFieldPositions);

	UFUNCTION(BlueprintCallable)
	void SetFillFlags(bool bFill);

protected:
	UPROPERTY(EditAnywhere, Category = "FootballerPosition|Appearance")
	FTextBlockStyle TextBlockStyle;

	UPROPERTY(EditAnywhere, Category = "FootballerPosition|Appearance")
	TArray<EFieldPosition> FieldPositions;

	UPROPERTY(EditAnywhere, Category = "FootballerPosition|Appearance")
	UStringTable* LocalizationString;

	UPROPERTY(EditAnywhere, Category = "FootballerPosition|Appearance")
	bool bDarkMode {};

	UPROPERTY(EditAnywhere, Category = "FootballerPosition|Appearance")
	bool bFillFlags = true;

	UPROPERTY(EditAnywhere, Category = "FootballerPosition|Appearance")
    float Padding = 5;
	
private:
	TSharedPtr<class SFootballerPosition> MyFootballerPosition;
};
