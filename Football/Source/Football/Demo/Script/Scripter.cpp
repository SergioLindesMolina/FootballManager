// Copyright, 2023, by NGD Studios AB. All rights reserved.

#include "Scripter.h"

#include <Logging/LogMacros.h>

DEFINE_LOG_CATEGORY_STATIC(LogScripter, Log, All);

AScripter::AScripter()
{
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = false;
}

void AScripter::PreStart()
{
	CurrentTime = FDateTime(1, 1, 1, 0, 0, 0) + FTimespan::FromMinutes(ScriptEvents[0]->Minutes) + FTimespan::FromSeconds(ScriptEvents[0]->Seconds);
	CurrentIndex = 0;
}

void AScripter::BroadcastEvent(FName Type, uint8 Minutes, uint8 Seconds, const TArray<FString>& Params)
{
	OnScriptStep.Broadcast(Type, Minutes, Seconds, Params);

	TArray<FOnScriptStep>* StepDelegates = DelegatesPerType.Find(Type);
	if (StepDelegates)
	{
		for (const FOnScriptStep& Step : *StepDelegates)
		{
			Step.Execute(Minutes, Seconds, Params);
		}
	}

	UE_LOG(LogScripter, Log, TEXT("Broadcasting %s, %d, %d. With Param count %d"), *Type.ToString(), Minutes, Seconds, Params.Num());
	for (const FString& P : Params)
	{
		UE_LOG(LogScripter, Log, TEXT("\t%s"), *P);
	}
}

void AScripter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	FTimespan Elapsed = FTimespan::FromSeconds(DeltaSeconds * SecondsIncrement);
	CurrentTime += Elapsed;

	SecondCounter += DeltaSeconds;

	if (SecondCounter > 1.0f)
	{
		SecondCounter -= 1.0f;

		uint8 Minutes = CurrentTime.GetMinute() + CurrentTime.GetHour() * 60;
		BroadcastEvent(FName("Timer"), Minutes, CurrentTime.GetSecond(), TArray<FString>());
	}

	for (int32 i = CurrentIndex; i < ScriptEvents.Num(); ++i)
	{
		const FScriptStepEvent* Data = ScriptEvents[i];

		FDateTime StepTime = FDateTime(1, 1, 1, 0, 0, 0) + FTimespan::FromMinutes(Data->Minutes) + FTimespan::FromSeconds(Data->Seconds);

		if (StepTime <= CurrentTime)
		{
			TArray<FString> Params;
			if (!Data->Param1.IsEmpty())
			{
				Params.Add(Data->Param1);
			}
			if (!Data->Param2.IsEmpty())
			{
				Params.Add(Data->Param2);
			}
			if (!Data->Param3.IsEmpty())
			{
				Params.Add(Data->Param3);
			}

			BroadcastEvent(Data->Type, Data->Minutes, Data->Seconds, Params);

			//Last one executed, then stop
			if (i == ScriptEvents.Num() - 1)
			{
				Stop();
			}
		}
		else
		{
			CurrentIndex = i;
			break;
		}
	}
}

#ifdef WITH_IMGUI
void AScripter::InsideImGui()
{
	ImGui::Text("Is Scripter running? %s", IsActorTickEnabled() ? "Yes" : "No");
	ImGui::Text("Restart from"); ImGui::SameLine();
	ImGui::PushItemWidth(90);
	ImGui::InputInt("Minutes", &DebugMinutes); ImGui::SameLine();
	ImGui::InputInt(" Seconds", &DebugSeconds); ImGui::SameLine();
	ImGui::PopItemWidth();
	if (ImGui::Button("Go!"))
	{
		CurrentTime = FDateTime(1, 1, 1, 0, DebugMinutes, DebugSeconds);
		CurrentIndex = 0;
		for (int32 i = 0; i < ScriptEvents.Num(); ++i)
		{
			const FScriptStepEvent* Data = ScriptEvents[i];

			FDateTime StepTime = FDateTime(1, 1, 1, 0, 0, 0) + FTimespan::FromMinutes(Data->Minutes) + FTimespan::FromSeconds(Data->Seconds);

			if (StepTime >= CurrentTime)
			{
				CurrentIndex = i;
				break;
			}
		}
	}

	if (ImGui::Button("Start"))
	{
		Start();
	}
	ImGui::SameLine();
	if (ImGui::Button("Stop"))
	{
		Stop();
	}
	ImGui::SameLine();
	if (ImGui::Button("Resume"))
	{
		Resume();
	}
	ImGui::InputInt("Seconds Increment", &SecondsIncrement);
}
#endif //WITH_IMGUI

void AScripter::BeginPlay()
{
	Super::BeginPlay();

	SetActorTickEnabled(false);

	ScriptEventsTable->GetAllRows<FScriptStepEvent>(__FILE__, ScriptEvents);

	PreStart();

	IMPLEMENT_IMGUI_SCREEN
	(
		InsideImGui();
	);
}

void AScripter::Start()
{
	PreStart();
	SetActorTickEnabled(true);

	UE_LOG(LogScripter, Log, TEXT("Start"));
	bRunning = true;
}

void AScripter::Stop()
{
	SetActorTickEnabled(false);
	UE_LOG(LogScripter, Log, TEXT("Stop"));
	bRunning = false;
}

void AScripter::Resume()
{
	SetActorTickEnabled(true);
	UE_LOG(LogScripter, Log, TEXT("Resume"));
	bRunning = true;
}

bool AScripter::IsRunning()
{
	return bRunning;
}

void AScripter::RegisterForEventType(FName Type, const FOnScriptStep& Delegate)
{
	TArray<FOnScriptStep> &Delegates = DelegatesPerType.FindOrAdd(Type);
	Delegates.AddUnique(Delegate);
}

void AScripter::DeregisterForEventType(FName Type, const FOnScriptStep& Delegate)
{
	TArray<FOnScriptStep> *Delegates = DelegatesPerType.Find(Type);
	if (Delegates)
	{
		for (int32 i = 0; i < Delegates->Num(); ++i)
		{
			FOnScriptStep& Step = (*Delegates)[i];
			if (Step == Delegate)
			{
				Step.Unbind();
				Delegates->RemoveAtSwap(i);
				break;
			}
		}
	}
}
