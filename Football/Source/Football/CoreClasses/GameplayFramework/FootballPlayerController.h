// Copyright, 2023, by NGD Studios AB. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "FootballPlayerController.generated.h"

class IUsableActor;
class SOverlayWorldTooltip;
class UInputMappingContext;

/**
 * Base class of Football project. All PlayerControllers should inherit from here.
 * Contains base code to all basic mechanic of the game.
 *
 * Please, to specific mechanics, inherit from here. 
 */
UCLASS()
class FOOTBALL_API AFootballPlayerController : public APlayerController
{
	GENERATED_BODY()

protected:
	AFootballPlayerController();
	
	void BeginPlay() override;
	void Tick(float DeltaTime) override;
	void SetupInputComponent() override;
	
protected:
	void DisplayWorldTooltip(const FText& Text) const;
	void HideWorldTooltip() const;

private:
	void CalculateActorUnderCursor();


	
protected:
	//~=================================================================================================================
	// InputMappingContext functions
	//~=================================================================================================================
	
	UFUNCTION(BlueprintNativeEvent)
	void OnDialogueBoxAdvancePressed(const FInputActionValue& Value);

	UFUNCTION(BlueprintNativeEvent)
	void OnUsableActorUse(const FInputActionValue& Value);

	UFUNCTION(BlueprintNativeEvent)
	void OnPauseMenuPressed(const FInputActionValue& Value);

	UFUNCTION(BlueprintNativeEvent)
	void OnLeftMouseButton(const FInputActionValue& Value);
	
private:
	//~=================================================================================================================
	// Properties
	//~=================================================================================================================
	
	TSharedPtr<SOverlayWorldTooltip> OverlayWorldTooltip;
	FCollisionQueryParams QueryParams;

	struct FUsableItemUnderCursor
	{
		FUsableItemUnderCursor() = default; // DEFINE_VTABLE_PTR_HELPER_CTOR requisite
		explicit FUsableItemUnderCursor(AFootballPlayerController* InPlayerController);
		void operator=(AActor* Other);
		void Use();
		void Reset();
	
	private:
		TWeakObjectPtr<AActor> UsableItemUnderCursor;
		TWeakObjectPtr<AFootballPlayerController> PlayerController;
	}
	UsableItemUnderCursor;

	UPROPERTY()
	UInputMappingContext* InputMappingContext {};

	
public:
	//~=================================================================================================================
	// Input Mapping Names
	//~=================================================================================================================
	
	inline static constexpr const char* InputActionName_BoxAdvance		= "IA_DialogueBoxAdvance";
	inline static constexpr const char* InputActionName_UsableActorUse	= "IA_UsableActorUse";
	inline static constexpr const char* InputActionName_PauseMenu		= "IA_PauseMenu";
	inline static constexpr const char* InputActionName_LeftMouseButton = "IA_LeftMouseButton";
};
