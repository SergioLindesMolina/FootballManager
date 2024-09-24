// Copyright, 2023, by NGD Studios AB. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "LevelSequenceActor.h"

#include "DemoGameState.generated.h"

class UManagerRenderTargetWidget;
class ARenderTargetScenario;
/**
 * 
 */

constexpr uint8 MAX_RENDERTARGET_NUM = 2;

UCLASS()
class FOOTBALL_API ADemoGameState : public AGameStateBase
{
	GENERATED_BODY()
	
protected:
	virtual void BeginPlay() override;

	UFUNCTION(Exec)
	void ToggleManager(int RenderTargetNum, int AnimationNum);

	UPROPERTY()
	TArray<UManagerRenderTargetWidget*> ManagerRenderTarget;

	UPROPERTY()
	TArray<ARenderTargetScenario*> RenderTargetScenario;
};
