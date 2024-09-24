// Copyright, 2023, by NGD Studios AB. All rights reserved.

#pragma once

#include "CoreMinimal.h"

#include <Football/CoreClasses/DataStructures/Footballer.h>
#include <Football/CoreClasses/Interfaces/IUsableActor.h>

#include "GameFramework/Character.h"
#include "FootballerCharacter.generated.h"

class UDialogueAvatarComponent;

UCLASS()
class FOOTBALL_API AFootballerCharacter : public ACharacter, public IUsableActor
{
	GENERATED_BODY()

protected:
	AFootballerCharacter();

	//~ IUsableActor interface
	bool OnCanUse_Implementation(APlayerController*  PlayerController) const override;
	void OnUsed_Implementation(APlayerController*  PlayerController) override;
	void OnCursorEnter_Implementation(APlayerController* PlayerController) override;
	void OnCursorRelease_Implementation(APlayerController* PlayerController) override;

public:
	/**
	 * Update FFootballerEntity value of this AFootballerCharacter
	 **/
	void UpdateFootballerEntity(const FFootballerData& InFootballerEntity);
	
private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(AllowPrivateAccess=true))
	UDialogueAvatarComponent* DialogueAvatarComponent {};

private:
	FFootballerData FootballerEntity;
};
