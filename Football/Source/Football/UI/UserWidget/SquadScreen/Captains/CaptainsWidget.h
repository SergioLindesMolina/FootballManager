// Copyright, 2023, by NGD Studios AB. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CaptainsWidget.generated.h"


class UCaptainsPanelWidget;
class UTeam_Deprecated;

/**
 * 
 */
UCLASS()
class FOOTBALL_API UCaptainsWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	void NativeConstruct() override;

	UFUNCTION()
	void OnPanelAddClicked(UCaptainsPanelWidget* Panel);

	UFUNCTION()
	void OnCaptainButtonClicked(UCaptainsPanelWidget* Panel);

	UPROPERTY(BlueprintReadWrite, meta=(BindWidget))
	UCaptainsPanelWidget* MainCaptainPanel;
	UPROPERTY(BlueprintReadWrite, meta=(BindWidget))
	UCaptainsPanelWidget* CaptainPanel_1;
	UPROPERTY(BlueprintReadWrite, meta=(BindWidget))
	UCaptainsPanelWidget* CaptainPanel_2;
	UPROPERTY(BlueprintReadWrite, meta=(BindWidget))
	UCaptainsPanelWidget* CaptainPanel_3;
	UPROPERTY(BlueprintReadWrite, meta=(BindWidget))
	UCaptainsPanelWidget* CaptainPanel_4;

	UPROPERTY(BlueprintReadWrite, meta=(ExposeOnSpawn = true))
	UTeam_Deprecated* Team;


protected:


    UFUNCTION(BlueprintImplementableEvent, DisplayName="OnAddCaptainClicked")
	void K2_OnAddCaptainClicked(UCaptainsPanelWidget* Panel);

	UFUNCTION(BlueprintImplementableEvent, DisplayName="OnCaptainButtonClicked")
	void K2_OnCaptainButtonClicked(UCaptainsPanelWidget* Panel);
	
	UFUNCTION(BlueprintCallable, DisplayName="MakeItMainCaptian")
	void K2_MakeItMainCaptain(UCaptainsPanelWidget* Panel);
	
};
