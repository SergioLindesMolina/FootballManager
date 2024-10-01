// Copyright, 2023, by NGD Studios AB. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TutorialHub.generated.h"

class UTutorial;
class SWidget;
class UUserWidget;

/*
* Level Actor that manage all the tutorials in a given map, the tutorials are duplicated at runtime to ensure that the modifications are temporary
*/
UCLASS()
class TUTORIALCRAFTER_API ATutorialHub : public AActor
{
	GENERATED_BODY()
	
public:	

	ATutorialHub();

	//Add a tutorial object to the current map of tutorials of this actor using the name as the key 
	UFUNCTION(BlueprintCallable, Category = "TutorialCrafter|CrafterActions")
	bool Add(const FName& Name, UTutorial* Tutorial);

	//Remove a tutorial object of the current map of tutorials of this actor
	UFUNCTION(BlueprintCallable, Category = "TutorialCrafter|CrafterActions")
	bool Remove(const FName& Name);

	//Tries to play a tutorial from the map of tutorials of this actor
	UFUNCTION(BlueprintCallable, Category = "TutorialCrafter|CrafterActions")
	bool Play(const FName& Name);

	//Stop and clears the current playing tutorial
	UFUNCTION(BlueprintCallable, Category = "TutorialCrafter|CrafterActions")
	void ClearPlayingTutorial();

	UFUNCTION(BlueprintImplementableEvent)
	void OnValidatorWidget(bool Result, UUserWidget* WidgetContainer);


protected:

	UPROPERTY(Transient)
	TMap<FName, UTutorial*> Tutorials;

	UPROPERTY(BlueprintReadWrite, Category = "TutorialCrafter|CrafterHub")
	UTutorial* PlayingTutorial;

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

};
