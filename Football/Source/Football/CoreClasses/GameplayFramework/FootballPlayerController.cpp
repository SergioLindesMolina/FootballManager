// Copyright, 2023, by NGD Studios AB. All rights reserved.

#include "FootballPlayerController.h"
#include <Football/CoreClasses/Interfaces/IUsableActor.h>
#include <Slate/OverlayWorldTooltip/SOverlayWorldTooltip.h>

#include "Engine/UserInterfaceSettings.h"
#include "InputMappingContext.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"

AFootballPlayerController::AFootballPlayerController()
{
	UsableItemUnderCursor		  = FUsableItemUnderCursor(this);
	
	PrimaryActorTick.bCanEverTick = true;
	bShowMouseCursor			  = true;
	HitResultTraceDistance		  = 10000;
}

void AFootballPlayerController::BeginPlay()
{
	GetWorld()->GetGameViewport()->AddViewportWidgetContent(SAssignNew(OverlayWorldTooltip, SOverlayWorldTooltip));
	OverlayWorldTooltip->SetVisibility(EVisibility::Collapsed);
	OverlayWorldTooltip->SetEnabled(false);
	
	QueryParams.bTraceComplex = false;

	Super::BeginPlay();
}

void AFootballPlayerController::Tick(const float DeltaTime)
{
	Super::Tick(DeltaTime);
	CalculateActorUnderCursor();

	static float MouseX, MouseY;
	if(OverlayWorldTooltip->GetVisibility() != EVisibility::Collapsed && GetMousePosition(MouseX, MouseY))
	{
		FIntPoint ViewportSize;
		GetViewportSize(ViewportSize.X, ViewportSize.Y);
		
		// Set mouse position with 15px of offset
		const float Offset = 15 * GetDefault<UUserInterfaceSettings>()->GetDPIScaleBasedOnSize(ViewportSize);
		OverlayWorldTooltip->SetScreenPosition({MouseX + Offset, MouseY + Offset});
	}
}

void AFootballPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	if(UInputMappingContext* DemoInputMappingContext = LoadObject<UInputMappingContext>(this, TEXT("/Script/EnhancedInput.InputMappingContext'/Game/Football/Input/IMC_Demo.IMC_Demo'")))
	{
		InputMappingContext = DemoInputMappingContext;
		
		UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
		check(!Subsystem->HasMappingContext(InputMappingContext));
		
		Subsystem->AddMappingContext(InputMappingContext, 0);
		UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent);

		for(const FEnhancedActionKeyMapping& InputAction : InputMappingContext->GetMappings())
		{
			static const TMap<FString, void(AFootballPlayerController::*)(const FInputActionValue&)> Bindings =
			{
				{ InputActionName_BoxAdvance,		&AFootballPlayerController::OnDialogueBoxAdvancePressed	},
				{ InputActionName_UsableActorUse,	&AFootballPlayerController::OnUsableActorUse			},
				{ InputActionName_PauseMenu,		&AFootballPlayerController::OnPauseMenuPressed			},
				{ InputActionName_LeftMouseButton,	&AFootballPlayerController::OnLeftMouseButton			}
			};
			
			EnhancedInputComponent->BindAction(InputAction.Action, ETriggerEvent::Started, this, Bindings[InputAction.Action.GetName()]);
		}
	}
}

void AFootballPlayerController::DisplayWorldTooltip(const FText& Text) const
{
	check(OverlayWorldTooltip);
	
	OverlayWorldTooltip->SetVisibility(EVisibility::HitTestInvisible);
	OverlayWorldTooltip->SetEnabled(true);
	OverlayWorldTooltip->SetText(Text);
}

void AFootballPlayerController::HideWorldTooltip() const
{
	check(OverlayWorldTooltip);
	
	OverlayWorldTooltip->SetVisibility(EVisibility::Collapsed);
}

