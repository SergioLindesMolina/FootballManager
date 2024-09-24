// Copyright, 2023, by NGD Studios AB. All rights reserved.

#include "FootballerPlayerStart.h"
#include "Components/BillboardComponent.h"

AFootballerPlayerStart::AFootballerPlayerStart(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	#if WITH_EDITORONLY_DATA
	if (GetGoodSprite())
	{
		ConstructorHelpers::FObjectFinderOptional<UTexture2D> FootballerEntity(TEXT("Texture2D'/Game/Football/EditorContent/T_FootballerEntity.T_FootballerEntity'"));
		FootballerEntityTeture	 = FootballerEntity.Get();
		GetGoodSprite()->SetSprite(FootballerEntityTeture);
	}
	#endif
}
