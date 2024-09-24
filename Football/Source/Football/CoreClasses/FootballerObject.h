// Copyright, 2023, by NGD Studios AB. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Football/CoreClasses/DataStructures/Footballer.h"
#include "FootballerObject.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnUpdateRating);

/**
 * Object that holds a FFootballerData struct.
 * This object serves several purposes: Memory management, passes around the data object to and from blueprints, call delegates
 * Think of UWidget -> Slate relationship
 * @see FFootballerData
 * @note Please font expose Data variable to Blueprints!
 */
UCLASS(BlueprintType)
class FOOTBALL_API UFootballerObject : public UObject
{
	GENERATED_BODY()
	
public:
	//void GenerateRatingProperties(const UDataTable* RatingWeightsTable, const UDataTable* StarsAndLevelsTable);

	FFootballerData Data;

	UPROPERTY(BlueprintAssignable)
	FOnUpdateRating OnUpdateRating;

	UFUNCTION(BlueprintCallable)
	EFootballerLineUp GetLineUpPosition() const;

	UFUNCTION(BlueprintCallable)
	TArray<EFieldPosition> GetDesiredPositions() const;

	UFUNCTION(BlueprintCallable)
	EFieldPosition GetSelectedFieldPosition() const;

	UFUNCTION(BlueprintCallable)
	FString GetName() const;

	UFUNCTION(BlueprintCallable)
	FString GetDisplayName() const;

	UFUNCTION(BlueprintCallable)
	uint8 GetNumber() const;

	UFUNCTION(BlueprintCallable)
	void GetRating(float& Stars, float& Overall, float &Potential, ERatingLevel &Level) const;

	UFUNCTION(BlueprintCallable)
	int32 GetId() const;

	UFUNCTION(BlueprintCallable)
	TArray<FString> GetAllProperties() const;

	UFUNCTION(BlueprintCallable)
	float GetShootingAttribute() const;

	UFUNCTION(BlueprintCallable)
	EPreferredFootType GetPreferredFoot() const;

	UFUNCTION(BlueprintCallable)
	float GetAfinityWithManager() const;

	UFUNCTION(BlueprintCallable)
	ESpecialTrait GetSpecialTrait() const;

	//Todo David: Move it to something editor only
	UFUNCTION(BlueprintCallable)
	void SetKickerPreviewInfo(const FString& InName, EPreferredFootType Foot, uint8 InNumber, EFieldPosition FieldPosition);

};
