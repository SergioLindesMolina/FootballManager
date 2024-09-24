// Copyright, 2023, by NGD Studios AB. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RenderTargetScenario.generated.h"

/**
 * Actor To Set RenderTarget scenario and play Head Coach animations
 */

UCLASS()
class FOOTBALL_API ARenderTargetScenario : public AActor
{
	GENERATED_BODY()

private:

	ARenderTargetScenario();

public:

	void PlayAnimation(int AnimationNum);
	
public:	

	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category="Properties")
	USceneComponent* SceneComp;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Head Coach Animation")
	USkeletalMeshComponent* SkelMesh;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Head Coach Animation")
	TArray<UAnimSequence*> AnimSequence;

private:

	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (AllowPrivateAccess = true))
	bool bIsLocal = true;
};
