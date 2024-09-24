// Copyright, 2023, by NGD Studios AB. All rights reserved.

#pragma once

#include <CoreMinimal.h>
#include <GameFramework/Actor.h>

#include "BaseChip.h"
#include <Football/Formation/EmptyChip.h>

#include "FootballerChip.generated.h"

enum class EChipFormationStatus : uint8;
enum class EFootballerLineUp : uint8;
class UTeam_Deprecated;
class UChipFootballerWidget;
class UFootballerObject;
class AEmptyChip;
class AFieldZone;

UCLASS()
class FOOTBALL_API AFootballerChip : public ABaseChip
{
	GENERATED_BODY()

protected:
	void BeginPlay() override;

public:
	void SwapPositions(AActor* OverlappedActor);

	void SetChipWidget() override;

	void SetIsOnField(bool Value);

	bool IsUsed() const;

	bool IsOnField() const;

	UChipFootballerWidget* GetFootballerWidget();

	UFUNCTION(BlueprintCallable)
	const UChipFootballerWidget* GetFootballerWidget() const;

	UFUNCTION(BlueprintCallable)
	const UTeam_Deprecated* GetFootballerCurrentTeam() const;

	
public:
	UPROPERTY()
	UTeam_Deprecated* FootballerCurrentTeam {};

	UPROPERTY(EditAnywhere)
	TSubclassOf<AEmptyChip> EmptyChipSubclass;

	UPROPERTY()
	AEmptyChip* EmptyChip;

	UPROPERTY()
	AFieldZone* CurrentFieldZone;

	
private:
	UPROPERTY()
	UChipFootballerWidget* ChipFootballerWidget;

	bool bIsOnField = true;
	bool bIsUsed {};
};
