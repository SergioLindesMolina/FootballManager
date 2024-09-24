// Copyright, 2023, by NGD Studios AB. All rights reserved.

#pragma once

#include "IUsableActor.generated.h"

UINTERFACE(MinimalAPI, Blueprintable)
class UUsableActor : public UInterface
{
	GENERATED_BODY()
};

class IUsableActor
{    
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "UsableActor")
	bool OnCanUse(APlayerController* PlayerController) const;
	virtual bool OnCanUse_Implementation(APlayerController*  PlayerController) const { return true; }
	
	UFUNCTION(BlueprintNativeEvent, Category = "UsableActor")
	void OnUsed(APlayerController* PlayerController);
	virtual void OnUsed_Implementation(APlayerController*  PlayerController) { }

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "UsableActor")
	void OnCursorEnter(APlayerController* PlayerController);
	virtual void OnCursorEnter_Implementation(APlayerController* PlayerController) { }
	
	UFUNCTION(BlueprintNativeEvent, Category = "UsableActor")
	void OnCursorHover(APlayerController* PlayerController);
	virtual void OnCursorHover_Implementation(APlayerController* PlayerController) { }
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "UsableActor")
	void OnCursorRelease(APlayerController* PlayerController);
	virtual void OnCursorRelease_Implementation(APlayerController* PlayerController) { }

	UFUNCTION(BlueprintNativeEvent, Category = "UsableActor")
	FText OnGetTooltipName(APlayerController* PlayerController);
	virtual FText OnGetTooltipName_Implementation(APlayerController*  PlayerController) { return FText::GetEmpty(); }

public:
	// GameTraceChannel used by ALockerRoomPlayerController to detect IUsableActor
	inline static constexpr ECollisionChannel GameTraceChannel = ECC_GameTraceChannel1;
};
