// Copyright, 2023, by NGD Studios AB. All rights reserved.

#include "GlobalColorsBFL.h"

std::array<FColor, static_cast<size_t>(ERatingLevel::MAX_COUNT)> UGlobalColorsBFL::RatingLevelColors =
{
	FColor::FromHex("8B4513"),
	FColor::FromHex("C0C0C0"),
	FColor::FromHex("FFC42D"),
	FColor::FromHex("3285b7")
};

std::array<FColor, static_cast<size_t>(EFieldPosition::MAX_COUNT)> UGlobalColorsBFL::FieldPositionColors =
{
	// None color
	FColor::FromHex("00FFFF"),
	
	// Levels colors
	FColor::FromHex("051692"),
	FColor::FromHex("025620"),
	FColor::FromHex("025620"),
	FColor::FromHex("025620"),
	FColor::FromHex("016B6B"),           
	FColor::FromHex("584101"),
	FColor::FromHex("584101"),
	FColor::FromHex("584101"),
	FColor::FromHex("932304"),
	FColor::FromHex("932304"),
	FColor::FromHex("932304"),
	FColor::FromHex("9C0211")
};

FColor UGlobalColorsBFL::GetRatingColor(ERatingLevel RatingLevel)
{
	return RatingLevelColors[static_cast<size_t>(RatingLevel)];
}

FColor UGlobalColorsBFL::GetFootballerPositionColor(EFieldPosition FieldPosition)
{
	return FieldPositionColors[static_cast<size_t>(FieldPosition)];
}
