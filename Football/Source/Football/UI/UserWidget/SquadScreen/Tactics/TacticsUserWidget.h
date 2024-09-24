// Copyright, 2023, by NGD Studios AB. All rights reserved.

#pragma once

#include <CoreMinimal.h>
#include <Blueprint/UserWidget.h>
#include <Football/CoreClasses/DataStructures/Tactics.h>

#include "TacticsUserWidget.generated.h"

struct FTacticGroup;
class UScrollBox;
class UVerticalBox;
class UDropdownButton;
class UTacticGroupDataAsset;
class UDualButtonScroll;
enum class ETacticCategory : uint8;


/**
 * Represents different categories of a tactic.
 */
UENUM(BlueprintType)
enum class ETacticCategory : uint8
{
	General,   				// A General category tactic.
	Defensive, 				// Tactics for defensive plays.
	Offensive, 				// Tactics for offensive plays.

	MAX_COUNT UMETA(Hidden) // Used for internal purposes.
};

/**
 * @see https://nimblegiant.atlassian.net/browse/FTB1-873
 */
UCLASS()
class FOOTBALL_API UTacticsUserWidget : public UUserWidget
{
	GENERATED_BODY()

	typedef TStaticArray<TArray<TStrongObjectPtr<UTacticGroupDataAsset>>, static_cast<uint32>(ETacticCategory::MAX_COUNT)>
	FTacticGroupContainer;

protected:
	//~=================================================================================================================
	// Events
	//~=================================================================================================================

	/**
	 * This is invoked to show a warning message to the client. The warning notifies that the continuation might lead to
	 * the loss of data associated with CurrentPreset.
	 * 
	 * @param IndexRequested The index of the preset requested to manage the override if the client opts to "LOAD"
	 * despite the warning.
	 */
	UFUNCTION(BlueprintImplementableEvent, DisplayName=OnDisplayLossDataWarning)
	void K2_OnDisplayLossDataWarning(int32 IndexRequested);

	UFUNCTION(BlueprintImplementableEvent, DisplayName=OnUpdateDescriptionText)
	void K2_OnUpdateDescriptionText(const FText& Description);

	UFUNCTION(BlueprintImplementableEvent, DisplayName=OnUpdateDescriptionThumbnail)
	void K2_OnUpdateDescriptionThumbnail(const UTexture2D* Thumbnail);

	UFUNCTION(BlueprintImplementableEvent, DisplayName=OnUpdatePresetPreviewText)
	void K2_OnUpdatePresetPreviewText(const FText& Description);

	UFUNCTION(BlueprintImplementableEvent, DisplayName=OnUpdatePresetPreviewThumbnail)
	void K2_OnUpdatePresetPreviewThumbnail(const UTexture2D* Thumbnail);
	
	UFUNCTION(BlueprintImplementableEvent, DisplayName=OnDirtyStateChanged)
	void K2_OnDirtyStateChanged(bool bIsDirty);



protected:
	//~=================================================================================================================
	// Assistant
	//~=================================================================================================================
	//@todo(jcastro) Copied from UQuickActions. Generalize 
	
	/**
	 * Display a message directly. It's UMG dependent the way of do this.
	 * @param Message The message to display
	 * @param Timeout If greater than zero, how much seconds the message remains until hidden itself
	 */
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, DisplayName=DisplayAssistantMessage)
	void K2_DisplayAssistantMessage(const FText& Message, float Timeout);

	/**
	 * Hide a previous message. It's UMG dependent the way of do this.
	 */	
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, DisplayName=HideAssistantMessage)
	void K2_HideAssistantMessage();

	/**
	 * Display a notify in assistant area. It's UMG dependent the way of do this.
	 * @param bVisible True to display, false to hide
	 */
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, DisplayName=DisplayAssistantNotify)
	void K2_DisplayAssistantNotify(bool bVisible);

	/**
	 * Push a message in the stack of assistant messages. This means that the message don't display
	 * directly like K2_DisplayAssistantMessage, instead awaits until next call K2_DisplayAssistantMessage.
	 * @param Message The message to display
	 */
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, DisplayName=PushAssistantMessage)
	void K2_PushAssistantMessage(const FText& Message);

	
protected:
	//~=================================================================================================================
	// Set up tactics
	//~=================================================================================================================

	/** Cache all tactics groups based on <ECategory,Group> key-value container */
	UFUNCTION(BlueprintCallable)
	void InitializeTacticsGroup(ETacticCategory Category, const TArray<UTacticGroupDataAsset*>& Tactics);

	/** Cache all tactics presets  */
	UFUNCTION(BlueprintCallable)
	void InitializeTacticsPresets(const TArray<UTacticPresetDataAsset*>& TacticPresets, const TArray<UTacticPresetDataAsset*>& DefaultTacticPresets, UDualButtonScroll* Container, UTacticPresetDataAsset* InCurrentPreset);
	
	/** Update PanelWidget with UDropdownButton associated to InCategory */
	UFUNCTION(BlueprintCallable)
	void SwitchTacticGroup(const ETacticCategory InCategory, UVerticalBox* PanelWidget);
	
