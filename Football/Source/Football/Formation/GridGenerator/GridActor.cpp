// Copyright, 2023, by NGD Studios AB. All rights reserved.


#include "GridActor.h"

AGridActor::AGridActor()
{
	SetRootComponent(CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent")));
}

void AGridActor::SetId(int XCoord)
{
	Id = XCoord;
}




