// Copyright, 2023, by NGD Studios AB. All rights reserved.


#include "TutorialHub.h"
#include "TutorialAction.h"
#include "TutorialValidator.h"
#include "Tutorial.h"

ATutorialHub::ATutorialHub()
{
	PrimaryActorTick.bCanEverTick = true;

}

bool ATutorialHub::Add(const FName& Name, UTutorial* Tutorial)
{
	bool Result = true;
	UTutorial* DuplicateTutorial = DuplicateObject<UTutorial>(Tutorial, this);
	//UTutorial* DuplicateTutorial = NewObject<UTutorial>(this, "Tutorial", EObjectFlags::RF_Transient, Tutorial);

	/*
	* DuplicateObject does not copy the values from arrays so is necessary to copy those manually
	* In this chase is necessary to copy the array of actions and the array of validators of each action
	*/
	if (DuplicateTutorial)
	{
		DuplicateTutorial->Actions.Empty();

		for (UTutorialAction* Action : Tutorial->Actions)
		{
			UTutorialAction* DuplicateAction = DuplicateObject<UTutorialAction>(Action, DuplicateTutorial);

			if (DuplicateAction)
			{
				DuplicateAction->Validators.Empty();

				for (UTutorialValidator* Validator : Action->Validators)
				{
					UTutorialValidator* DuplicateValidator = DuplicateObject<UTutorialValidator>(Validator, DuplicateAction);

					DuplicateAction->Validators.Add(DuplicateValidator);
				}

				DuplicateTutorial->Actions.Add(DuplicateAction);
			}
			else
			{
				Result = false;
			}
		}
	}
	else
	{
		Result = false;
	}

	if (DuplicateTutorial)
	{

		Tutorials.Add(Name, DuplicateTutorial);
	}


	return Result;
}

bool ATutorialHub::Remove(const FName& Name)
{
	if (Tutorials.Contains(Name))
	{
		UTutorial* Value;
		Tutorials.RemoveAndCopyValue(Name, Value);
		Value = nullptr;
		return true;
	}
	else
	{
		return false;
	}
}

bool ATutorialHub::Play(const FName& Name)
{
	if (Tutorials.Contains(Name))
	{
		PlayingTutorial = Tutorials[Name];
		return true;
	}

	return false;
}

void ATutorialHub::ClearPlayingTutorial()
{
	if (PlayingTutorial)
	{
		for (UTutorialAction* Action : PlayingTutorial->Actions)
		{
			check(Action);

			if (!Action->bCompleted)
			{
				Action->Clear(GetWorld());
				PlayingTutorial = nullptr;
				return;
			}
		}


	}
}

void ATutorialHub::BeginPlay()
{
	Super::BeginPlay();

	//TODO Sergio Load the tutorials from a folder directly, currently they are being add in the begin play from blueprint

}

void ATutorialHub::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (PlayingTutorial)
	{
		for (UTutorialAction* Action : PlayingTutorial->Actions)
		{
			check(IsValid(Action));

			if (!Action->bCompleted)
			{
				if (Action->bValidatorsCompleted)
				{
					Action->Do(GetWorld());
				}
				else
				{
					Action->CheckValidators(GetWorld());
				}

				return;
			}
		}

		PlayingTutorial = nullptr;
	}
}

