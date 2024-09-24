// Copyright, 2023, by NGD Studios AB. All rights reserved.

#pragma once

#include <Engine/DataTable.h>

#include "ISO316612.generated.h"

/**
 * @todo(jcastro)
 * It's highly likely that this data should have its own slate.
 * There's also a high probability that we'll use this in more locations. 
 * For now, it's defined here temporarily.
 */
USTRUCT(BlueprintType)
struct FISO316612 : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	FString ISO {};

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	FText DisplayName {};

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	UTexture2D* FlagTexture {};
};
