// Copyright, 2023, by NGD Studios AB. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Engine/DataTable.h"
#include "Football/Match/MatchDefs.h"
#include "Highlight.generated.h"



USTRUCT(BlueprintType)
struct FHighlight
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FString> Footballers;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<EHighlightEvent> Events;

};

USTRUCT(BlueprintType)
struct FHightlightEventData : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	EHighlightEvent Event {};
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	UTexture2D* Icon {};
};

USTRUCT(BlueprintType)
struct FHighlightsData : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	FString Time;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TArray<FHighlight> LocalTeamHighlights;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TArray<FHighlight> VisitorTeamHighlights;
};