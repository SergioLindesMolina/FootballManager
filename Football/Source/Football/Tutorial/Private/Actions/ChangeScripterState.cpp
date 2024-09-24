// Copyright, 2023, by NGD Studios AB. All rights reserved.


#include "Football/Tutorial/Public/Actions/ChangeScripterState.h"
#include "Football/Demo/Script/Scripter.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Actor.h"

void UChangeScripterState::Do(const UObject* WorldContextObject)
{	
	if (const auto* World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull))
	{
		TArray<AActor*> MapScripters;
		UGameplayStatics::GetAllActorsOfClass(World, AScripter::StaticClass(), MapScripters);

		if (MapScripters.Num() > 0)
		{
			if (MapScripters.Num() > 1)
			{
				UE_LOG(LogTemp, Warning, TEXT("In the current map are cunrrently more than one scripter actor, should only exist one per map"));
			}

			MapScripter = Cast<AScripter>(MapScripters.Pop());
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("In the current map does not exist a scripter actor please add one"));
			checkNoEntry();
		}


		if (DesiredScripterState == EScripterState::Resume)
		{
			MapScripter->Resume();
			bCompleted = true;
		}
		else if (DesiredScripterState == EScripterState::Stop)
		{
			MapScripter->Stop();
			bCompleted = true;
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("Invalid DesiredScripterState"));
		}
	
	}
}

