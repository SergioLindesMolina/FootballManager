// Copyright, 2023, by NGD Studios AB. All rights reserved.


#include "GridGenerator.h"

void AGridGenerator::InitGrid()
{
	if(!GridActors.IsEmpty())
	{
		return;
	}

	StartPositionInWorld = this->GetActorLocation();
	
	for(int y = 0; y < Height; y++)
	{
		for(int x = 0; x < Width; x++)
		{
			const FVector GridActorTransform(StartPositionInWorld.X + (x * DistanceBetweenActors), StartPositionInWorld.Y + (y * DistanceBetweenActors), StartPositionInWorld.Z);
			FActorSpawnParameters GridActorSpawnParameters;
			GridActorSpawnParameters.Owner = this;
			AGridActor* GridActor = GetWorld()->SpawnActor<AGridActor>(GridActorTransform, FRotator::ZeroRotator, GridActorSpawnParameters);
			const int CalculateId = (y * Width) + x;
			GridActor->SetId(CalculateId);
			GridActors.Add(GridActor);

			GridActor->SetActorHiddenInGame(IsHidden());
			GridActor->AttachToActor(this, FAttachmentTransformRules::KeepWorldTransform);
		}
	}
}
