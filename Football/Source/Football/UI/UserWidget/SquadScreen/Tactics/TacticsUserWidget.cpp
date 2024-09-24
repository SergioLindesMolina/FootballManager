// Copyright, 2023, by NGD Studios AB. All rights reserved.

#include "TacticsUserWidget.h"

#include <PlatformFeatures.h>
#include <SaveGameSystem.h>
#include <Kismet/GameplayStatics.h>
#include "Football/CoreClasses/FootballGameInstance.h"
//#include <AssetRegistry/AssetRegistryModule.h>

#include <Components/VerticalBox.h>
#include <Components/VerticalBoxSlot.h>

#include <UWidget/DropdownButton.h>
#include <UWidget/DualButtonScroll.h>

#include <Football/CoreClasses/GameplayFramework/SaveObjects/TacticSaveGame.h>
#include <Football/CoreClasses/DataStructures/Tactics.h>
#include <Common/Logging.h>


void UTacticsUserWidget::InitializeTacticsGroup(const ETacticCategory Category, const TArray<UTacticGroupDataAsset*>& Tactics)
{
	UE_CLOG(!TacticGroupContainer[static_cast<uint32>(Category)].IsEmpty(),
		LogFootball, Warning, TEXT("Attempting to add elements to TacticGroupContainer that is already filled"));

	UE_CLOG(Tactics.IsEmpty(),
		LogFootball, Error, TEXT("InitializeTacticsGroup called with empty Tactics"));

	for(int32 i = 0; i < Tactics.Num(); i++)
	{
		TacticGroupContainer[static_cast<uint32>(Category)].Add(TStrongObjectPtr(Tactics[i]));
	}
}

void UTacticsUserWidget::InitializeTacticsPresets(const TArray<UTacticPresetDataAsset*>& TacticPresets, const TArray<UTacticPresetDataAsset*>& DefaultTacticPresets, UDualButtonScroll* Container, UTacticPresetDataAsset* InCurrentPreset)
{
	UE_CLOG(!Container->IsEmpty(),
	LogFootball, Warning, TEXT("Attempting to add elements to TacticPresets that is already filled"));

	if(TacticPresets.IsEmpty())
	{
		UE_LOG(LogFootball, Error, TEXT("InitializeTacticsPresets called with empty TacticPresets"));
		return;
	}

	check(!DefaultTacticPresets.IsEmpty());
	
	DefaultPresets = DefaultTacticPresets;
	Presets        = TacticPresets;
	//Temp fix to maintain data without modifying the main data assets
	CurrentPreset  = InCurrentPreset;

	if (CurrentPreset->GetTacticPreset().OverrideValues.IsEmpty())
	{
		CurrentPreset->GetTacticPreset() = Presets.Last()->GetTacticPreset();
	}
	
	TArray<FText> ValuesNames;
	ValuesNames.Reserve(Presets.Num());
	for(const UTacticPresetDataAsset* Preset : Presets)
	{
		check(Preset);
		ValuesNames.Add(Preset->GetTacticPreset().DisplayName);
	}

	Container->ClearChildren();
	Container->PopulateElements(ValuesNames);

	// Bind event to Presets list. When a preset is selected, we update our current preset and re-draw the new state
	Container->OnDBScrollBoxSelChanged.AddDynamic(this, &UTacticsUserWidget::OnTacticsPresetContainerSelChanged);

	Container->OnDBScrollBoxHovered.AddDynamic(this, &UTacticsUserWidget::OnTacticsPresetContainerHovered);

	OnCurrentPresetUpdate();
}

