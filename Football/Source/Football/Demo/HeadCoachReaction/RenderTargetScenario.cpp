// Copyright, 2023, by NGD Studios AB. All rights reserved.

#include "RenderTargetScenario.h"

ARenderTargetScenario::ARenderTargetScenario()
{
	SceneComp = CreateDefaultSubobject<USceneComponent>("Scene Component");
	SceneComp->SetupAttachment(this->RootComponent);
	RootComponent = SceneComp;

	SkelMesh = CreateDefaultSubobject<USkeletalMeshComponent>("Skeletal Mesh Component");
	SkelMesh->SetupAttachment(RootComponent);
}

void ARenderTargetScenario::PlayAnimation(int AnimationNum)
{
	SkelMesh->PlayAnimation(AnimSequence[AnimationNum], false);
}
