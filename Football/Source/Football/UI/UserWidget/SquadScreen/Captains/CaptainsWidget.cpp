// Copyright, 2023, by NGD Studios AB. All rights reserved.


#include "CaptainsWidget.h"
#include "Football/Team/TeamGenerator.h"
#include "Football/CoreClasses/DataStructures/Footballer.h"
#include "Football/Private/Common/Logging.h"
#include "Football/UI/UserWidget/SquadScreen/Captains/CaptainsPanelWidget.h"

void UCaptainsWidget::NativeConstruct()
{
	check(Team);

	MainCaptainPanel->OnAddClicked.AddDynamic(this, &UCaptainsWidget::OnPanelAddClicked);
	CaptainPanel_1->OnAddClicked.AddDynamic(this, &UCaptainsWidget::OnPanelAddClicked);
	CaptainPanel_2->OnAddClicked.AddDynamic(this, &UCaptainsWidget::OnPanelAddClicked);
	CaptainPanel_3->OnAddClicked.AddDynamic(this, &UCaptainsWidget::OnPanelAddClicked);
	CaptainPanel_4->OnAddClicked.AddDynamic(this, &UCaptainsWidget::OnPanelAddClicked);
	
	MainCaptainPanel->OnCaptainButtonPressed.AddDynamic(this, &UCaptainsWidget::OnCaptainButtonClicked);
	CaptainPanel_1->OnCaptainButtonPressed.AddDynamic(this, &UCaptainsWidget::OnCaptainButtonClicked);
	CaptainPanel_2->OnCaptainButtonPressed.AddDynamic(this, &UCaptainsWidget::OnCaptainButtonClicked);
	CaptainPanel_3->OnCaptainButtonPressed.AddDynamic(this, &UCaptainsWidget::OnCaptainButtonClicked);
	CaptainPanel_4->OnCaptainButtonPressed.AddDynamic(this, &UCaptainsWidget::OnCaptainButtonClicked);

	TArray<UFootballerObject*> TeamFootballers;

	TeamFootballers.Append(Team->Starters);
	TeamFootballers.Append(Team->Substitutes);
	TeamFootballers.Append(Team->Reserves);
	
	for (UFootballerObject* Footballer : TeamFootballers)
	{
		if (Footballer->Data.CharacterType == ECharacterType::CaptainCharacter)
		{
			MainCaptainPanel->K2_UpdateFootballer(Footballer);
		}
		else if(Footballer->Data.CharacterType == ECharacterType::ViceCaptainCharacter)
		{
			int32 ViceCaptainPriority = Footballer->Data.CharacterTypePriority;

			switch (ViceCaptainPriority)
			{
			case 0:
				CaptainPanel_1->K2_UpdateFootballer(Footballer);
				break;
			case 1:
				CaptainPanel_2->K2_UpdateFootballer(Footballer);
				break;
			case 2:
				CaptainPanel_3->K2_UpdateFootballer(Footballer);
				break;
			case 3:
				CaptainPanel_4->K2_UpdateFootballer(Footballer);
				break;
			default:
				UE_LOG(LogFootball, Error, TEXT("INVALID VICE-CAPTAIN PRIORITY"));
				break;
			}
		}
	}
	
}


void UCaptainsWidget::OnPanelAddClicked(UCaptainsPanelWidget* Panel)
{
	check(Panel);

	K2_OnAddCaptainClicked(Panel);
}

void UCaptainsWidget::OnCaptainButtonClicked(UCaptainsPanelWidget* Panel)
{
	check(Panel);
	check(Team);


	K2_OnCaptainButtonClicked(Panel);

}

void UCaptainsWidget::K2_MakeItMainCaptain(UCaptainsPanelWidget* Panel)
{
	check(Panel);
	check(MainCaptainPanel);

	UFootballerObject* NewMainCaptain = Panel->GetFootballer();

	if (MainCaptainPanel->bSelected)
	{
		UFootballerObject* OldMainCaptain = MainCaptainPanel->GetFootballer();
		MainCaptainPanel->K2_UpdateFootballer(NewMainCaptain);
		Panel->K2_UpdateFootballer(OldMainCaptain);
	}
	else
	{
		Panel->DemoteFootballer();
		MainCaptainPanel->K2_UpdateFootballer(NewMainCaptain);
	}


}
