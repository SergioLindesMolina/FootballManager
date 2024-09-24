// Copyright, 2023, by NGD Studios AB. All rights reserved.

#include "BackendBridgeLibrary.h"
#include "HttpModule.h"
#include "Interfaces/IHttpResponse.h"
#include "Football/Manager/ManagerPlayerState.h"
#include "Football/Manager/ManagerGameState.h"

static TAutoConsoleVariable<bool> CVarBackendSimulate(
	TEXT("Backend.Simulate"),
	true,
	TEXT("If true, then there's no backend needed for all the server communication"),
	ECVF_Cheat
);

static TAutoConsoleVariable<FString> CVarBackendUrl(
	TEXT("Backend.url"),
	"http://127.0.0.1:8080",
	TEXT("Backend url")
);

static TSharedRef<IHttpRequest, ESPMode::ThreadSafe> CreateHttpRequest(EHttpVerb Verb, const FString& Url)
{
	TSharedRef<IHttpRequest, ESPMode::ThreadSafe> Req = FHttpModule::Get().CreateRequest();
	switch (Verb)
	{
	case Get:
		Req->SetVerb(TEXT("GET"));
		break;
	case Post:
		Req->SetVerb(TEXT("POST"));
		break;
	default:
		checkNoEntry();
		break;
	}
	Req->SetURL(CVarBackendUrl.GetValueOnGameThread() + Url);

	return Req;
}

void UBackendAsyncActionBase::LoopbackAction()
{
	checkNoEntry();
}

void UBackendAsyncActionBase::RequestCompleteAction(TSharedPtr<FJsonObject> JsonObject)
{
	checkNoEntry();
}

void UBackendAsyncActionBase::Activate()
{
	Super::Activate();

	if (CVarBackendSimulate.GetValueOnGameThread())
	{
		LoopbackAction();
		SetReadyToDestroy();
	}
	else
	{
		TSharedRef<IHttpRequest, ESPMode::ThreadSafe> Req = CreateHttpRequest(Verb, Url);
		Req->OnProcessRequestComplete().BindLambda([=](FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded)
			{
				if (bSucceeded)
				{
					if (HttpResponse->GetResponseCode() == 200)
					{
						FString Json = HttpResponse->GetContentAsString();
						UE_LOG(LogTemp, Log, TEXT("[%s]"), *Json);

						TSharedPtr<FJsonObject> JsonObject;
						TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(Json);
						FJsonSerializer::Deserialize(Reader, JsonObject);
						//RequestCompleteAction(JsonObject);
					}
				}
				//SetReadyToDestroy();
			});
		Req->ProcessRequest();
	}
}

UBackendBridgeGenTeamFromGeneratorAsyncAction* UBackendBridgeGenTeamFromGeneratorAsyncAction::AsyncGenerateTeamFromGenerator
(UObject* WorldContextObject, FTeamGenerator GeneratorData)
{
	UBackendBridgeGenTeamFromGeneratorAsyncAction* AsyncAction = NewObject<UBackendBridgeGenTeamFromGeneratorAsyncAction>();
	AsyncAction->RegisterWithGameInstance(WorldContextObject);
	AsyncAction->GeneratorData = GeneratorData;
	AsyncAction->Verb = EHttpVerb::Get;
	AsyncAction->Url = TEXT("/generate-team");

	return AsyncAction;
}

void UBackendBridgeGenTeamFromGeneratorAsyncAction::LoopbackAction()
{
	UTeam_Deprecated* Team = UTeamGeneratorFunctionLibrary::GenerateTeamWithGenerator(GeneratorData);
	Completed.Broadcast(Team);
}

void UBackendBridgeGenTeamFromGeneratorAsyncAction::RequestCompleteAction(TSharedPtr<FJsonObject> JsonObject)
{
	Completed.Broadcast(NewObject<UTeam_Deprecated>());
}

void UBackendTrainTeamAsyncAction::LoopbackAction()
{
	for (const ESkillType& SkillType : Training.SkillsToTrain)
	{
		check(SkillType < ESkillType::Max);

		for (UFootballerObject* Footballer : Team->Starters)
		{
			//TODO David: Make training
			//Footballer.Skills[(uint8)SkillType] += FMath::RandRange(Training.ImprovementBase, Training.ImprovementMax);
		}
	}

	FTraining* CurTraining = &RegisteredWithGameInstance->GetWorld()->GetGameState<AManagerGameState>()->CurrentTraining;
	CurTraining->IsRunning = true;
	CurTraining->TrainingData = Training;
	CurTraining->TimeTrainingStarted = FDateTime::UtcNow();

	RequestCompleted.Broadcast();
}

void UBackendTrainTeamAsyncAction::RequestCompleteAction(TSharedPtr<FJsonObject> JsonObject)
{
	RequestCompleted.Broadcast();
}


