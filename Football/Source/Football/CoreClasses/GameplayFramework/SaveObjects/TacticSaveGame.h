// Copyright, 2023, by NGD Studios AB. All rights reserved.

#pragma once

#include <CoreMinimal.h>
#include <GameFramework/SaveGame.h>

#include "TacticSaveGame.generated.h"

/**
 * @see UTacticsUserWidget
 */
UCLASS()
class FOOTBALL_API UTacticSaveGame : public USaveGame
{
	GENERATED_BODY()

public:
	//@todo(jcastro) I'm not finished
	//UPROPERTY(SaveGame)
	//class UTacticPresetDataAsset* Preset {};

	UPROPERTY(SaveGame)
	FTacticPreset PresetData;
};
