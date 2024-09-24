// Copyright, 2023, by NGD Studios AB. All rights reserved.

#include "Footballer.h"

#include <Football/UtilsFunctionLibrary.h>
#include <Kismet/DataTableFunctionLibrary.h>


FFootballerData::FFootballerRating FFootballerData::CalculateFootballerRating(const EFieldPosition FieldPosition) const
{
	const UDataTable* RatingWeightsTable  = LoadObject<UDataTable>(nullptr, TEXT("/Game/Football/DataTables/DT_RatingWeights.DT_RatingWeights"));
	const UDataTable* StarsAndLevelsTable = LoadObject<UDataTable>(nullptr, TEXT("/Game/Football/DataTables/DT_StarsAndLevels.DT_StarsAndLevels"));

	check(RatingWeightsTable && StarsAndLevelsTable);
	
	FFootballerRating FootballerRating;
	
	const TArray<FString> PositionPropertiesValues = UDataTableFunctionLibrary::GetDataTableColumnAsString(
		RatingWeightsTable,
		FName(UEnum::GetDisplayValueAsText(FieldPosition).ToString())
	);

	const float TotalPropertiesWeight = FCString::Atof(*PositionPropertiesValues.Last());
	for (int32 i = 0; i < static_cast<int32>(EFootballerAttributes::MAX_COUNT); i++)
	{
		const float PropertyWeight = FCString::Atof(*PositionPropertiesValues[i]);
		FootballerRating.Overall  += Attributes[i] * (PropertyWeight / TotalPropertiesWeight);
	}

	FootballerRating.Potential = FMath::Clamp(FootballerRating.Overall * FMath::RandRange(1.1f, 1.3f), 0, 160);
	FootballerRating.Level     = UUtilsFunctionLibrary::GetRatingLevel(StarsAndLevelsTable, FootballerRating.Overall);
	FootballerRating.Stars     = UUtilsFunctionLibrary::GetRatingStars(StarsAndLevelsTable, FootballerRating.Overall, FootballerRating.Level);

	return FootballerRating;
}
