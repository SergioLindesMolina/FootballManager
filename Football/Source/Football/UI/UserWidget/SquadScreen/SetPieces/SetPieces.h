// Copyright, 2023, by NGD Studios AB. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SetPieces.generated.h"

UENUM(BlueprintType)
enum class ESetPieceType : uint8
{
	None,
	FreeKickRight,
	FreeKickLeft,
	LongFreeKickRight,
	LongFreeKickLeft,
	CornerRight,
	CornerLeft,
	Penalty	
};


DECLARE_DYNAMIC_MULTICAST_DELEGATE(FUpdateUI);

UCLASS(Blueprintable, BlueprintType)
class FOOTBALL_API USetPieceData : public UObject
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadWrite, meta=(ExposeOnSpawn))
	class UFootballerObject* Footballer;

	UPROPERTY(BlueprintReadWrite, meta = (ExposeOnSpawn))
	ESetPieceType Type =  ESetPieceType::None;

	UPROPERTY(BlueprintReadWrite)
	int32 Priority = 0;
	
	UPROPERTY(BlueprintReadWrite)
	bool bSelected = false;

	UPROPERTY(BlueprintReadWrite)
	bool bHovered = false;

	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FUpdateUI OnUpdateUI;
};


/**
 * 
 */
UCLASS()
class FOOTBALL_API USetPieces : public UUserWidget
{
	GENERATED_BODY()
	
protected:

	UPROPERTY(BlueprintReadWrite)
	TArray<USetPieceData*> SetPiecesData;


};