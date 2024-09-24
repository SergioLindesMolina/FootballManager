// Copyright, 2023, by NGD Studios AB. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GridActor.h"
#include "GridGenerator.generated.h"

UCLASS()
class FOOTBALL_API AGridGenerator : public AActor
{
	GENERATED_BODY()

protected:

public:

	UFUNCTION(BlueprintCallable)
	void InitGrid();

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int Width;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int Height;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int DistanceBetweenActors;

	UPROPERTY(BlueprintReadWrite)
	FVector StartPositionInWorld;

	UPROPERTY()
	TArray<AGridActor*> GridActors;

};
