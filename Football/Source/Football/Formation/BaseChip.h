// Copyright, 2023, by NGD Studios AB. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseChip.generated.h"

class UWidgetComponent;
class UFollowMouseComponent;
class UStaticMeshComponent;

UCLASS(Abstract)
class FOOTBALL_API ABaseChip : public AActor
{
	GENERATED_BODY()

protected:
	ABaseChip();

public:

	void InitializeWidget();

	virtual void SetChipWidget();


public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widgets")
	UWidgetComponent* ChipWidget;


	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UFollowMouseComponent* FollowMouseComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Properties")
	UStaticMeshComponent* ChipMesh;

private:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Properties", meta = (AllowPrivateAccess = true))
	USceneComponent* SceneComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widgets", meta = (AllowPrivateAccess = true))
	TSubclassOf<UUserWidget> ChipWidgetClass;
};
