// Copyright, 2023, by NGD Studios AB. All rights reserved.


#include "FootballerCharacter.h"

#include <Blueprint/WidgetLayoutLibrary.h>
#include <Components/CapsuleComponent.h>

#include <UserInterfaceBFL.h>
#include <DialogueSystem/Public/Components/DialogueAvatarComponent.h>
#include <Football/UI/UserWidget/Shared/FootballerOverview/FootballerOverview.h>

AFootballerCharacter::AFootballerCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	DialogueAvatarComponent = CreateDefaultSubobject<UDialogueAvatarComponent>("DialogueAvatarComponent");
	DialogueAvatarComponent->SetupAttachment(GetMesh(), "headSocket");
	DialogueAvatarComponent->bAutoActivate = false;

	GetCapsuleComponent()->SetCapsuleHalfHeight(94);
	GetCapsuleComponent()->SetCollisionResponseToChannel(IUsableActor::GameTraceChannel, ECR_Block);

	//const ConstructorHelpers::FObjectFinder<USkeletalMesh> FTBModel(TEXT("/Script/Engine.SkeletalMesh'/Game/Football/Art/Characters/FTPModel/SK_FTBModel.SK_FTBModel'"));
	const ConstructorHelpers::FObjectFinder<USkeletalMesh> FTBModel(TEXT("/Script/Engine.SkeletalMesh'/Game/Football/Art/Characters/CityRangers/Meshes/SK_Footballer.SK_Footballer'"));
	if(FTBModel.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(FTBModel.Object);
    	GetMesh()->SetRelativeLocation(FVector(0, 0,-90));
    	GetMesh()->SetRelativeRotation(FRotator(0, -90, 0));	
	}
}

bool AFootballerCharacter::OnCanUse_Implementation(APlayerController* PlayerController) const
{
	return true;
}

void AFootballerCharacter::OnUsed_Implementation(APlayerController* PlayerController)
{
}

void AFootballerCharacter::OnCursorEnter_Implementation(APlayerController* PlayerController)
{
	const auto Content = LoadClass<UFootballerOverview>(this, TEXT("/Game/Football/UI/Widgets/FootballerOverview/WBP_FootballerOverview.WBP_FootballerOverview_C"));

	const FString FormattedNumber = FString::Printf(TEXT("%02d"), FootballerEntity.Number);
	const FText DisplayName = FText::Format(INVTEXT("{0}. {1}"), FText::FromString(FormattedNumber), FootballerEntity.DisplayName.GetDisplayName());

	UFootballerOverview* Widget = Cast<UFootballerOverview>(CreateWidget(PlayerController, Content));
	UUserInterfaceBFL::SpawnBubblePanel(this, UWidgetLayoutLibrary::GetMousePositionOnViewport(this), Widget);

	Widget->K2_OnUpdateStats(DisplayName, FootballerEntity.SelectedFieldPosition, FootballerEntity.Rating.Level, FootballerEntity.Rating.Stars, FootballerEntity.Rating.Overall);
}

void AFootballerCharacter::OnCursorRelease_Implementation(APlayerController* PlayerController)
{
	UUserInterfaceBFL::DestroyBubblePanel(this);
}

void AFootballerCharacter::UpdateFootballerEntity(const FFootballerData& InFootballerEntity)
{
	FootballerEntity = InFootballerEntity;
}
