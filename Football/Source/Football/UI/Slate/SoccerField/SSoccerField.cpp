// Copyright, 2023, by NGD Studios AB. All rights reserved.

#include "SSoccerField.h"

#include <SlateMaterialBrush.h>

#include "Football/UI/GlobalColorsBFL.h"


class SSoccerField_Position final : public SButton
{
public:
	SLATE_BEGIN_ARGS(SSoccerField_Position)
	: _FieldPositionButtonDefaultStyle(&FCoreStyle::Get().GetWidgetStyle<FButtonStyle>("Button"))
	, _FieldPositionButtonSelectedStyle(&FCoreStyle::Get().GetWidgetStyle<FButtonStyle>("Button"))
	, _DefaultColor(FColor::FromHex("#F24271"))
	, _SelectColor(FColor::FromHex("#F24271"))
	, _HoverColor(FColor::FromHex("#EBAFBF"))
	{}

	SLATE_ARGUMENT(const FButtonStyle*, FieldPositionButtonDefaultStyle)
	SLATE_ARGUMENT(const FButtonStyle*, FieldPositionButtonSelectedStyle)

	
	SLATE_ARGUMENT(EFieldPosition, FieldPosition)
	SLATE_EVENT(FInteractablePositionClicked, InteractablePositionClicked)
	
	SLATE_ARGUMENT(FVector2D, Position)
	
	SLATE_ARGUMENT(FSlateColor, DefaultColor)
	SLATE_ARGUMENT(FSlateColor, SelectColor)
	SLATE_ARGUMENT(FSlateColor, HoverColor)

	SLATE_END_ARGS()

public:
	void Construct(const FArguments& InArgs)
	{
		ButtonDefaultStyle                   = *InArgs._FieldPositionButtonDefaultStyle;
		ButtonDefaultStyle.Normal.TintColor  = InArgs._DefaultColor;
		ButtonDefaultStyle.Hovered.TintColor = InArgs._HoverColor;
		ButtonDefaultStyle.Pressed.TintColor = InArgs._SelectColor;

		ButtonSelectedStyle                   = *InArgs._FieldPositionButtonSelectedStyle;
		ButtonSelectedStyle.Normal.TintColor  = InArgs._DefaultColor;
		ButtonSelectedStyle.Hovered.TintColor = InArgs._HoverColor;
		ButtonSelectedStyle.Pressed.TintColor = InArgs._SelectColor;		
		
		Position                      = InArgs._Position;
		FieldPosition                 = InArgs._FieldPosition;
		OnInteractablePositionClicked = InArgs._InteractablePositionClicked;
		
		SButton::Construct(SButton::FArguments()
			.ButtonStyle(&ButtonDefaultStyle)
			.ContentPadding(0)
			.OnClicked(this, &SSoccerField_Position::OnClicked)
		);
	}

	const FVector2D& GetPosition() const
	{
		return Position;
	}

	EFieldPosition GetFieldPosition() const
	{
		return FieldPosition;
	}

	void SetSelectedStyle(const bool bInSelected)
	{
		bSelected = bInSelected;
		SetButtonStyle(bSelected ? &ButtonSelectedStyle : &ButtonDefaultStyle);
	}

private:
	FReply OnClicked()
	{
		SetSelectedStyle(!bSelected);
		if(OnInteractablePositionClicked.ExecuteIfBound(FieldPosition, bSelected))
		{
			return FReply::Handled();
		}

		return FReply::Unhandled();
	}

private:
	FButtonStyle ButtonDefaultStyle;
	FButtonStyle ButtonSelectedStyle;
	FVector2D Position;
	bool bSelected {};

	EFieldPosition FieldPosition = EFieldPosition::None;
	FInteractablePositionClicked OnInteractablePositionClicked;
};





void SSoccerField::Construct(const FArguments& InArgs)
{
	check(IsValid(InArgs._FieldMaterial) && "SSoccerField need an instance of UMaterialInterface to works");

	BrushSize = InArgs._DefaultDimensions;

	FieldPositionButtonDefaultStyle   = InArgs._FieldPositionButtonDefaultStyle;
	FieldPositionButtonSelectedStyle  = InArgs._FieldPositionButtonSelectedStyle;

	SetSoccerFieldMaterial(InArgs._FieldMaterial);

	TStaticArray<FLinearColor, 3> InitialValues;
	InitialValues[0] = InArgs._LeftColor.GetSpecifiedColor(); 
	InitialValues[1] = InArgs._MiddleColor.GetSpecifiedColor(); 
	InitialValues[2] = InArgs._RightColor.GetSpecifiedColor(); 
	SetPossessionColors(InitialValues);

	FieldPositionsList = InArgs._FieldPositionsList;
	
	ChildSlot
	[
		SAssignNew(Overlay, SOverlay)
	];
}