UBackendTrainTeamAsyncAction* UBackendTrainTeamAsyncAction::AsyncTrainTeam(UObject* WorldContextObject, const FTrainingData& Training, UTeam_Deprecated* Team)
{
	UBackendTrainTeamAsyncAction* AsyncAction = NewObject<UBackendTrainTeamAsyncAction>();
	AsyncAction->RegisterWithGameInstance(WorldContextObject);
	AsyncAction->Verb = EHttpVerb::Post;
	AsyncAction->Url = TEXT("/train-team");

	AsyncAction->Team = Team;
	AsyncAction->Training = Training;

	return AsyncAction;
}

UBackendScoutAsyncAction* UBackendScoutAsyncAction::AsyncScoutAction(UObject* WorldContextObject)
{
	UBackendScoutAsyncAction* AsyncAction = NewObject<UBackendScoutAsyncAction>();
	AsyncAction->RegisterWithGameInstance(WorldContextObject);
	AsyncAction->Verb = EHttpVerb::Get;
	AsyncAction->Url = TEXT("/scout");

	return AsyncAction;
}

void UBackendScoutAsyncAction::LoopbackAction()
{
	//TODO Change to new generate or redo 
	//TODO David: Make scout work again
	UTeam_Deprecated* Team = UTeamGeneratorFunctionLibrary::GenerateTeamWithGenerator(ScoutTeamGenerator);
//	TArray<UFootballerObject*>* ScoutDatabase = &RegisteredWithGameInstance->GetWorld()->GetGameState<AManagerGameState>()->ScoutDatabase;
//	ScoutDatabase->Append(Team->Starters);
	//RequestCompleted.Broadcast(*ScoutDatabase);
}

void UBackendScoutAsyncAction::RequestCompleteAction(TSharedPtr<FJsonObject> JsonObject)
{
	//Parse json
	RequestCompleted.Broadcast(TArray<UFootballerObject*>());
}


UBackendBuyFootballerAsyncAction* UBackendBuyFootballerAsyncAction::AsyncBuyFootballerAction(UObject* WorldContextObject, UFootballerObject* Footballer)
{
	UBackendBuyFootballerAsyncAction* AsyncAction = NewObject<UBackendBuyFootballerAsyncAction>();
	AsyncAction->RegisterWithGameInstance(WorldContextObject);
	AsyncAction->Verb = EHttpVerb::Post;
//	AsyncAction->Url = FString::Printf(TEXT("/buy-footballer?id=%d"), Footballer->Id);
//	AsyncAction->Footballer = Footballer;

	return AsyncAction;
}

void UBackendBuyFootballerAsyncAction::RequestCompleteAction(TSharedPtr<FJsonObject> JsonObject)
{
	RequestCompleted.Broadcast(false);
}

void UBackendBuyFootballerAsyncAction::LoopbackAction()
{
	AManagerPlayerState* PlayerState = RegisteredWithGameInstance->GetWorld()->GetFirstPlayerController()->GetPlayerState<AManagerPlayerState>();
		
//	if (PlayerState->TrySpend(Footballer->Salary))
	{
//		Footballer->LineupPosition = EFootballerLineUp::Reserve;
		//TODO David: Make buy work again
	//	PlayerState->CurrentTeam->Reservers.Add(Footballer);
//		RegisteredWithGameInstance->GetWorld()->GetGameState<AManagerGameState>()->ScoutDatabase.Remove(Footballer);
		RequestCompleted.Broadcast(true);
	}
//	else
	{
//		RequestCompleted.Broadcast(false);
	}
}

UBackendBridgeSetTeamName* UBackendBridgeSetTeamName::AsyncSetTeamName(UObject* WorldContextObject, const FString& TeamName)
{
	UBackendBridgeSetTeamName* AsyncAction = NewObject<UBackendBridgeSetTeamName>();
	AsyncAction->RegisterWithGameInstance(WorldContextObject);
	AsyncAction->Verb = EHttpVerb::Post;
	AsyncAction->Url = FString::Printf(TEXT("/set-teamname?name=%s"), *TeamName);

	return AsyncAction;
}

void UBackendBridgeSetTeamName::LoopbackAction()
{
	Completed.Broadcast(true);
}

void UBackendBridgeSetTeamName::RequestCompleteAction(TSharedPtr<FJsonObject> JsonObject)
{
	Completed.Broadcast(false);
}

UBackendGetServerTime* UBackendGetServerTime::AsyncGetServerTime(UObject* WorldContextObject)
{
	UBackendGetServerTime* AsyncAction = NewObject<UBackendGetServerTime>();
	AsyncAction->RegisterWithGameInstance(WorldContextObject);
	AsyncAction->Verb = EHttpVerb::Get;
	AsyncAction->Url = TEXT("/get-time");

	return AsyncAction;
}

void UBackendGetServerTime::LoopbackAction()
{
	if (AManagerGameState* GameState = Cast<AManagerGameState>(RegisteredWithGameInstance->GetWorld()->GetGameState()))
	{
		GameState->ServerTime = FDateTime::UtcNow().GetTicks();
		Completed.Broadcast(true);
	}
	else
	{
		Completed.Broadcast(false);
	}
}

void UBackendGetServerTime::RequestCompleteAction(TSharedPtr<FJsonObject> JsonObject)
{
	Completed.Broadcast(false);
}