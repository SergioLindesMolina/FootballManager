// Copyright, 2023, by NGD Studios AB. All rights reserved.


#include "MatchHudWidget.h"

#include <LevelSequence.h>
#include <LevelSequenceActor.h>
#include <LevelSequencePlayer.h>

#include <UWidget/PossessionBar.h>
#include <Common/Logging.h>

#include <Football/UI/UserWidget/MatchHud/CoachesViewports/CoachesViewports.h>
#include <Football/UI/UserWidget/MatchHud/Commentator/Commentator.h>
#include <Football/UI/UserWidget/MatchHud/FootballersStateboard/FootballersStateboard.h>
#include <Football/UI/UserWidget/MatchHud/QuickActions/QuickActions.h>
#include <Football/UI/UserWidget/MatchHud/ScoreAndTimer/ScoreAndTimer.h>
#include <Football/UI/UserWidget/MatchHud/SlowActions/SlowActions.h>
#include <Football/UI/UserWidget/MatchHud/StaticsAndHightlighs/StaticsAndHighlights.h>


void UMatchHudWidget::NativeConstruct()
{
	Super::NativeConstruct();

	//
	// Setup LevelSequencePlayer
	(void)ULevelSequencePlayer::CreateLevelSequencePlayer(GetWorld(), Highlights.Last(), FMovieSceneSequencePlaybackSettings(), HighlightsLevelSequenceActor);
	HighlightsLevelSequenceActor->GetSequencePlayer()->OnFinished.AddDynamic(this, &UMatchHudWidget::OnHighlightsLevelSequenceActorStop);

	//
	// Setup OnScriptStep
	{
		FOnScriptStep OnScriptStep_Timer;
		OnScriptStep_Timer.BindUFunction(this, "OnScriptStep_Timer");
		Scripter->RegisterForEventType("Timer", OnScriptStep_Timer);

		FOnScriptStep OnScriptStep_ChangeView;
		OnScriptStep_ChangeView.BindUFunction(this, "OnScriptStep_ChangeView");
		Scripter->RegisterForEventType("ChangeView", OnScriptStep_ChangeView);

		FOnScriptStep OnScriptStep_Highlight;
		OnScriptStep_Highlight.BindUFunction(this, "OnScriptStep_Highlight");
		Scripter->RegisterForEventType("Highlight", OnScriptStep_Highlight);

		FOnScriptStep OnScriptStep_HeadCoachReaction;
		OnScriptStep_HeadCoachReaction.BindUFunction(this, "OnScriptStep_HeadCoachReaction");
		Scripter->RegisterForEventType("HeadCoachReaction", OnScriptStep_HeadCoachReaction);

		FOnScriptStep OnScriptStep_Dialog;
		OnScriptStep_Dialog.BindUFunction(this, "OnScriptStep_Dialog");
		Scripter->RegisterForEventType("Dialog", OnScriptStep_Dialog);

		FOnScriptStep OnScriptStep_PossessionBar;
		OnScriptStep_PossessionBar.BindUFunction(this, "OnScriptStep_PossessionBar");
		Scripter->RegisterForEventType("PossessionBar", OnScriptStep_PossessionBar);

		FOnScriptStep OnScriptStep_ScoreEntry;
		OnScriptStep_ScoreEntry.BindUFunction(this, "OnScriptStep_ScoreEntry");
		Scripter->RegisterForEventType("ScoreEntry", OnScriptStep_ScoreEntry);		
	}
}

void UMatchHudWidget::NativeDestruct()
{
	Super::NativeDestruct();

	Scripter->DeregisterForEventType("PossessionBar", ScripterPossessionBarDelegate);
}


void UMatchHudWidget::OnScriptStep_Timer(const uint8 Minute, const uint8 Second, const TArray<FString>& /*Params*/)
{
	PossessionBar->AddRandomPercentage(Minute, Second);
	K2_GetScoreAndTimer()->UpdateTime(Minute, Second);
}

void UMatchHudWidget::OnScriptStep_ChangeView(uint8 /*Minute*/, uint8 /*Second*/, const TArray<FString>& Params)
{
	enum EParameters
	{
		TypeOfView, SequenceAction, Index
	};

	if(Params[TypeOfView] == "HighlightView")
	{
		EPlayHighlightsAction PlayHighlightsAction = {};
		if(Params[SequenceAction] == "Play")
		{
			PlayHighlightsAction = EPlayHighlightsAction::Play;
		}
		else if(Params[SequenceAction] == "Pause")
		{
			PlayHighlightsAction = EPlayHighlightsAction::Pause;
		}
		else if(Params[SequenceAction] == "Stop")
		{
			PlayHighlightsAction = EPlayHighlightsAction::Stop;
		}

		checkf(Params[Index].IsNumeric(), TEXT("Params[Index] isn't a number. Value = %s"), *Params[Index]);
		PlayHighlights(PlayHighlightsAction, Highlights[FCString::Atoi(*Params[Index])]);
	}
	else if(Params[TypeOfView] == "DefaultView")
	{
		ChangeView(EChangeView::DefaultView);
	}
	else
	{
		UE_LOG(LogFootball, Error, TEXT("OnScriptStep_ChangeView with unexpected ETypeOfView"));
	}

}

