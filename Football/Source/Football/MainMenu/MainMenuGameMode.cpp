// Copyright, 2023, by NGD Studios AB. All rights reserved.

#include "MainMenuGameMode.h"

#include <Components/AudioComponent.h>
#include <Football/CoreClasses/GameplayFramework/FootballPlayerController.h>


AMainMenuGameMode::AMainMenuGameMode()
{
	DefaultPawnClass      = TSubclassOf<APawn>();
	PlayerControllerClass = AFootballPlayerController::StaticClass();
}

void AMainMenuGameMode::PlayBackgroundMusic(USoundBase* Music)
{
	if(BackgroundMusicAudioComponent == nullptr)
	{
		AActor* BackgroundMusicAudioActor = GetWorld()->SpawnActor(AActor::StaticClass());
		BackgroundMusicAudioComponent = Cast<UAudioComponent>(BackgroundMusicAudioActor->AddComponentByClass(UAudioComponent::StaticClass(), true, FTransform{}, true));
		BackgroundMusicAudioComponent->SetUISound(true);
		BackgroundMusicAudioComponent->bSuppressSubtitles = true;	
	}
	
	if(BackgroundMusicAudioComponent->IsPlaying())
	{
		BackgroundMusicAudioComponent->FadeOut(1.f, 0.f);
	
		FTimerDelegate TimerDelegate;
		TimerDelegate.BindUObject(this, &AMainMenuGameMode::OnBackgroundMusicFade, Music);
		GetWorld()->GetTimerManager().SetTimer(BackgroundMusicFadeTimerHandle, TimerDelegate, 1.f, false);
		return;
	}
	
	OnBackgroundMusicFade(Music);
}

void AMainMenuGameMode::OnBackgroundMusicFade(USoundBase* Music)
{
	check(BackgroundMusicAudioComponent);
	
	BackgroundMusicAudioComponent->SetSound(Music);
	BackgroundMusicAudioComponent->Play();
	BackgroundMusicAudioComponent->FadeIn(1.f, 1.f);

	GetWorld()->GetTimerManager().ClearTimer(BackgroundMusicFadeTimerHandle);
}
