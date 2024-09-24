// Copyright, 2023, by NGD Studios AB. All rights reserved.

#include "RatingBarWidget.h"
#include "Football/UI/Slate/RatingBar/SRatingBar.h"
//#include "Engine/Source/Runtime/Slate/Public/Widgets/Text/STextBlock.h"
//#include "SlateCore/Public/Widgets/SBoxPanel.h"
#include "Styling/SlateTypes.h"


void URatingBarWidget::ReleaseSlateResources(const bool bReleaseChildren)
{
	Super::ReleaseSlateResources(bReleaseChildren);
	MyRatingBar.Reset();
}

void URatingBarWidget::SynchronizeProperties()
{
	Super::SynchronizeProperties();

	if (MyRatingBar.IsValid())
	{
		MyRatingBar->SetSegmentsAmount(5);

		SetCurrentStars(CurrentStars);
		SetNumericValue(NumericValue);
		SetMaxStars(MaxStars);
		
		SetEmptyBackgroundColor(EmptyBackgroundColor);
		SetEmptyBorderColor(EmptyBorderColor);

		MyRatingBar->SetProgressBarBrushSize(StarsSize);
		MyRatingBar->SetLevelColor(Level);
		MyRatingBar->SetTextVisibility(bDisplayText);
	}
}

void URatingBarWidget::SetCurrentStars(const float InCurrentStars)
{
	CurrentStars = InCurrentStars;
	MyRatingBar->SetFillPercentage(CurrentStars / static_cast<float>(MaxStars));
}

void URatingBarWidget::SetNumericValue(const float InNumericValue)
{
	NumericValue = InNumericValue;
	MyRatingBar->SetNumericValue(NumericValue);
}

void URatingBarWidget::SetMaxStars(const int32 MaxAmount)
{
	MaxStars = MaxAmount;
	MyRatingBar->SetSegmentsAmount(MaxStars);
}

void URatingBarWidget::UpdateLevel(const ERatingLevel InLevel) const
{
	MyRatingBar->SetLevelColor(InLevel);
}

void URatingBarWidget::SetEmptyBackgroundColor(const FLinearColor& Color)
{
	MyRatingBar->SetEmptyBackgroundColor(Color);
	
}

void URatingBarWidget::SetEmptyBorderColor(const FLinearColor& Color)
{
	MyRatingBar->SetEmptyBorderColor(Color);
}

TSharedRef<SWidget> URatingBarWidget::RebuildWidget()
{
	MyRatingBar = SNew(SRatingBar)
		.SegmentsAmount(MaxStars)
		.StarsSize(StarsSize)
		.TextBlockStyle(&TextBlockStyle)
		.EmptyBackgroundColor(EmptyBackgroundColor)
		.EmptyBorderColor(EmptyBorderColor);

	MyRatingBar->SetFillPercentage(CurrentStars / 5.f);
	MyRatingBar->SetNumericValue(NumericValue);
	MyRatingBar->SetLevelColor(Level);
	
	return MyRatingBar.ToSharedRef();
}
