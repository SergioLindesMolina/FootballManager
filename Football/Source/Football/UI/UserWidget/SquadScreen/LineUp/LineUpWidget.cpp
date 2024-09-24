// Copyright, 2023, by NGD Studios AB. All rights reserved.


#include "LineUpWidget.h"
#include "FieldWidget.h"

#include <Football/Formation/GridGenerator/GridGenerator.h>
#include <Football/Team/TeamGenerator.h>
#include <Football/UI/UserWidget/Shared/ChipFootballer/ChipFootballerWidget.h>

#include "Football/Match/MatchDefs.h"

#include <Football/Formation/FootballerChip.h>
#include <Football/Formation/FieldZone.h>

#include <Components/Image.h>

#ifdef WITH_IMGUI
void ULineUpWidget::DrawImGuiScreen()
{
	if(!StarterChips[0]) return;
		
	for (int32 i=0; i < StarterChips.Num(); ++i)
	{
		AFootballerChip* Chip = StarterChips[i];
		if(!ensureAlways(Chip)) continue;
		
		UChipFootballerWidget* ChipWidget = Chip->GetFootballerWidget();
		FFootballerData* Data = &ChipWidget->Footballer->Data;
		ImGui::PushID(i);
		FString TreeName = FString::Printf(TEXT("%d - %s %s (%s)"), Data->Number, *Data->DisplayName.FirstName.ToString(), *Data->DisplayName.LastName.ToString(), *Data->DisplayName.GetDisplayName().ToString());
		if (ImGui::TreeNode(TCHAR_TO_UTF8(*TreeName)))
		{
			// Penalty Cards
			{
				ImGui::Text("Cards: "); 
				ImGui::PushItemWidth(100);
				ImGui::InputInt("Yellow", &Data->State.PenaltyCards[0]);
				ImGui::SameLine(); ImGui::InputInt("Red", &Data->State.PenaltyCards[1]);
				ImGui::PopItemWidth();	
			}
			
			// Captain
			{
				bool bIsCaptain = Data->CharacterType == ECharacterType::CaptainCharacter;
				ImGui::Checkbox("Captain?", &bIsCaptain);
				if (bIsCaptain)
				{
					Data->CharacterType = ECharacterType::CaptainCharacter;
				}
				else
				{
					Data->CharacterType = ECharacterType::RegularCharacter;
				}	
			}

			// State
			{
				ImGui::SliderFloat("Condition", &Data->State.Condition, 0, 100);
				ImGui::SliderFloat("Moral", &Data->State.Morale, 0, 100);
				ImGui::SliderFloat("Sharpness", &Data->State.Sharpness, 0, 100);

				const char* InjuriesItems[] = { "None", "Light Injury", "Severe Injury" };
				ImGui::ListBox("Injuries", &Data->State.Injured, InjuriesItems, IM_ARRAYSIZE(InjuriesItems));
				if (Data->State.Injured)
				{
					int32 RecDays = 0;
					if (Data->State.InjuredEndDate.GetTicks() > 0)
					{
						FDateTime N = FDateTime::Now();
						FTimespan Span = Data->State.InjuredEndDate - N;
						RecDays = Span.GetTotalDays() + 1; //Hack to round days
					}
					if (ImGui::InputInt("Recovery days", &RecDays))
					{
						if (RecDays >= 0)
						{
							FDateTime N = FDateTime::Now();
							FTimespan DSpan = FTimespan::FromDays(RecDays);
							Data->State.InjuredEndDate = N + DSpan;
						}
					}
				}
			}
			
			// Selected Name
			{
				const char* SelectedNameItems[] = { "First Name", "Last Name" };
				ImGui::ListBox("Selected Name", reinterpret_cast<int32*>(&Data->DisplayName.SelectedDisplayName), SelectedNameItems, IM_ARRAYSIZE(SelectedNameItems));
			}
			
			// All Properties
			{
				ImGui::BeginChild("AllPropertiesChild", ImVec2(0, 150), true);
				TArray AllProperties = ChipWidget->Footballer->GetAllProperties();
				for (int j = 0; j < AllProperties.Num(); j++)
				{
					ImGui::Text(TCHAR_TO_UTF8(*AllProperties[j]), j);
				}
				ImGui::EndChild();
			}

			ChipWidget->RefreshData();
			ChipWidget->UpdateState();

			ImGui::TreePop();
		}
		ImGui::PopID();
	}
}
#endif

