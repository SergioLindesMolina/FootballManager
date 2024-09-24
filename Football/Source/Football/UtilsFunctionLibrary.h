// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <CoreMinimal.h>
#include <Kismet/BlueprintFunctionLibrary.h>

#include "Match/MatchDefs.h"

#include "UtilsFunctionLibrary.generated.h"

USTRUCT(BlueprintType)
struct FPlayingPositionToRoleData : public FTableRowBase
{
	GENERATED_BODY()

	//'Name' column must be a 'EFieldPosition'

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<EFootballerRole> PossibleRoles;
};

USTRUCT(BlueprintType)
struct FFootballerPlayingPositionToLocalizedTextData : public FTableRowBase
{
	GENERATED_BODY()

	// 'Name' as Playing Position
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText LocalizedText;
};

/**
 * Some utils functions exposed to blueprints
 */
UCLASS()
class FOOTBALL_API UUtilsFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, BlueprintPure)
	static FText GetTextOfPosition(const UDataTable* PositionToTextTable, EFieldPosition Position);
	
	UFUNCTION(BlueprintCallable, BlueprintPure)
	static TArray<EFootballerRole> GetPossibleRoles(const UDataTable* PositionToRolesTable, EFieldPosition Position);

	UFUNCTION(BlueprintCallable)
	static EFootballerLineUp GetLineupFromText(FText Name);

	UFUNCTION(BlueprintCallable)
	static float GetRatingStars(const UDataTable* StarsAndLevelsTable, const float CallerRating, const ERatingLevel CallerLevel);

	UFUNCTION(BlueprintCallable)
	static ERatingLevel GetRatingLevel(const UDataTable* StarsAndLevelsTable, const float CallerRating);

	/*
	* From blueprint the WidgetTree of a widget is nos accessible so a helper functions was needed to enable that.
	*/
	UFUNCTION(BlueprintCallable, BlueprintPure)
	static TArray<UWidget*> GetChildWidgetsOfType(const UUserWidget* UserWidget, TSubclassOf<UWidget> Type);

	/*
	* source :https://forums.unrealengine.com/t/how-to-detect-true-widget-visibility/414922/3
	* Is necessary to check all the parents visibility property to know if a widget is currently visible on the screen because the Visibility
	* property of the widgets can be set to visible but be hidden cause one of his parents is hidden, also the geometry is cached once it has 
	* been drawn so is not reliable information
	*/
	static bool IsWidgetVisibleOnScreen(const UWidget* Widget);
};