void UTacticsUserWidget::SwitchTacticGroup(const ETacticCategory InCategory, UVerticalBox* PanelWidget)
{
	check(PanelWidget);

	PanelWidget->ClearChildren();

	DropdownButtons.Empty();
	DropdownButtons.Reserve(TacticGroupContainer[static_cast<uint32>(InCategory)].Num());
	
	for(const TStrongObjectPtr<UTacticGroupDataAsset>& Tactic : TacticGroupContainer[static_cast<uint32>(InCategory)])
	{
		const auto [DisplayName, Description, Values, Key, SelectedIndex] = Tactic.Get()->GetTacticGroup();
		
		UDropdownButton* TacticGroupButton = NewObject<UDropdownButton>(this, UDropdownButton::StaticClass());

		UVerticalBoxSlot* VerticalBoxSlot = CastChecked<UVerticalBoxSlot>(PanelWidget->AddChild(TacticGroupButton));
		VerticalBoxSlot->SetPadding(FMargin(0,0,0, 4));

		DropdownButtons.Add(TacticGroupButton, Tactic.Get()->GetTacticGroup());
		
		// Bind events
		{
			TacticGroupButton->OnDropdownButtonSelChanged.AddDynamic(this, &UTacticsUserWidget::OnTacticGroupButtonSelChanged);
			TacticGroupButton->OnDropdownButtonHovered.AddDynamic(this, &UTacticsUserWidget::OnTacticGroupButtonHovered);
			TacticGroupButton->OnDropdownButtonCollChanged.AddDynamic(this, &UTacticsUserWidget::OnTacticGroupButtonCollChanged);	
		}
		
		// Setup DropdownButton's style
		{
			TacticGroupButton->SetTextBlockStyle(TextBlockStyle);
			TacticGroupButton->SetScrollBoxStyle(ScrollBoxStyle);
			TacticGroupButton->SetScrollBarStyle(ScrollBarStyle);
			TacticGroupButton->SetChildButtonStyle(ChildButtonStyle);	
			TacticGroupButton->SetChildButtonSelectedStyle(ChildButtonSelectedStyle);
			TacticGroupButton->SetChildTextBlockStyle(ChildTextBlockStyle);
			TacticGroupButton->SetChildTextBlockSelectedStyle(ChildTextBlockSelectedStyle);
		}
		
		// Setup DropdownButton values
		{
			switch (InCategory)
			{
				case ETacticCategory::General   : TacticGroupButton->SetFlagColor(CategoryGeneralColor);   break;
				case ETacticCategory::Defensive : TacticGroupButton->SetFlagColor(CategoryDefensiveColor); break;
				case ETacticCategory::Offensive : TacticGroupButton->SetFlagColor(CategoryOffensiveColor); break;
			}
			
			TacticGroupButton->SetText(DisplayName);
			TacticGroupButton->SetContentCollapsed(true);

			TArray<FText> ValuesNames;
			ValuesNames.Reserve(Values.Num());
			for(const FTacticValue& Value : Values)
			{
				ValuesNames.Add(Value.DisplayName);
			}
			TacticGroupButton->PopulateButtonLabelList(ValuesNames);	
		}
	}

	OnCurrentPresetUpdate();
}

void UTacticsUserWidget::LoadDefaultTacticPreset(const int32 Index)
{
	CurrentPreset->GetTacticPreset() = DefaultPresets[Index]->GetTacticPreset();

	// Collapse any Tactic Group Button expanded
	for (const auto& [UMGDropdownButton, _] : DropdownButtons)
	{
		UMGDropdownButton->SetContentCollapsed(true);
	}

	ChangeDirtyState(false);
	OnCurrentPresetUpdate();
}

void UTacticsUserWidget::LoadTacticPreset(const int32 Index)
{
	CurrentPreset->GetTacticPreset() = Presets[Index]->GetTacticPreset();

	// Collapse any Tactic Group Button expanded
	for(const auto& [UMGDropdownButton, _] : DropdownButtons)
	{
		UMGDropdownButton->SetContentCollapsed(true);
	}
	
	ChangeDirtyState(false);
	OnCurrentPresetUpdate();	
}

bool UTacticsUserWidget::SaveCurrentCustomTacticPreset(const FString& Name) const
{
	if(UGameplayStatics::DoesSaveGameExist(*Name, 0))
	{
		UE_LOG(LogFootball, Error, TEXT("Save slot '%s' already exists. Don't override"), *Name);
		return false;
	}

	UTacticSaveGame* FootballSaveGame = Cast<UTacticSaveGame>(UGameplayStatics::CreateSaveGameObject(UTacticSaveGame::StaticClass()));
	FootballSaveGame->PresetData = CurrentPreset->GetTacticPreset();
	FootballSaveGame->PresetData.DisplayName = FText::FromString(Name);
	
	return UGameplayStatics::SaveGameToSlot(FootballSaveGame, *Name, 0);
}

bool UTacticsUserWidget::LoadCustomTacticPreset(const FString& Name)
{
	if(!UGameplayStatics::DoesSaveGameExist(*Name, 0))
	{
		UE_LOG(LogFootball, Error, TEXT("Save slot '%s' doesn't exists. Don't override"), *Name);
		return false;
	}

	const UTacticSaveGame* FootballSaveGame = Cast<UTacticSaveGame>(UGameplayStatics::LoadGameFromSlot(*Name, 0));
	CurrentPreset->GetTacticPreset() = FootballSaveGame->PresetData;

	OnCurrentPresetUpdate();
	
	return FootballSaveGame != nullptr;
}

bool UTacticsUserWidget::DeleteCustomTacticPreset(const FString& Name)
{
	if(!UGameplayStatics::DoesSaveGameExist(*Name, 0))
	{
		UE_LOG(LogFootball, Error, TEXT("Save slot '%s' doesn't exists. Can't delete"), *Name);
		return false;
	}
	
	return UGameplayStatics::DeleteGameInSlot(*Name, 0);
}

