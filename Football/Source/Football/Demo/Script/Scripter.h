// Copyright, 2023, by NGD Studios AB. All rights reserved.

#pragma once

#include <CoreMinimal.h>
#include <GameFramework/Actor.h>
#include <UnrealImGui.h>
#include <Engine/DataTable.h>

#include "Scripter.generated.h"


/**
 * Data for the script sequence, every entry is executed at the given time.
 * It has a type and 3 params
 */
USTRUCT(BlueprintType)
struct FScriptStepEvent : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly)
	uint8 Minutes = 0;

	UPROPERTY(EditDefaultsOnly)
	uint8 Seconds = 0;

	UPROPERTY(EditDefaultsOnly)
	FName Type;
	
	UPROPERTY(EditDefaultsOnly)
	FString Id;

	UPROPERTY(EditDefaultsOnly)
	FString Param1;

	UPROPERTY(EditDefaultsOnly)
	FString Param2;

	UPROPERTY(EditDefaultsOnly)
	FString Param3;
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FOnScriptStepMulti, FName, Type, uint8, Minute, uint8, Second, const TArray<FString>&, Params);
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnScriptStep, uint8, Minute, uint8, Second, const TArray<FString>&, Params);

/**
 * The Scripter class is responsible for continuously monitoring a sequence of steps (FScriptStepEvent).
 * A delegate triggers an event notification containing the event type and parameters when appropriate conditions are met.
 * The script halts automatically upon reaching the final line.
 * Manual initiation is required via the "Start" function.
 */
UCLASS()
class FOOTBALL_API AScripter : public AActor
{
	GENERATED_BODY()
	DEFINE_IMGUI_SCREEN(AScripter)


protected:
	AScripter();
	void BeginPlay() override;
	void Tick(float DeltaSeconds) override;

private:
	void PreStart();
	void BroadcastEvent(FName Type, uint8 Minutes, uint8 Seconds, const TArray<FString>& Params);
	
public:
	//Will start the scripter from the beginning
	UFUNCTION(BlueprintCallable)
	void Start();

	//Will stop the scripter, it must be manually resumed or started over
	UFUNCTION(BlueprintCallable)
	void Stop();

	//Will resume the scripter from the previous time
	UFUNCTION(BlueprintCallable)
	void Resume();

	UFUNCTION(BlueprintPure, BlueprintCallable)
	bool IsRunning();

	UFUNCTION(BlueprintCallable)
	void RegisterForEventType(FName Type, const FOnScriptStep& Delegate);

	UFUNCTION(BlueprintCallable)
	void DeregisterForEventType(FName Type, const FOnScriptStep& Delegate);



public:	
	//How many seconds should the match advance per real life seconds
	UPROPERTY(EditAnywhere, Category=Football)
	int32 SecondsIncrement = 40;

	UPROPERTY(EditAnywhere, Category=Football, meta=(RequiredAssetDataTags = "RowStructure=/Script/Football.ScriptStepEvent"))
	UDataTable* ScriptEventsTable;

	UPROPERTY(BlueprintAssignable)
	FOnScriptStepMulti OnScriptStep;
	
private:
	FDateTime CurrentTime;
	int32 CurrentIndex = 0;
	bool bRunning = false;

	//Only used to get data out of a DataTable, no memory is created in the middle
	TArray<FScriptStepEvent*> ScriptEvents;
	TMap<FName, TArray<FOnScriptStep>> DelegatesPerType;

	float SecondCounter = 0;

#ifdef WITH_IMGUI
	void InsideImGui();
	int32 DebugMinutes = 45;
	int32 DebugSeconds = 0;
#endif
};