void SSoccerField::Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime)
{
	for(const auto& [Widget, _] : Positions)
	{
		FVector2d TransformedPosition = TransformPoint(AllottedGeometry, Widget->GetPosition() * AllottedGeometry.GetLocalSize());
		TransformedPosition -= Widget->GetDesiredSize() / 2; 
		
		Widget->SetRenderTransform(FSlateRenderTransform(TransformedPosition));
	}
	
	
	SSkewingWidget::Tick(AllottedGeometry, InCurrentTime, InDeltaTime);
}

SSoccerField::~SSoccerField()
{
	if(ensure(IsValid(FieldMaterialInstanceDynamic)))
	{
		FieldMaterialInstanceDynamic->RemoveFromRoot();
	}
}

void SSoccerField::SetPossessionValues(const FVector2f& Values) const
{
	if(Values.X + Values.Y > 100)
	{
		UE_LOG(LogTemp, Error, TEXT("Possession values exceed value of 100"));
	}
	
	FieldMaterialInstanceDynamic->SetScalarParameterValue("Percentage (Right)", Values.X);
	FieldMaterialInstanceDynamic->SetScalarParameterValue("Percentage (Left)", Values.Y);
}

void SSoccerField::SetPossessionColors(const TStaticArray<FLinearColor, 3>& Colors) const
{
	for(uint32 i = 0; i < 3; i++)
	{
		SetPossessionColor(i, Colors[i]);
	}
}

void SSoccerField::SetPossessionColor(const uint32 Index, const FLinearColor& Color) const
{
	switch (Index)
	{
		case 0: FieldMaterialInstanceDynamic->SetVectorParameterValue("Tint (Left)",   Color); break;
		case 1: FieldMaterialInstanceDynamic->SetVectorParameterValue("Tint (Middle)", Color); break;
		case 2: FieldMaterialInstanceDynamic->SetVectorParameterValue("Tint (Right)",  Color); break;

		default:
			UE_LOG(LogTemp, Error, TEXT("SetPossessionColor with invalid value"));
			break;
	}
}

void SSoccerField::SetSoccerFieldMaterial(UMaterialInterface* SoccerFieldMaterial)
{
	if(ensureMsgf(IsValid(SoccerFieldMaterial), TEXT("SColoredProgressbar need an instance of UMaterialInterface to works")))
	{
		if(IsValid(FieldMaterialInstanceDynamic))
		{
			FieldMaterialInstanceDynamic->RemoveFromRoot();
		}

		if(FieldBrush.IsValid())
		{
			FieldBrush.Reset();
		}
		
		FieldMaterialInstanceDynamic = UMaterialInstanceDynamic::Create(SoccerFieldMaterial, nullptr);
		FieldMaterialInstanceDynamic->AddToRoot();
		FieldBrush = MakeShareable(new FSlateMaterialBrush(*FieldMaterialInstanceDynamic, BrushSize));

		Brush = FieldBrush.Get();
	}
	else
	{
		FieldBrush = MakeShared<FSlateBrush>(*FCoreStyle::Get().GetBrush("WhiteBrush"));
	}
}

void SSoccerField::ClearInteractablePositions()
{
	Overlay->ClearChildren();
	Positions.Empty();
}

void SSoccerField::AddInteractablePosition(const EFieldPosition FieldPosition, FInteractablePositionClicked InteractablePositionClicked)
{
	// Ignore EFieldPosition::None
	if(FieldPosition == EFieldPosition::None) return;

	const FLinearColor FieldColor = UGlobalColorsBFL::GetFootballerPositionColor(FieldPosition);

	const auto Widget = SNew(SSoccerField_Position)
	.Position(FieldPositionsList[FieldPosition])
	.FieldPositionButtonDefaultStyle(FieldPositionButtonDefaultStyle)
	.FieldPositionButtonSelectedStyle(FieldPositionButtonSelectedStyle)
	.InteractablePositionClicked(InteractablePositionClicked)
	.FieldPosition(FieldPosition)
	.DefaultColor(FieldColor * 2.00f)
	.HoverColor(FieldColor   * 4.00f)
	.SelectColor(FieldColor  * 4.00f);
	
	Overlay->AddSlot()
	.HAlign(HAlign_Left)
	.VAlign(VAlign_Top)
	[
		Widget
	];

	Positions.Add({Widget, InteractablePositionClicked});
}

void SSoccerField::UpdateFieldPositionsList(const FFieldPositionsList& InFieldPositionsList)
{
	FieldPositionsList = InFieldPositionsList;
}

void SSoccerField::ChangeInteractablePositionsStatus(const EFieldPosition FieldPosition, const bool bSelected)
{
	for(const auto& Position : Positions)
	{
		if(Position.Key->GetFieldPosition() == FieldPosition)
		{
			Position.Key->SetSelectedStyle(bSelected);
			break;
		}	
	}
}

void SSoccerField::ChangeAllInteractablePositionsStatus(const bool bSelected)
{
	for(const auto& Position : Positions)
	{
		Position.Key->SetSelectedStyle(bSelected);
	}
}
