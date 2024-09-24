// Copyright, 2023, by NGD Studios AB. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Football/CoreClasses/DataStructures/Footballer.h"
#include "CaptainsPanelWidget.generated.h"


class UFootballerObject;
enum class ECharacterType : uint8;


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAddClicked, UCaptainsPanelWidget*, Panel);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnCaptainButtonPressed, UCaptainsPanelWidget*, Panel);


/**
 * 
 */
UCLASS()
class FOOTBALL_API UCaptainsPanelWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:


	UFUNCTION(BlueprintCallable)
	void UpdateFootballerType(const ECharacterType& InCharacterType, const int32 InPriority);

	UFUNCTION(BlueprintCallable)
	void DemoteFootballer();

	UFUNCTION(BlueprintCallable, DisplayName="UpdateFootballer")
	void K2_UpdateFootballer(UFootballerObject* InFootballer);

	UFUNCTION(BlueprintImplementableEvent, DisplayName = "OnUpdateFootballerInfo")
	void K2_OnUpdateFootballerInfo(const int32 Number, const FText& Name, const TArray<EFieldPosition>& Positions);

	UFUNCTION(BlueprintImplementableEvent, DisplayName = "OnUpdateFootballerRating")
	void K2_OnUpdateFootballerRating(const float Overrall, const float Stars, const ERatingLevel& Level);

	UFUNCTION(BlueprintImplementableEvent, DisplayName = "OnUpdateAffinity")
	void K2_OnUpdateAffinity(const int32 Affinity);

	UFUNCTION(BlueprintImplementableEvent, DisplayName = "OnUpdateSpecialTrait")
	void K2_OnUpdateSpecialTrait(const ESpecialTrait& SpecialTrait, const int32 Level, const float TraitPoints);

	UFUNCTION(BlueprintImplementableEvent, DisplayName="OnUpdateCaptainStatus")
	void K2_OnUpdateCaptianStatus(const bool bIsCaptain);

	UFUNCTION(BlueprintImplementableEvent, DisplayName="OnFootballerSelected")
	void K2_OnFootballerSelected();

	UFUNCTION(BlueprintImplementableEvent, DisplayName="OnFootballerDemoted")
	void K2_OnFootballerDemoted();

	UFUNCTION(BlueprintCallable, BlueprintPure, DisplayName="GetFooballerID")
	int32 K2_GetFootballerID() const;

	UFUNCTION(BlueprintCallable, BlueprintPure, DisplayName="GetFootballer")
	UFootballerObject* GetFootballer() const;

	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FOnAddClicked OnAddClicked;

	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FOnCaptainButtonPressed OnCaptainButtonPressed;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	bool bSelected = false;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Appearance")
	ECharacterType PanelCharacterType;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Appearance")
	int32 PanelCharacterPriority = 0;

private:

	TObjectPtr<UFootballerObject> Footballer;

};
