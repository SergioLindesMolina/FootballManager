// Copyright, 2023, by NGD Studios AB. All rights reserved.

#include "FootballerCardSlot.h"

#include <Widgets/SNullWidget.h>
#include <Components/Widget.h>

#include <Football/UI/Slate/FootballerCard/SFootballerCard.h>


UFootballerCardSlot::UFootballerCardSlot(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
PRAGMA_DISABLE_DEPRECATION_WARNINGS
	Padding = FMargin(4.f, 2.f);

	HorizontalAlignment = HAlign_Center;
	VerticalAlignment = VAlign_Center;
PRAGMA_ENABLE_DEPRECATION_WARNINGS
}

void UFootballerCardSlot::ReleaseSlateResources(const bool bReleaseChildren)
{
	Super::ReleaseSlateResources(bReleaseChildren);

	Button.Reset();
}

void UFootballerCardSlot::BuildSlot(const TSharedRef<SFootballerCard>& InButton)
{
	//Button = InButton;
	
PRAGMA_DISABLE_DEPRECATION_WARNINGS
	InButton->SetContentPadding(Padding);
	InButton->SetHAlign(HorizontalAlignment);
	InButton->SetVAlign(VerticalAlignment);
PRAGMA_ENABLE_DEPRECATION_WARNINGS

	InButton->SetContent(Content ? Content->TakeWidget() : SNullWidget::NullWidget);

	Button = InButton;
}

PRAGMA_DISABLE_DEPRECATION_WARNINGS
FMargin UFootballerCardSlot::GetPadding() const
{
	return Padding;
}

void UFootballerCardSlot::SetPadding(FMargin InPadding)
{
	Padding = InPadding;
	if (Button.IsValid())
	{
		StaticCastSharedPtr<SFootballerCard>(Button.Pin())->SetContentPadding(InPadding);
	}
}

EHorizontalAlignment UFootballerCardSlot::GetHorizontalAlignment() const
{
	return HorizontalAlignment;
}

void UFootballerCardSlot::SetHorizontalAlignment(const EHorizontalAlignment InHorizontalAlignment)
{
	HorizontalAlignment = InHorizontalAlignment;
	if (Button.IsValid())
	{
		StaticCastSharedPtr<SFootballerCard>(Button.Pin())->SetHAlign(InHorizontalAlignment);
	}
}

EVerticalAlignment UFootballerCardSlot::GetVerticalAlignment() const
{
	return VerticalAlignment;
}

void UFootballerCardSlot::SetVerticalAlignment(const EVerticalAlignment InVerticalAlignment)
{
	VerticalAlignment = InVerticalAlignment;
	if ( Button.IsValid() )
	{
		StaticCastSharedPtr<SFootballerCard>(Button.Pin())->SetVAlign(InVerticalAlignment);
	}
}
PRAGMA_ENABLE_DEPRECATION_WARNINGS

void UFootballerCardSlot::SynchronizeProperties()
{
PRAGMA_DISABLE_DEPRECATION_WARNINGS
	SetPadding(Padding);
	SetHorizontalAlignment(HorizontalAlignment);
	SetVerticalAlignment(VerticalAlignment);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
}
