// Copyright, 2023, by NGD Studios AB. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MainMenuGameMode.generated.h"

UCLASS()
class FOOTBALL_API AMainMenuGameMode : public AGameModeBase
{
	GENERATED_BODY()

protected:
	AMainMenuGameMode();

public:
	UFUNCTION(BlueprintCallable)
	void PlayBackgroundMusic(USoundBase* Music);

private:
	UFUNCTION()
	void OnBackgroundMusicFade(USoundBase* Music);
	
private:
	UPROPERTY(Transient)
	USoundBase* CurrentBackgroundMusic {};
	
	UPROPERTY(Transient)
	UAudioComponent* BackgroundMusicAudioComponent {};

	FTimerHandle BackgroundMusicFadeTimerHandle;
};
