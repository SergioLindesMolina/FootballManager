// Copyright, 2023, by NGD Studios AB. All rights reserved.

#pragma once
 
#include <CoreMinimal.h>
#include <Containers/StaticArray.h>

#include <BaseClasses/SSkewingWidget.h>
#include <Style/DefaultStyle.h>

#include "Football/UI/UserWidget/Shared/ChipFootballer/ChipFootballerWidget.h"

enum class EFieldPosition : uint8;
DECLARE_DELEGATE_TwoParams(FInteractablePositionClicked, EFieldPosition /*FieldPosition*/, bool /*bSelected*/);

/**
 * Draw a SoccerField with the ability to add sub-elements (which will be the positions of the players), and the ability
 * to interact with the mouse (click, hover).
 * @see https://nimblegiant.atlassian.net/browse/FTB1-1401
 */
class FOOTBALL_API SSoccerField final : public SSkewingWidget
{
	typedef TMap<EFieldPosition, FVector2D> FFieldPositionsList;
	
public:
	SLATE_BEGIN_ARGS(SSoccerField)
	: _FieldMaterial(LoadObject<UMaterialInterface>(nullptr, TEXT("/UserInterface/M_SoccerField.M_SoccerField")))
	, _DefaultDimensions({684, 452})
	, _LeftColor(FColor::FromHex("#9BFF8DFF"))
	, _MiddleColor(FColor::FromHex("#4A7844FF"))
	, _RightColor(FColor::FromHex("#9BFF8DFF"))
	, _FieldPositionsList(
		{
			{ EFieldPosition::GK,	FVector2D(0.50, 0.950) },
			{ EFieldPosition::DL,	FVector2D(0.15, 0.725) },
			{ EFieldPosition::DC, 	FVector2D(0.50, 0.800) },
			{ EFieldPosition::DR, 	FVector2D(0.85, 0.725) },
			{ EFieldPosition::DM, 	FVector2D(0.50, 0.650) },
			{ EFieldPosition::ML, 	FVector2D(0.15, 0.490) },
			{ EFieldPosition::MC, 	FVector2D(0.50, 0.490) },
			{ EFieldPosition::MR, 	FVector2D(0.85, 0.490) },
			{ EFieldPosition::AML, 	FVector2D(0.85, 0.275) },
			{ EFieldPosition::AMC, 	FVector2D(0.50, 0.350) },
			{ EFieldPosition::AMR, 	FVector2D(0.15, 0.275) },
			{ EFieldPosition::ST,	FVector2D(0.50, 0.200) }
		})
	, _FieldPositionButtonDefaultStyle(&FCoreStyle::Get().GetWidgetStyle<FButtonStyle>("Button"))
	, _FieldPositionButtonSelectedStyle(&FCoreStyle::Get().GetWidgetStyle<FButtonStyle>("Button"))
	{}

	SLATE_ARGUMENT(UMaterialInterface*, FieldMaterial)
	SLATE_ARGUMENT(FVector2D, DefaultDimensions)
	SLATE_ARGUMENT(FSlateColor, LeftColor)
	SLATE_ARGUMENT(FSlateColor, MiddleColor)
	SLATE_ARGUMENT(FSlateColor, RightColor)
	SLATE_ARGUMENT(FFieldPositionsList, FieldPositionsList)

	SLATE_ARGUMENT(const FButtonStyle*, FieldPositionButtonDefaultStyle)
	SLATE_ARGUMENT(const FButtonStyle*, FieldPositionButtonSelectedStyle)

	SLATE_END_ARGS()
	
public:
	void Construct(const FArguments& InArgs);
	void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;
	~SSoccerField() override;

	void SetPossessionValues(const FVector2f& Values) const;
	void SetPossessionColors(const TStaticArray<FLinearColor, 3>& Colors) const;
	void SetPossessionColor(uint32 Index, const FLinearColor& Color) const;

	void SetSoccerFieldMaterial(UMaterialInterface* SoccerFieldMaterial);
	
public:
	void ClearInteractablePositions();
	void AddInteractablePosition(EFieldPosition FieldPosition, FInteractablePositionClicked InteractablePositionClicked = {});

	void UpdateFieldPositionsList(const FFieldPositionsList& FieldPositionsList);

	void ChangeInteractablePositionsStatus(EFieldPosition FieldPosition, bool bSelected);
	void ChangeAllInteractablePositionsStatus(bool bSelected);
	
private:
	UMaterialInstanceDynamic* FieldMaterialInstanceDynamic = nullptr;
	FVector2D BrushSize;
	TSharedPtr<FSlateBrush> FieldBrush;
	TSharedPtr<SImage> FieldImage;

	const FButtonStyle* FieldPositionButtonDefaultStyle {};
	const FButtonStyle* FieldPositionButtonSelectedStyle {};

	TSharedPtr<SOverlay> Overlay;
	TArray<TPair<TSharedRef<class SSoccerField_Position>, FInteractablePositionClicked>> Positions;
	FFieldPositionsList FieldPositionsList;
};
