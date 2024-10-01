// Copyright, 2023, by NGD Studios AB. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Tutorial.generated.h"


class UTutorialAction;

/**
 * Class that contains all the actions necessary to complete a tutorial, this asset will be copied before runtime usage to avoid the permanent modification of 
 * properties inside every TutorialAction
 */
UCLASS()
class TUTORIALCRAFTER_API UTutorial : public UDataAsset
{
	GENERATED_BODY()

public:

	/*
	* TODO Sergio Add property to control if the tutorial freeze the game or not, this way an action is not required every time
	*/

	/*
	* Todo Sergio wrap the tutorial actions inside other class/struct called step to allow more fine control of the tutorials
	*/

	/*
	* TODO Sergio Add a property that saves the state of the tutorial if is completed or not 
	*/

	/*
	* TODO Sergio Add a property to know if the tutorial is repeatable after being completed
	*/

	/*
	* TODO Sergio Find if is possible to divide each tutorial action and validator between data and functionality to avoid the duplication of necessary data
	*/

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Instanced, DuplicateTransient, Category = "TutorialCrafter|Tutorial")
	TArray<UTutorialAction*> Actions;



};