// Copyright, 2023, by NGD Studios AB. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include <UnrealImGui.h>

#include "ImGuiActor.generated.h"

UCLASS()
class FOOTBALL_API AImGuiActor : public AActor
{
	GENERATED_BODY()
	DEFINE_IMGUI_SCREEN(AImGuiActor)
	
protected:
	AImGuiActor();
	virtual void BeginPlay() override;
	
private:
	UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess=true))
	int32 Var_Integer;
	
	UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess=true))
	uint32 Var_Unsigned;
	
	UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess=true))
	FString Var_String;
	
	UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess=true))
	float Var_Real;
	
	UPROPERTY(EditAnywhere, meta=(HideImGui, AllowPrivateAccess=true))
	bool Var_Boolean;
	
	UPROPERTY()
	double Var_Double = 123.456;
};
