// Copyright, 2023, by NGD Studios AB. All rights reserved.

#pragma once

#include <CoreMinimal.h>
#include <GameFramework/Actor.h>
#include "GridActor.generated.h"

UCLASS()
class FOOTBALL_API AGridActor : public AActor
{
	GENERATED_BODY()

public:

	UFUNCTION()
	void SetId(int XCoord);

protected:

	AGridActor();

private:

	int Id;
};