protected:
	//~=================================================================================================================
	// Tactic Presets
	//~=================================================================================================================

	/** Loads a tactic preset based on the given index */
	UFUNCTION(BlueprintCallable)
	void LoadDefaultTacticPreset(const int32 Index);

	/** Loads a tactic preset based on the given index */
	UFUNCTION(BlueprintCallable)
	void LoadTacticPreset(const int32 Index);

	/** Saves the current tactic preset as a user-defined tactic preset with the given name */
	UFUNCTION(BlueprintCallable, BlueprintPure=false)
	bool SaveCurrentCustomTacticPreset(const FString& Name) const;

	/** Loads a user-defined tactic preset based on the given index */
	UFUNCTION(BlueprintCallable)
	bool LoadCustomTacticPreset(const FString& Name);

	UFUNCTION(BlueprintCallable)
	static bool DeleteCustomTacticPreset(const FString& Name);
	
	/** Populates the panel widget with buttons corresponding to each saved user-defined tactic */
	UFUNCTION(BlueprintCallable)
	static void PopulateCustomTacticPresets(UDualButtonScroll* Container);

private:
	//~=================================================================================================================
	// TacticGroup buttons events
	//~=================================================================================================================
	
	UFUNCTION()
	void OnTacticGroupButtonSelChanged(int32 Index, UDropdownButton* DropdownButton);
	
	UFUNCTION()
	void OnTacticGroupButtonHovered(int32 Index, UDropdownButton* DropdownButton);
	
	UFUNCTION()
	void OnTacticGroupButtonCollChanged(bool bIsCollapsed, UDropdownButton* DropdownButton);

	UFUNCTION()
	void OnTacticsPresetContainerSelChanged(int32 Index, UDualButtonScroll* DualButtonScroll);

	UFUNCTION()
	void OnTacticsPresetContainerHovered(int32 Index, UDualButtonScroll* DualButtonScroll);	
	
private:
	//~=================================================================================================================
	// Presets State Management
	//~=================================================================================================================
	
	void OnCurrentPresetUpdate();
	void ChangeDirtyState(bool bIsDirty);

	
private:
	UPROPERTY(EditAnywhere, Category="TacticGroup|Appaerance")
	FTextBlockStyle TextBlockStyle = FCoreStyle::Get().GetWidgetStyle<FTextBlockStyle>("NormalText");

	UPROPERTY(EditAnywhere, Category="TacticGroup|Appaerance")
	FScrollBoxStyle ScrollBoxStyle = FCoreStyle::Get().GetWidgetStyle<FScrollBoxStyle>("ScrollBox");
	
	UPROPERTY(EditAnywhere, Category="TacticGroup|Appaerance")
	FScrollBarStyle ScrollBarStyle = FCoreStyle::Get().GetWidgetStyle<FScrollBarStyle>("ScrollBar");

	UPROPERTY(EditAnywhere, Category="TacticGroup|Appaerance")
	FButtonStyle ChildButtonStyle;

	UPROPERTY(EditAnywhere, Category="TacticGroup|Appaerance")
	FButtonStyle ChildButtonSelectedStyle;

	UPROPERTY(EditAnywhere, Category="TacticGroup|Appaerance")
	FTextBlockStyle ChildTextBlockStyle = FCoreStyle::Get().GetWidgetStyle<FTextBlockStyle>("NormalText");

	UPROPERTY(EditAnywhere, Category="TacticGroup|Appaerance")
	FTextBlockStyle ChildTextBlockSelectedStyle = FCoreStyle::Get().GetWidgetStyle<FTextBlockStyle>("NormalText");
	
	UPROPERTY(EditAnywhere, Category="TacticGroup|Appaerance")
	FLinearColor CategoryGeneralColor = FColor::FromHex("FDFAC1FF");
	
	UPROPERTY(EditAnywhere, Category="TacticGroup|Appaerance")
	FLinearColor CategoryDefensiveColor = FColor::FromHex("00A89EFF");
	
	UPROPERTY(EditAnywhere, Category="TacticGroup|Appaerance")
	FLinearColor CategoryOffensiveColor = FColor::FromHex("FE016BFF");

private:
	/** Cache all tactics groups based on <ECategory,Group> key-value container */
	FTacticGroupContainer TacticGroupContainer;

	/** Cache all tactics presets  */
	UPROPERTY()
	TArray<UTacticPresetDataAsset*> Presets;

	/** Cache the default tactics presets  */
	UPROPERTY()
	TArray<UTacticPresetDataAsset*> DefaultPresets;

	/** Hold the current preset used */
	UPROPERTY()
	UTacticPresetDataAsset* CurrentPreset {};

	UPROPERTY()
	TMap<UDropdownButton*, FTacticGroup> DropdownButtons;

	/** When CurrentPreset is modified from user inputs, we'll turn dirty, that means we are in a un-saved state */
	bool bDirty = false;
};
