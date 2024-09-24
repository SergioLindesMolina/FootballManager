// Copyright, 2023, by NGD Studios AB. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "BaseChip.h"
#include "EmptyChip.generated.h"

class UEmptyChipWidget;
enum class EFieldPosition : uint8;

/**
 * Chip with empty info
 */

UCLASS()
class FOOTBALL_API AEmptyChip : public ABaseChip
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

public:

	virtual void SetChipWidget() override;

	void ToggleChipVisibility(AActor* OverlapedActor);

private:

	UPROPERTY()
	UEmptyChipWidget* EmptyChipWidget;

};
