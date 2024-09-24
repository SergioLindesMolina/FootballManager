// Copyright, 2023, by NGD Studios AB. All rights reserved.

#pragma once

#include <CoreMinimal.h>
#include <Widgets/SBoxPanel.h>

#include <BaseClasses/SMaterialProgressbar.h>
#include <Football/CoreClasses/DataStructures/Footballer.h>


/**
 * Draw a random number of stars one besides other.
 * Used to display rating from footballers.
 */
class FOOTBALL_API SRatingBar final : public SMaterialProgressbar
{
public:

	SLATE_BEGIN_ARGS(SRatingBar)
		: _StarsSize(160,32)
		, _SegmentsAmount(5)
		, _EmptyBackgroundColor(FColor::Black)
		, _EmptyBorderColor(FColor::FromHex("1D1D1D"))
	{
	}

	SLATE_ARGUMENT(FVector2D, StarsSize)
	SLATE_ARGUMENT(int32, SegmentsAmount)
	SLATE_ARGUMENT(FLinearColor, EmptyBackgroundColor)
	SLATE_ARGUMENT(FLinearColor, EmptyBorderColor)
	SLATE_STYLE_ARGUMENT(FTextBlockStyle, TextBlockStyle)

	SLATE_END_ARGS()

public:
	void Construct(const FArguments& InArgs);
	
public:
	void SetSegmentsAmount(int32 Amount) const;
	void SetEmptyBackgroundColor(const FLinearColor& Color);
	void SetEmptyBorderColor(const FLinearColor& Color);
	void SetLevelColor(ERatingLevel Level) const;
};
