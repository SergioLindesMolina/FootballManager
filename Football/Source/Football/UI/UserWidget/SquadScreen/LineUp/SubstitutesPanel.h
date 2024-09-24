// Copyright, 2023, by NGD Studios AB. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include <Football/Formation/GridGenerator/GridActor.h>
#include "SubstitutesPanel.generated.h"

class UFootballerObject;
class AFootballerChip;
class UChipFootballerWidget;
class AEmptyChip;
class AGridGenerator;

UCLASS()
class FOOTBALL_API ASubstitutesPanel : public AActor
{
	GENERATED_BODY()
	
public:	

	UFUNCTION(BlueprintCallable)
	void SetSubstitutes(TArray<UFootballerObject*> Footballers, UTeam_Deprecated* InTeam);

protected:

	UChipFootballerWidget* CreateChip(UFootballerObject* Footballer, UTeam_Deprecated* InTeam, AGridActor* GridActor);

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	TSubclassOf<AFootballerChip> FootballerChipSubclass;
	
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	TArray<AGridGenerator*> GridGenerators;

	TArray<AGridActor*> AllGridActors;

	TArray<AFootballerChip*> ChipsToSave;
};