void AFootballPlayerController::CalculateActorUnderCursor()
{
	if(GetWorld()->GetGameViewport()->IgnoreInput() || !InputEnabled())
	{
		UsableItemUnderCursor.Reset();
		return;
	}

	static FVector MouseWorldLocation, MouseWorldDirection;
	if (DeprojectMousePositionToWorld(MouseWorldLocation, MouseWorldDirection))
	{
		static FHitResult Result;
		if (GetWorld()->LineTraceSingleByChannel(Result, MouseWorldLocation, MouseWorldLocation + MouseWorldDirection * HitResultTraceDistance, IUsableActor::GameTraceChannel, QueryParams))
		{
			if (auto Actor = Result.GetActor())
			{
				// We want to detect ChildActorComponents too
				if(Actor->IsChildActor()) Actor = Actor->GetParentActor();
					
				if(Actor->Implements<UUsableActor>())
				{
					UsableItemUnderCursor = Actor;
					return;
				}
			}
		}
	}

	UsableItemUnderCursor.Reset();
}

void AFootballPlayerController::OnLeftMouseButton_Implementation(const FInputActionValue& Value)
{
	/* Nothing to do here */
}

void AFootballPlayerController::OnDialogueBoxAdvancePressed_Implementation(const FInputActionValue& Value)
{
	/* Nothing to do here */
}

void AFootballPlayerController::OnUsableActorUse_Implementation(const FInputActionValue& Value)
{
	UsableItemUnderCursor.Use();
}

void AFootballPlayerController::OnPauseMenuPressed_Implementation(const FInputActionValue& Value)
{
	/* Nothing to do here */
}


//~=====================================================================================================================
// FUsableItemUnderCursor implementation
//~=====================================================================================================================
AFootballPlayerController::FUsableItemUnderCursor::FUsableItemUnderCursor(AFootballPlayerController* InPlayerController)
: PlayerController(InPlayerController) {}
	
void AFootballPlayerController::FUsableItemUnderCursor::operator=(AActor* Other)
{
	if(ensureAlways(IsValid(Other)))
	{
		if(Other != UsableItemUnderCursor)
		{
			Reset();
			
			UsableItemUnderCursor = Other;

			check(PlayerController.IsValid());
			if(IUsableActor::Execute_OnCanUse(UsableItemUnderCursor.Get(), PlayerController.Get()))
			{
				const FText UsableItemUnderCursorName = IUsableActor::Execute_OnGetTooltipName(UsableItemUnderCursor.Get(), PlayerController.Get());
				if(!UsableItemUnderCursorName.IsEmpty())
				{
					PlayerController->DisplayWorldTooltip(UsableItemUnderCursorName);
				}
			}
			
			IUsableActor::Execute_OnCursorEnter(UsableItemUnderCursor.Get(), PlayerController.Get());
		}

		if(IUsableActor::Execute_OnCanUse(UsableItemUnderCursor.Get(), PlayerController.Get()))
		{
			IUsableActor::Execute_OnCursorHover(UsableItemUnderCursor.Get(), PlayerController.Get());	
		}
	}
}

void AFootballPlayerController::FUsableItemUnderCursor::Use()
{
	if(IsValid(UsableItemUnderCursor.Get()) && ensureAlways(UsableItemUnderCursor->Implements<UUsableActor>()))
	{
		check(PlayerController.IsValid());

		if(IUsableActor::Execute_OnCanUse(UsableItemUnderCursor.Get(), PlayerController.Get()))
		{
			IUsableActor::Execute_OnUsed(UsableItemUnderCursor.Get(), PlayerController.Get());
			Reset();
		}
	}
}

void AFootballPlayerController::FUsableItemUnderCursor::Reset()
{
	if(IsValid(UsableItemUnderCursor.Get()) && ensureAlways(UsableItemUnderCursor->Implements<UUsableActor>()))
	{
		check(PlayerController.IsValid());

		PlayerController->HideWorldTooltip();
		IUsableActor::Execute_OnCursorRelease(UsableItemUnderCursor.Get(), PlayerController.Get());	
	}
	UsableItemUnderCursor = nullptr;
}
//~=====================================================================================================================
