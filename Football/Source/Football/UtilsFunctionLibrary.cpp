// Fill out your copyright notice in the Description page of Project Settings.

#include "UtilsFunctionLibrary.h"
#include "Team/TeamGenerator.h"
#include "Kismet/DataTableFunctionLibrary.h"
#include "Blueprint/WidgetTree.h"

FText UUtilsFunctionLibrary::GetTextOfPosition(const UDataTable* PositionToTextTable, EFieldPosition Position)
{
	FFootballerPlayingPositionToLocalizedTextData* TextData = PositionToTextTable->FindRow<FFootballerPlayingPositionToLocalizedTextData>(FName(UEnum::GetDisplayValueAsText(Position).ToString()), nullptr);

	return TextData->LocalizedText;
}

EFootballerLineUp UUtilsFunctionLibrary::GetLineupFromText(FText Name)
{
	int64 LineupIndex = StaticEnum<EFootballerLineUp>()->GetValueByNameString(Name.ToString());

	if (LineupIndex == INDEX_NONE) 
	{
		UE_LOG(LogTemp, Error, TEXT("Invalid Name to find Lineup enum value"));
	}

	return EFootballerLineUp(LineupIndex);
}

float UUtilsFunctionLibrary::GetRatingStars(const UDataTable* StarsAndLevelsTable, const float CallerRating, const ERatingLevel CallerLevel)
{	
	if (!StarsAndLevelsTable)
	{
		UE_LOG(LogTemp, Error, TEXT("StarsAndLevelsTable was null, the stars value couldn't be calculated"));
		return 0;
	}

	FName LevelName = FName(UEnum::GetDisplayValueAsText(CallerLevel).ToString());

	if (FStarsAndLevelsData* CurrentLevelRow = StarsAndLevelsTable->FindRow<FStarsAndLevelsData>(LevelName, TEXT(__FILE__)))
	{	
		float StarsValue = (CallerRating - CurrentLevelRow->MinRating) / CurrentLevelRow->StarCost;
		
		return StarsValue;		
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Was not possible to find an apropiate Level inside StarsAndLevelsTable with the name %s"), *LevelName.ToString());
		return 0;
	}		
}

ERatingLevel UUtilsFunctionLibrary::GetRatingLevel(const UDataTable* StarsAndLevelsTable, const float CallerRating)
{
	ERatingLevel SelectedLevel = ERatingLevel::Bronze;

	if (!StarsAndLevelsTable)
	{
		UE_LOG(LogTemp, Error, TEXT("StarsAndLevelsTable was null so Bronze was assigned as level"));
		return SelectedLevel;
	}

	TArray<FName> LevelsRowNames = StarsAndLevelsTable->GetRowNames();
	TArray<FString> MinColumnValues = UDataTableFunctionLibrary::GetDataTableColumnAsString(StarsAndLevelsTable, FName("MinRating"));

	FName SelectedLevelName = LevelsRowNames.Last();

	for (int32 i = 0; i < MinColumnValues.Num(); i++)
	{
		float CurrentColumnValue = FCString::Atof(*MinColumnValues[i]);

		if (CallerRating < CurrentColumnValue)
		{
			SelectedLevelName = LevelsRowNames[FMath::Clamp(i - 1, 0, MinColumnValues.Num())];
			break;
		}
	}

	SelectedLevel = (ERatingLevel)StaticEnum<ERatingLevel>()->GetValueByName(SelectedLevelName);

	return SelectedLevel;
}

TArray<UWidget*> UUtilsFunctionLibrary::GetChildWidgetsOfType(const UUserWidget* UserWidget, TSubclassOf<UWidget> Type)
{
	TArray<UWidget*> WidgetsFound;

	TObjectPtr<UWidgetTree> UserWidgetTree = UserWidget->WidgetTree;
	
	if (ensure(UserWidgetTree))
	{	
		UserWidgetTree->ForEachWidget([&WidgetsFound, Type](UWidget* Widget) 
			{
				if (Widget && Widget->IsA(Type))
				{
					WidgetsFound.Add(Widget);
				}
			});
	}

	return WidgetsFound;
}


bool UUtilsFunctionLibrary::IsWidgetVisibleOnScreen(const UWidget* Widget)
{
	bool ResultVisibility = false;

	const UWidget* CurrentWidget = Widget;

	while (CurrentWidget)
	{
		// WARNING: don't use outerWidget->IsVisible() since that uses inner slate widget which might not yet be initialized here!
		// GetVisibility uses the UMG defined visibility which is exactly what we want and need here.
		bool isCurrentVisible = CurrentWidget->GetVisibility() == ESlateVisibility::Visible ||
			CurrentWidget->GetVisibility() == ESlateVisibility::HitTestInvisible ||
			CurrentWidget->GetVisibility() == ESlateVisibility::SelfHitTestInvisible;

		ResultVisibility = isCurrentVisible;

		if (!ResultVisibility)
		{
			break;
		}
		
		UWidget* NextHierarchyWidget = CurrentWidget->GetParent();

		// if outerWidget is nullptr it means we reached the root container of the current UserWidget...
		if (!NextHierarchyWidget)
		{
			//...Get the WidgetTree...
			if (UWidgetTree* CurrentWidgetTree = Cast<UWidgetTree>(CurrentWidget->GetOuter()))
			{
				//...and the corresponding parent UserWidget...
				if (UUserWidget* CurrentUserWidget = Cast<UUserWidget>(CurrentWidgetTree->GetOuter()))
				{
					//...and take it as UWidget to consider in next loop
					NextHierarchyWidget = CurrentUserWidget;
				}
			}
		}

		CurrentWidget = NextHierarchyWidget;
	}

	return ResultVisibility;
}

TArray<EFootballerRole> UUtilsFunctionLibrary::GetPossibleRoles(const UDataTable* PositionToRolesTable, EFieldPosition Position)
{
	//TODO David: Change this data layout, use first column as FieldPosition and search for the first one, do not lookup for the FName
	FPlayingPositionToRoleData* Data = PositionToRolesTable->FindRow<FPlayingPositionToRoleData>(FName(UEnum::GetDisplayValueAsText(Position).ToString()), nullptr);

	return Data->PossibleRoles;
}