void UTacticsUserWidget::PopulateCustomTacticPresets(UDualButtonScroll* Container)
{
	ISaveGameSystem* SaveSystem = IPlatformFeaturesModule::Get().GetSaveGameSystem();
	check(SaveSystem);

	TArray<FString> FoundSaved;
	SaveSystem->GetSaveGameNames(FoundSaved, 0);

	TArray<FText> FoundSavedText;
	FoundSavedText.Reserve(FoundSaved.Num());
	for (const FString& Saved : FoundSaved)
	{
		FoundSavedText.Add(FText::FromString(Saved));
	}

	Container->ClearChildren();
	Container->PopulateElements(FoundSavedText);
}

void UTacticsUserWidget::OnTacticGroupButtonSelChanged(const int32 Index, UDropdownButton* DropdownButton)
{
	check(DropdownButtons.Contains(DropdownButton));
	check(CurrentPreset);

	const FTacticGroup& TacticGroup = DropdownButtons[DropdownButton];

	for(auto It = CurrentPreset->GetTacticPreset().OverrideValues.CreateIterator(); It; ++It)
	{
		if(TacticGroup == It->Key->GetTacticGroup())
		{
			It->Value = Index;
			
			UFootballGameInstance* FootballGameInstance = Cast<UFootballGameInstance>(GetGameInstance());
			
			if (FootballGameInstance)
			{
				FootballGameInstance->UpdatePlayerTactics(TacticGroup.Key, Index);
			}

			ChangeDirtyState(true);

			// Each time we select a tactic from TacticGroup Button, we collapse it
			DropdownButton->SetContentCollapsed(true);
			
			OnCurrentPresetUpdate();
			return;
		}
	}
}

void UTacticsUserWidget::OnTacticGroupButtonHovered(const int32 Index, UDropdownButton* DropdownButton)
{
	check(DropdownButtons.Contains(DropdownButton));
					
	const FTacticGroup& TacticGroup = DropdownButtons[DropdownButton];

	K2_OnUpdateDescriptionThumbnail(TacticGroup.Values[Index].Thumbnail);
	K2_OnUpdateDescriptionText(FText::Format(INVTEXT("<Emphasis>{0}</>\n\n{1}\n\n<Emphasis>{2}</>\n\n{3}")
		, TacticGroup.DisplayName
		, TacticGroup.Description
		, TacticGroup.Values[Index].DisplayName
		, TacticGroup.Values[Index].Description
	));
}

void UTacticsUserWidget::OnTacticGroupButtonCollChanged(const bool bIsCollapsed, UDropdownButton* DropdownButton)
{
	// When one DropdownButton is expanded, all other DropdownButtons are automatically collapsed to ensure a clean
	// and organized UI.
		
	if(bIsCollapsed) return;
	for(const auto& [UMGDropdownButton, _] : DropdownButtons)
	{
		if(UMGDropdownButton == DropdownButton)
		{
			continue;
		}

		UMGDropdownButton->SetContentCollapsed(true);
	}		
}

void UTacticsUserWidget::OnTacticsPresetContainerSelChanged(const int32 Index, UDualButtonScroll* /*DualButtonScroll*/)
{
	#if 0
	if(bDirty)
	{
		K2_OnDisplayLossDataWarning(Index);
	}
	else
	{
		LoadTacticPreset(Index);
	}
	#endif

	// @todo(jcastro)
	// Always notify as if we are always dirty.
	// Temporal solution requested by UX.
	K2_OnDisplayLossDataWarning(Index);
}

void UTacticsUserWidget::OnTacticsPresetContainerHovered(const int32 Index, UDualButtonScroll* /*DualButtonScroll*/)
{
	const FTacticPreset& TacticPreset = Presets[Index]->GetTacticPreset();

	K2_OnUpdatePresetPreviewThumbnail(TacticPreset.Thumbnail);
	K2_OnUpdatePresetPreviewText(FText::Format(INVTEXT("<Emphasis>{0}</>\n\n{1}")
		, TacticPreset.DisplayName
		, TacticPreset.Description
	));
}

void UTacticsUserWidget::OnCurrentPresetUpdate()
{
	if(!CurrentPreset)
	{
		UE_LOG(LogFootball, Error, TEXT("CurrentPreset uninitialized"));
		return;		
	}
		
	for(const auto& [DataAsset, OverrideIndex] : CurrentPreset->GetTacticPreset().OverrideValues)
	{
		for(const auto& [UMGDropdownButton, TacticGroup] : DropdownButtons)
		{
			if(TacticGroup == DataAsset->GetTacticGroup())
			{
				UMGDropdownButton->SetSelectedText(UMGDropdownButton->GetButtonLabelList()[OverrideIndex]);
				UMGDropdownButton->HighlightChild(OverrideIndex);
				break; // go to the next tactic
			}
		}
	}
}

void UTacticsUserWidget::ChangeDirtyState(const bool bIsDirty)
{
	bDirty = bIsDirty;
	K2_OnDirtyStateChanged(bIsDirty);
}