void ULineUpWidget::NativeConstruct()
{
	Super::NativeConstruct();
	IMPLEMENT_IMGUI_SCREEN(DrawImGuiScreen(););
}

void ULineUpWidget::RefreshAllFootballers()
{
	UE_LOG(LogFootball, Log, TEXT("ULineUpWidget::RefreshAllFootballers()"));
	for(int32 i = 0; i < StarterChips.Num(); ++i)
	{
		AFootballerChip* Chip = StarterChips[i];
		UChipFootballerWidget* ChipWidget = Chip->GetFootballerWidget();

		ChipWidget->RefreshData();
		ChipWidget->UpdateState();
	}
}

void ULineUpWidget::SetCurrentTeam(UTeam_Deprecated* InTeam, const FTeamTacticsData& TeamTacticsData, TArray<AFieldZone*> FieldZones, bool LoadDefault)
{
	check(IsValid(GridGenerator));

	GridGenerator->InitGrid();

	TArray<uint8> PositionsQuantityData = this->GetFormationData(TeamTacticsData);

	InitializeStarterChips(InTeam);

	TArray<AFootballerChip*> ChipsToAdd = StarterChips;

	for (AFieldZone* Zone : FieldZones)
	{
		Zone->SetGridGenerator(GridGenerator);
		Zone->RemoveAllChips();
	}

	if (LoadDefault)
	{
		for (AFieldZone* Zone : FieldZones)
		{
			for (AFootballerChip* Chip : ChipsToAdd)
			{
				if (Chip->GetFootballerWidget()->Footballer->Data.LineUpPosition == EFootballerLineUp::Starter)
				{
					if (Chip->GetFootballerWidget()->Footballer->Data.SelectedFieldPosition == Zone->FootballerPosition)
					{
						Zone->AddChip(Chip, InTeam);
						Chip->CurrentFieldZone = Zone;
						Zone->SortChips();
					}
				}
			}
		}
	}
	else
	{
		int32 ChipIndex = 0;
		bool ChipAdded = false;
		AFootballerChip* Chip = nullptr;
		TArray<EFieldPosition> DesiredPositions;

		// Set chips with best position
		for (AFieldZone* Zone : FieldZones)
		{
			uint8 PositionIndex = static_cast<uint8>(Zone->FootballerPosition);
			uint8 PositionsPerZone = PositionsQuantityData[PositionIndex];

			for (uint8 i = 0; i < PositionsPerZone; i++)
			{
				ChipIndex = 0;
				ChipAdded = false;
				Chip = nullptr;

				while (!ChipAdded && ChipIndex < ChipsToAdd.Num())
				{
					Chip = ChipsToAdd[ChipIndex];
					DesiredPositions = Chip->GetFootballerWidget()->Footballer->Data.DesiredFieldPositions;
					if (DesiredPositions[0] == Zone->FootballerPosition)
					{
						Zone->AddChip(Chip, InTeam);
						Chip->CurrentFieldZone = Zone;
						Zone->SortChips();
						ChipsToAdd.Remove(Chip);
						PositionsQuantityData[PositionIndex] = PositionsQuantityData[PositionIndex] - 1;
						ChipAdded = true;
					}
					ChipIndex++;
				}
			}
		}

		// Set Chips with other desired position
		for (AFieldZone* Zone : FieldZones)
		{
			uint8 PositionIndex = static_cast<uint8>(Zone->FootballerPosition);
			uint8 PositionsPerZone = PositionsQuantityData[PositionIndex];

			for (uint8 i = 0; i < PositionsPerZone; i++)
			{
				ChipIndex = 0;
				ChipAdded = false;
				Chip = nullptr;

				while (!ChipAdded && ChipIndex < ChipsToAdd.Num())
				{
					Chip = ChipsToAdd[ChipIndex];
					DesiredPositions = Chip->GetFootballerWidget()->Footballer->Data.DesiredFieldPositions;
					if (DesiredPositions.Contains(Zone->FootballerPosition))
					{
						Zone->AddChip(Chip, InTeam);
						Chip->CurrentFieldZone = Zone;
						Zone->SortChips();
						ChipsToAdd.Remove(Chip);
						PositionsQuantityData[PositionIndex] = PositionsQuantityData[PositionIndex] - 1;
						ChipAdded = true;
					}
					ChipIndex++;
				}
			}
		}

		// Set with any Chip
		for (AFieldZone* Zone : FieldZones)
		{
			uint8 PositionIndex = static_cast<uint8>(Zone->FootballerPosition);
			uint8 PositionsPerZone = PositionsQuantityData[PositionIndex];

			for (uint8 i = 0; i < PositionsPerZone; i++)
			{
				ChipIndex = 0;
				ChipAdded = false;
				Chip = nullptr;

				ChipIndex = 0;
				while (!ChipAdded && ChipIndex < ChipsToAdd.Num())
				{
					Chip = ChipsToAdd[ChipIndex];
					Zone->AddChip(Chip, InTeam);
					Chip->CurrentFieldZone = Zone;
					Zone->SortChips();
					ChipsToAdd.Remove(Chip);
					PositionsQuantityData[PositionIndex] = PositionsQuantityData[PositionIndex] - 1;
					ChipAdded = true;
					ChipIndex++;
				}
			}
		}
	} 

	UTeamGeneratorFunctionLibrary::SortFootballersByFieldPositions(InTeam->Starters);
}

