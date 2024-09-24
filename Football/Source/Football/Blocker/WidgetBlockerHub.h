// Copyright, 2023, by NGD Studios AB. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WidgetBlockerHub.generated.h"

class UBlockMessage;

/*
* 
* Manage the list of widget with avalible input in a map and create the appropriated message when a blocked widget is clicked
* 
*/

UCLASS()
class FOOTBALL_API AWidgetBlockerHub : public AActor
{
	GENERATED_BODY()
	
public:	
	AWidgetBlockerHub();

	UFUNCTION(BlueprintCallable)
	TArray<UWidget*> GetDefaultWidgetsWithInput();	

	void OnWidgetBlocked(TSharedPtr<SWidget> WidgetClicked);

public:

	void BeginPlay() override;

	void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

protected:

	UPROPERTY(BlueprintReadWrite)
	TArray<UWidget*> DefaultWidgetsWithInput;
	/*
	* The map tutorials currently handle the widget to show blocked messages due to this feature been only needed for the demo
	*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TSubclassOf<UBlockMessage> BlockMessageWidgetClass;

	UPROPERTY(BlueprintReadWrite)
	UBlockMessage* BlockMessageWidget;

};