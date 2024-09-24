// Copyright, 2023, by NGD Studios AB. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PostMatchSplashScreenMVP.generated.h"

class UFootballerObject;
class UVerticalBox;
struct FFootballerData;

/**
 * 
 */
UCLASS()
class FOOTBALL_API UPostMatchSplashScreenMVP : public UUserWidget
{
	GENERATED_BODY()

public:
	void UpdateMVP(const FFootballerData& Footballer, const int32 Goals, const int32 Shoots, const int32 Performance);

protected:


	UFUNCTION(BlueprintImplementableEvent, DisplayName="OnUpdateMVP")
	void K2_OnUpdateMVP(const FString& Name, const FString& Surname, const EFieldPosition Position, 
		const int32 Number, const float OverrallRating, const float Stars,
		const ERatingLevel Level, const int32 Goals, const int32 Shoots, const int32 Performance);
	
};
