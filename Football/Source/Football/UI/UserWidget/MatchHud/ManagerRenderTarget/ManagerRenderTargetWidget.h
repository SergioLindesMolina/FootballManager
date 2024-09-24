// Copyright, 2023, by NGD Studios AB. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ManagerRenderTargetWidget.generated.h"

class UImage;

/**
 * Widget class to show Render Target 
 */
UCLASS()
class FOOTBALL_API UManagerRenderTargetWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:

	UPROPERTY(EditAnywhere,BlueprintReadWrite, meta = (BindWidget) )
	UImage* RenderTargetImage;
};
