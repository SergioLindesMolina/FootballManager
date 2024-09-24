// Copyright, 2023, by NGD Studios AB. All rights reserved.

#pragma once

#include <CoreMinimal.h>
#include <Widgets/Text/STextBlock.h>

#include <UserInterface/Public/UWidget/DualButtonScroll.h>
#include <Interfaces/IButtonContainerBase.h>
#include <Slate/DualButtonScroll/SDualButtonScroll.h>

#include "DBSBCustomSavedTactic.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FDBScrollBoxTrashClicked, int32, Index);

/**
 * Specialization of UDualButtonScroll to display "Custom Tactics"
 */
UCLASS(meta=(DisplayName="DualButtonScrollBox (Custom Tactic Saved Button)"))
class FOOTBALL_API UDBSBCustomSavedTactic : public UDualButtonScroll
{
	GENERATED_BODY()

	void OnPopulateElements() override
	{
		auto CreateDefaultButton = [&](const int32 i)
		{
			return SNew(SButton)
			.ButtonStyle(&ChildButtonStyle)
			[
				SNew(SBox)
				.HeightOverride(27)
				[
					SNew(SOverlay)
					+SOverlay::Slot()
					.VAlign(VAlign_Center)
					.Padding(10, 0, 40, 0)
					[
						SNew(STextBlock)
						.TextStyle(&TextBlockStyle)
						.Text(TextValues[i])
					]
					+SOverlay::Slot()
					.HAlign(HAlign_Right)
					.VAlign(VAlign_Center)
					.Padding(0, 0, 3, 0)
					[
						SNew(SButton)
						.ButtonStyle(&TrashButtonStyle)
						.OnClicked_Lambda([&, Index = i]
						{
							if(OnDBScrollBoxTrashClicked.IsBound())
							{
								OnDBScrollBoxTrashClicked.Broadcast(Index);	
							}
								
							return FReply::Handled();
						})
					]	
				]
			];
		};

		auto CreateSelectedButton = [&](const int32 i)
		{
			return SNew(SButton)
			.ButtonStyle(&ChildButtonSelectedStyle)
			[
				SNew(SBox)
				.HeightOverride(27)
				[
					SNew(SOverlay)
					+SOverlay::Slot()
					.VAlign(VAlign_Center)
					.Padding(10, 0, 40, 0)
					[
						SNew(STextBlock)
						.TextStyle(&TextBlockSelectedStyle)
						.Text(TextValues[i])
					]
					+SOverlay::Slot()
					.HAlign(HAlign_Right)
					.VAlign(VAlign_Center)
					.Padding(0, 0, 3, 0)
					[
						SNew(SButton)
						.ButtonStyle(&TrashButtonStyle)
						.OnClicked_Lambda([&, Index = i]
						{
							if(OnDBScrollBoxTrashClicked.IsBound())
							{
								OnDBScrollBoxTrashClicked.Broadcast(Index);	
							}
								
							return FReply::Handled();
						})
					]	
				]			
			];
		};
		
		if(MyDualButtonScroll.IsValid())
		{
			MyDualButtonScroll->ClearButtonChildren();
			for(int32 i = 0; i < TextValues.Num(); i++)
			{
				MyDualButtonScroll->AddChild([&]() -> IButtonBaseContainer::FButtonsPair
				{
					return
					{
						CreateDefaultButton(i),
						CreateSelectedButton(i)			
					};
				});
			}
		}	
	}

protected:
	/** */	
	UPROPERTY(EditAnywhere, Category="DualButtonScroll|Appaerance")
	FButtonStyle TrashButtonStyle;

	UPROPERTY(BlueprintAssignable)
	FDBScrollBoxTrashClicked OnDBScrollBoxTrashClicked;
};
