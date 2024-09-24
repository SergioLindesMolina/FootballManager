// Copyright, 2023, by NGD Studios AB. All rights reserved.

#include "Football/UI/Slate/RatingBar/SRatingBar.h"
#include <Football/UI/GlobalColorsBFL.h>


void SRatingBar::Construct(const FArguments& InArgs)
{
	SMaterialProgressbar::Construct(
		SMaterialProgressbar::FArguments()
		.ProgressBarMaterial(LoadObject<UMaterialInterface>(nullptr, TEXT("/Script/Engine.Material'/Game/Football/UI/Shaders/RatingBar/M_StarTest.M_StarTest'")))
		.TextVisibility(false)
		.TextBlockStyle(InArgs._TextBlockStyle)
	);

	SetNumericValue(75);
	
	SetSegmentsAmount(InArgs._SegmentsAmount);
	SetEmptyBackgroundColor(InArgs._EmptyBackgroundColor);
	SetEmptyBorderColor(InArgs._EmptyBorderColor);
	
	SetProgressBarBrushSize(InArgs._StarsSize);
	SetLevelColor(ERatingLevel::Bronze);
}

void SRatingBar::SetSegmentsAmount(const int32 Amount) const
{
	MaterialInstanceDynamic->SetScalarParameterValue("SegmentsAmount", static_cast<float>(Amount));
}

void SRatingBar::SetEmptyBackgroundColor(const FLinearColor& Color)
{
	MaterialInstanceDynamic->SetVectorParameterValue("BackgroundInsideColor", Color);
}

void SRatingBar::SetEmptyBorderColor(const FLinearColor& Color)
{
	MaterialInstanceDynamic->SetVectorParameterValue("BackgroundBorderColor", Color);
}

void SRatingBar::SetLevelColor(const ERatingLevel Level) const
{
	MaterialInstanceDynamic->SetVectorParameterValue("FillColor", UGlobalColorsBFL::GetRatingColor(Level));
}