void ULineUpWidget::InitializeStarterChips(UTeam_Deprecated* InTeam)
{
	if (StarterChips.IsEmpty())
	{
		for (UFootballerObject* FootballerData : InTeam->Starters)
		{
			AFootballerChip* Chip = CreateChip(InTeam, FootballerData);
			StarterChips.Add(Chip);
		}
	}
	else
	{
		int32 StartersChipsIndex = 0;
		for (UFootballerObject* FootballerData : InTeam->Starters)
		{
			StarterChips[StartersChipsIndex]->GetFootballerWidget()->Footballer = FootballerData;
			StartersChipsIndex++;
		}
	}
}

AFootballerChip* ULineUpWidget::CreateChip(UTeam_Deprecated* InTeam, UFootballerObject* Footballer)
{
	FActorSpawnParameters ChipSpawnParameters;
	ChipSpawnParameters.Owner = GridGenerator;
	AFootballerChip* Chip = GetWorld()->SpawnActor<AFootballerChip>(FootballerChipSubclass, FVector::ZeroVector, FRotator::ZeroRotator, ChipSpawnParameters);
	Chip->SetChipWidget();
	UChipFootballerWidget* FootballerWidget = Chip->GetFootballerWidget();
	Chip->GetFootballerWidget()->Footballer = Footballer;
	FootballerWidget->InitializeDelegate();

	return Chip;
}


TArray<uint8> ULineUpWidget::GetFormationData(const FTeamTacticsData& TeamTacticsData)
{
	TArray<uint8> Data;

	Data.Add(-1);
	Data.Add(TeamTacticsData.GK);
	Data.Add(TeamTacticsData.DL);
	Data.Add(TeamTacticsData.DC);
	Data.Add(TeamTacticsData.DR);
	Data.Add(TeamTacticsData.DM);
	Data.Add(TeamTacticsData.ML);
	Data.Add(TeamTacticsData.MC);
	Data.Add(TeamTacticsData.MR);
	Data.Add(TeamTacticsData.AML);
	Data.Add(TeamTacticsData.AMC);
	Data.Add(TeamTacticsData.AMR);
	Data.Add(TeamTacticsData.ST);

	return Data;
}
