// Copyright, 2023, by NGD Studios AB. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/Widget.h"
#include "Football/CoreClasses/DataStructures/Footballer.h"
#include "UserInterface/Public/Style/DefaultStyle.h"
#include "RatingBarWidget.generated.h"

/**
 * @see SRatingBar
 */
UCLASS(meta = (DisplayName = "Rating Bar"))
class FOOTBALL_API URatingBarWidget final : public UWidget
{
	GENERATED_BODY()

protected:
	TSharedRef<SWidget> RebuildWidget() override;
	void ReleaseSlateResources(bool bReleaseChildren) override;
	void SynchronizeProperties() override;

#if WITH_EDITOR
	const FText GetPaletteCategory() override { return INVTEXT("Football"); }
#endif

public:
	UFUNCTION(BlueprintCallable)
	void SetCurrentStars(float CurrentStars);

	UFUNCTION(BlueprintCallable)
	void SetNumericValue(float NumericValue);
	
	UFUNCTION(BlueprintCallable)
	void SetMaxStars(int32 MaxAmount);
	
	UFUNCTION(BlueprintCallable)
	void UpdateLevel(ERatingLevel InLevel) const;

	UFUNCTION(BlueprintCallable)
	void SetEmptyBackgroundColor(const FLinearColor& Color);

	UFUNCTION(BlueprintCallable)
	void SetEmptyBorderColor(const FLinearColor& Color);
	
protected:
	UPROPERTY(EditAnywhere, Category="Appearance")
	FTextBlockStyle TextBlockStyle = FCoreStyle::Get().GetWidgetStyle<FTextBlockStyle>("NormalText");
	
	UPROPERTY(EditAnywhere, Category = "Appearance")
	FVector2D StarsSize = FVector2D(160, 32);

	UPROPERTY(EditAnywhere, Category = "Appearance")
	float CurrentStars = 3;

	UPROPERTY(EditAnywhere, Category = "Appearance")
	int32 MaxStars = 5;

	UPROPERTY(EditAnywhere, Category = "Appearance")
	bool bDisplayText = false;

	UPROPERTY(EditAnywhere, meta=(EditCondition="bDisplayText"), Category = "Appearance")
	float NumericValue = 160;

	UPROPERTY(EditAnywhere, Category = "Appearance")
	FLinearColor EmptyBackgroundColor = FColor::Black;

	UPROPERTY(EditAnywhere, Category = "Appearance")
	FLinearColor EmptyBorderColor = FColor::FromHex("1D1D1D");
	
	UPROPERTY(EditAnywhere, Category = "Appearance")
	ERatingLevel Level = ERatingLevel::Bronze;

private:
	TSharedPtr<class SRatingBar> MyRatingBar;
};
