// Copyright, 2023, by NGD Studios AB. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Football/Manager/Training.h"
#include "Football/Team/TeamGenerator.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "BackendBridgeLibrary.generated.h"


/**
 * Communication between client and backend, it will also make a loopback if no backend is present (cheat)
 */

enum EHttpVerb
{
	Get,
	Post
};

class UNameByRegionDataAsset;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnTeamGenerated, UTeam_Deprecated*, Generated);

UCLASS(Abstract)
class FOOTBALL_API UBackendAsyncActionBase : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()
public:

	virtual void Activate() override;
	virtual void LoopbackAction();
	virtual void RequestCompleteAction(TSharedPtr<FJsonObject> JsonObject);

	EHttpVerb Verb;
	FString Url;
};


UCLASS()
class FOOTBALL_API UBackendBridgeGenTeamFromGeneratorAsyncAction : public UBackendAsyncActionBase
{
	GENERATED_BODY()
public:

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true", WorldContext = "WorldContextObject"), Category = "Backend")
	static UBackendBridgeGenTeamFromGeneratorAsyncAction* AsyncGenerateTeamFromGenerator(UObject* WorldContextObject,FTeamGenerator GeneratorData);

	UPROPERTY(BlueprintAssignable)
	FOnTeamGenerated Completed;
	FTeamGenerator GeneratorData;

	virtual void LoopbackAction() override;
	virtual void RequestCompleteAction(TSharedPtr<FJsonObject> JsonObject) override;
};


DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnSimpleRequestCompleted);

UCLASS()
class FOOTBALL_API UBackendTrainTeamAsyncAction : public UBackendAsyncActionBase
{
	GENERATED_BODY()
public:

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true", WorldContext = "WorldContextObject"), Category = "Backend")
	static UBackendTrainTeamAsyncAction* AsyncTrainTeam(UObject* WorldContextObject, const FTrainingData& Training, UTeam_Deprecated* Team);

	FTrainingData Training;
	UTeam_Deprecated* Team;

	UPROPERTY(BlueprintAssignable)
	FOnSimpleRequestCompleted RequestCompleted;

	virtual void LoopbackAction() override;
	virtual void RequestCompleteAction(TSharedPtr<FJsonObject> JsonObject) override;
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnScoutCompleted, TArray<UFootballerObject*>, Footballers);

UCLASS()
class FOOTBALL_API UBackendScoutAsyncAction : public UBackendAsyncActionBase
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true", WorldContext = "WorldContextObject"), Category = "Backend")
	static UBackendScoutAsyncAction* AsyncScoutAction(UObject* WorldContextObject);

	UPROPERTY(BlueprintAssignable)
	FOnScoutCompleted RequestCompleted;
	FTeamGenerator ScoutTeamGenerator;

	virtual void LoopbackAction() override;
	virtual void RequestCompleteAction(TSharedPtr<FJsonObject> JsonObject) override;
};


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSimpleRequestWithConfirmation, bool, Success);

UCLASS()
class FOOTBALL_API UBackendBuyFootballerAsyncAction : public UBackendAsyncActionBase
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true", WorldContext = "WorldContextObject"), Category = "Backend")
	static UBackendBuyFootballerAsyncAction* AsyncBuyFootballerAction(UObject* WorldContextObject, UFootballerObject* Footballer);

	UFootballer_Deprecated* Footballer;

	UPROPERTY(BlueprintAssignable)
	FOnSimpleRequestWithConfirmation RequestCompleted;

	virtual void LoopbackAction() override;
	virtual void RequestCompleteAction(TSharedPtr<FJsonObject> JsonObject) override;
};

UCLASS()
class FOOTBALL_API UBackendBridgeSetTeamName : public UBackendAsyncActionBase
{
	GENERATED_BODY()
public:

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true", WorldContext = "WorldContextObject"), Category = "Backend")
		static UBackendBridgeSetTeamName* AsyncSetTeamName(UObject* WorldContextObject, const FString& TeamName);

	UPROPERTY(BlueprintAssignable)
		FOnSimpleRequestWithConfirmation Completed;

	virtual void LoopbackAction() override;
	virtual void RequestCompleteAction(TSharedPtr<FJsonObject> JsonObject) override;
};

UCLASS()
class FOOTBALL_API UBackendGetServerTime : public UBackendAsyncActionBase
{
	GENERATED_BODY()
public:

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true", WorldContext = "WorldContextObject"), Category = "Backend")
	static UBackendGetServerTime* AsyncGetServerTime(UObject* WorldContextObject);

	UPROPERTY(BlueprintAssignable)
	FOnSimpleRequestWithConfirmation Completed;

	virtual void LoopbackAction() override;
	virtual void RequestCompleteAction(TSharedPtr<FJsonObject> JsonObject) override;
};