void UMatchHudWidget::OnScriptStep_Highlight(uint8 /*Minute*/, uint8 /*Second*/, const TArray<FString>& Params)
{
	enum EParameters
	{
		Time, LocalHighlight, RivalHighlight
	};
	
	K2_GetStaticsAndHightlighs()->K2_AddHighlight(Params[Time], Params[LocalHighlight], Params[RivalHighlight]);
}

void UMatchHudWidget::OnScriptStep_HeadCoachReaction(uint8 /*Minute*/, uint8 /*Second*/, const TArray<FString>& Params)
{
	enum EParameters
	{
		Coach, Visibility, AnimationIndex
	};
	checkf(Params[AnimationIndex].IsNumeric(), TEXT("Params[AnimationIndex] isn't a number. Value = %s"), *Params[AnimationIndex]);

	bool bIsLocal   = Params[Coach] == "Local";
	bool bIsVisible = Params[Visibility] == "show";
	
	if(bIsLocal)
	{
		K2_GetCoachesViewports()->K2_SetLocalViewportVisibility(bIsVisible);
		K2_GetCoachesViewports()->K2_PlayLocalHeadCoachReactions(FCString::Atoi(*Params[AnimationIndex]));
	}
	else
	{
		K2_GetCoachesViewports()->K2_SetRivalViewportVisibility(bIsVisible);
		K2_GetCoachesViewports()->K2_PlayRivalHeadCoachReactions(FCString::Atoi(*Params[AnimationIndex]));
	}
}

void UMatchHudWidget::OnScriptStep_Dialog(uint8 /*Minute*/, uint8 /*Second*/, const TArray<FString>& Params)
{
	enum EParameters
	{
		Speaker, Time, Message
	};
	checkf(Params[Time].IsNumeric(), TEXT("Params[Time] isn't a number. Value = %s"), *Params[Time]);

	// Commentator message
	if(Params[Speaker] == "Commentator")
	{
		K2_GetCommentator()->DisplayMessage(FText::FromString(Params[Message]), FCString::Atof(*Params[Time]));
	}
	// Assistant message
	else if(Params[Speaker] == "ASSISTANT COACH")
	{
		K2_GetQuickActions()->K2_DisplayAssistantMessage(FText::FromString(Params[Message]), FCString::Atof(*Params[Time]));
	}
	else
	{
		UE_LOG(LogFootball, Error, TEXT("UMatchHudWidget::OnScriptStep_Dialog with unexpected Speaker"));
	}
	
	
}

void UMatchHudWidget::OnScriptStep_PossessionBar(uint8 Minute, uint8 Second, const TArray<FString>& Params)
{
	if (!Params[0].IsNumeric())
	{
		return;
	}
	
	float Value = FCString::Atof(*Params[0]);
	PossessionBar->SetPercentage(Value);
}

void UMatchHudWidget::OnScriptStep_ScoreEntry(const uint8 Minute, uint8 /*Second*/, const TArray<FString>& Params)
{
	const bool IsLocal         = (Params[1] == "Local");
	const FText FootballerName = FText::FromString(Params[2]);
	K2_GetScoreAndTimer()->K2_AddScoreEntry(IsLocal, FootballerName, Minute);
}

void UMatchHudWidget::PlayHighlights(const EPlayHighlightsAction Action, ULevelSequence* LevelSequence)
{
	ChangeView(EChangeView::HighlightView);

	
	switch (Action)
	{
		case EPlayHighlightsAction::Play:
			if(HighlightsLevelSequenceActor->GetSequencePlayer()->IsPlaying())
			{
				UE_LOG(LogFootball, Warning, TEXT("UMatchHudWidget::PlayHighlights try to play hightligh while one is still playing"));
				HighlightsLevelSequenceActor->GetSequencePlayer()->Stop();
			}

			HighlightsLevelSequenceActor->LevelSequenceAsset = LevelSequence;
			HighlightsLevelSequenceActor->InitializePlayer();
			HighlightsLevelSequenceActor->GetSequencePlayer()->Play();
			break;
			
		case EPlayHighlightsAction::Pause:
			HighlightsLevelSequenceActor->GetSequencePlayer()->Pause();
			break;
			
		case EPlayHighlightsAction::Stop:
			HighlightsLevelSequenceActor->GetSequencePlayer()->Stop();
			break;
	}
}

void UMatchHudWidget::ChangeView(const EChangeView View)
{
	TStaticArray<UUserWidget*, 3> UserWidgets;
	UserWidgets[0] = K2_GetScoreAndTimer(); 
	UserWidgets[1] = K2_GetFootballersStateboard(); 
	UserWidgets[2] = K2_GetSlowActions(); 
	
	switch (View)
	{
		case EChangeView::HighlightView:
			K2_OnBackgroundChangedVisibility(false);
			for(UUserWidget* UserWidget : UserWidgets)
			{
				UserWidget->SetVisibility(ESlateVisibility::Collapsed);
			}
		
			Scripter->Stop();
			break;
		
		case EChangeView::DefaultView:
			K2_OnBackgroundChangedVisibility(true);
			for(UUserWidget* UserWidget : UserWidgets)
			{
				UserWidget->SetVisibility(ESlateVisibility::Visible);
			}
		
			Scripter->Resume();
			break;

		default:
			UE_LOG(LogFootball, Error, TEXT("UMatchHudWidget::ChangeView with unexpected EChangeView"));
			break;
	}
}

void UMatchHudWidget::OnHighlightsLevelSequenceActorStop()
{
	ChangeView(EChangeView::DefaultView);
}
