// Copyright, 2023, by NGD Studios AB. All rights reserved.

#pragma once

#include <CoreMinimal.h>
#include <Blueprint/UserWidget.h>
#include <Football/Demo/Script/Scripter.h>

#include "MatchHudWidget.generated.h"

class UScoreAndTimer;
class USlowActions;
class UFootballersStateboard;
class UQuickActions;
class USquadScreen;
class UCoachesViewports;
class UStaticsAndHighlights;
class UCommentator;

class ULevelSequence;
class ALevelSequenceActor;

/**
 * This component acts as a coordinator for all widgets that constitute 
 * the main interface during a match game. Essentially serving as a bridge 
 * between systems and match-related widgets.
 *
 * The widgets include:
 *	1. Background Image
 *	2. Score and Timer
 *	3. Possession Bar
 *	4. Slow Actions
 *	5. Footballers Stateboard
 *	6. Quick Actions
 *	7. Squad Screen
 *	8. Coaches Viewports
 *	9. Statics and Highlights
 */
UCLASS()
class FOOTBALL_API UMatchHudWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	void NativeConstruct() override;
	void NativeDestruct() override;

public:
	//~=================================================================================================================
	// Getters
	//~=================================================================================================================
	
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, DisplayName=GetBackgroundImage)
	UOverlay* K2_GetBackgroundImage() const;

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, DisplayName=GetScoreAndTimer)
	UScoreAndTimer* K2_GetScoreAndTimer() const;

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, DisplayName=GetSlowActions)
	USlowActions* K2_GetSlowActions() const;

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, DisplayName=GetFootballersStateboard)
	UFootballersStateboard* K2_GetFootballersStateboard() const;

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, DisplayName=GetQuickActions)
	UQuickActions* K2_GetQuickActions() const;

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, DisplayName=GetSquadScreen)
	USquadScreen* K2_GetSquadScreen() const;

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, DisplayName=GetCoachesViewports)
	UCoachesViewports* K2_GetCoachesViewports() const;

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, DisplayName=GetStaticsAndHightlighs)
	UStaticsAndHighlights* K2_GetStaticsAndHightlighs() const;

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, DisplayName=GetCommentator)
	UCommentator* K2_GetCommentator() const;


private:
	//~=================================================================================================================
	// Script Steps events
	//~=================================================================================================================
	
	UFUNCTION()
	void OnScriptStep_Timer(uint8 Minute, uint8 Second, const TArray<FString>& Params);

	UFUNCTION()
	void OnScriptStep_ChangeView(uint8 Minute, uint8 Second, const TArray<FString>& Params);

	UFUNCTION()
	void OnScriptStep_Highlight(uint8 Minute, uint8 Second, const TArray<FString>& Params);

	UFUNCTION()
	void OnScriptStep_HeadCoachReaction(uint8 Minute, uint8 Second, const TArray<FString>& Params);

	UFUNCTION()
	void OnScriptStep_Dialog(uint8 Minute, uint8 Second, const TArray<FString>& Params);

	UFUNCTION()
	void OnScriptStep_PossessionBar(uint8 Minute, uint8 Second, const TArray<FString>& Params);

	UFUNCTION()
	void OnScriptStep_ScoreEntry(uint8 Minute, uint8 Second, const TArray<FString>& Params);	


protected:
	//~=================================================================================================================
	// Events
	//~=================================================================================================================
	
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, DisplayName=OnBackgroundChangedVisibility)
	void K2_OnBackgroundChangedVisibility(bool bVisible);

	
private:
	enum class EPlayHighlightsAction { Play, Pause, Stop };
	void PlayHighlights(EPlayHighlightsAction Action, ULevelSequence* LevelSequence);

	enum class EChangeView { HighlightView, DefaultView};
	void ChangeView(EChangeView View);
	
	UFUNCTION()
	void OnHighlightsLevelSequenceActorStop();
	


protected:
	UPROPERTY()
	FOnScriptStep ScripterPossessionBarDelegate;

protected:
	UPROPERTY(meta=(BindWidget))
	class UActionButton* SettingsButton {};
	
	UPROPERTY(meta=(BindWidget))
	class UPossessionBar* PossessionBar {};

	UPROPERTY(EditAnywhere)
	TArray<ULevelSequence*> Highlights;

	UPROPERTY(BlueprintReadWrite, meta=(ExposeOnSpawn, AllowPrivateAccess=true))
	AScripter* Scripter {};
	
private:
	UPROPERTY()
	ALevelSequenceActor* HighlightsLevelSequenceActor {};
};
