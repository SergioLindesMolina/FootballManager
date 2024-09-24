// Copyright, 2023, by NGD Studios AB. All rights reserved.

#include "FootballerProfile.h"
#include "DBSBFootballerCard.h"

#include <Blueprint/WidgetTree.h>
#include <Blueprint/GameViewportSubsystem.h>
#include <Internationalization/StringTable.h>
#include <Internationalization/StringTableCore.h>

#include <UWidget/RadarChart.h>
#include <UWidget/ListTextNumberValues.h>

#include <Football/CoreClasses/DataStructures/Footballer.h>
#include <Football/CoreClasses/FootballGameInstance.h>
#include <Football/Team/TeamGenerator.h>
#include <Football/UI/LocalizationBFL.h>
#include <Football/UI/UWidget/SoccerField/SoccerField.h>


void UFootballerProfile::SetupFootballerProfile(const UTeam_Deprecated* Team)
{
	CurrentTeam = Team;

	K2_GetSoccerField()->OnInteractablePositionClicked.AddDynamic(this, &UFootballerProfile::OnSoccerFieldPositionClicked);
	K2_GetFootballersCardScrollBox()->OnDBScrollBoxSelChanged.AddDynamic(this, &UFootballerProfile::OnFootballersCardScrollBoxSelectionChanged);
	K2_GetFootballersCardScrollBox()->FillFootballersData(GenerateFootballersDataFromTeam_Deprecated());
}

void UFootballerProfile::LoadDebug()
{
	const UFootballGameInstance* FootballGameInstance = GetGameInstance<UFootballGameInstance>();
	check(FootballGameInstance);

	SetupFootballerProfile(UTeamGeneratorFunctionLibrary::GenerateTeamWithGenerator(FootballGameInstance->GetPlayerTeamGenerator()));
	PopulateFootballerFromIndex(0);
}

UFootballerProfile* UFootballerProfile::DisplayWidget(const UObject* WorldContextObject, const UTeam_Deprecated* Team, UFootballerObject* Footballer)
{
	if(UFootballerProfile::bDisplayWidget)
	{
		UE_LOG(LogFootball, Warning, TEXT("Attempt to re-call DisplayWidget before close it."));
		return nullptr;
	}
	
	check(Footballer && Team);
	UFootballerProfile* FootballerProfile = {};

	if (UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull))
	{
		const TSubclassOf<UUserWidget> FootballerProfileContainerClass = LoadClass<UUserWidget>(World, TEXT("/Game/Football/UI/Widgets/FootballerProfile/WBP_FootballerProfileContainer.WBP_FootballerProfileContainer_C"));
		check(FootballerProfileContainerClass);
		
		UUserWidget* FootballerProfileContainer = ::CreateWidget<UUserWidget>(World, FootballerProfileContainerClass);
		
		FootballerProfileContainer->WidgetTree->ForEachWidget([&](UWidget* Widget)
		{
			(void)Widget->TakeWidget(); //< Force to load all SWidget in WidgetTree
			if(Widget->IsA(UFootballerProfile::StaticClass()))
			{
				FootballerProfile = CastChecked<UFootballerProfile>(Widget);
				UGameViewportSubsystem::Get(World)->OnWidgetRemoved.AddUFunction(FootballerProfile, "OnWidgetClosed");

				FootballerProfile->SetupFootballerProfile(Team);
				auto Array = FootballerProfile->GenerateFootballersDataFromTeam_Deprecated();
				for(int32 i = 0; i < Array.Num(); i++)
				{
					if(*Array[i] == Footballer->Data)
					{
						FootballerProfile->PopulateFootballerFromIndex(i);
						break;
					}
				}
			}
		});

		FootballerProfileContainer->AddToViewport();
		UFootballerProfile::bDisplayWidget = true;
	}	

	return FootballerProfile;
}

void UFootballerProfile::OnWidgetClosed(const UWidget* Widget) const
{
	if(const UUserWidget* UserWidget = Cast<UUserWidget>(Widget))
	{
		UserWidget->WidgetTree->ForEachWidget([&](const UWidget* WidgetChild)
		{
			if(WidgetChild == this)
			{
				UGameViewportSubsystem::Get(GetWorld())->OnWidgetRemoved.RemoveAll(this);
				UFootballerProfile::bDisplayWidget = false;
				
				OnFootballerProfileClosed.Broadcast();
				return;
			}
		});
	}
}

void UFootballerProfile::OnSoccerFieldPositionClicked(const EFieldPosition FieldPosition, bool /*bSelected*/)
{
	// @see https://docs.google.com/presentation/d/1W2_Rrqw7Gt_pDTYOdHQKs05LR16Fx6CDw5daqRxS7xI/edit#slide=id.g285d625f6e8_1_0
	static TMap<EFieldPosition, TArray<EFootballerAttributes>> FieldPosition_Attributes_Relations =
	{
		{ EFieldPosition::GK,  { EFootballerAttributes::Agility,      EFootballerAttributes::Reach,        EFootballerAttributes::AerialPlay,   EFootballerAttributes::Reflexes,     EFootballerAttributes::OneOnOnes,    EFootballerAttributes::Anticipation } },
		{ EFieldPosition::DL,  { EFootballerAttributes::Marking,      EFootballerAttributes::Speed,        EFootballerAttributes::Positioning,  EFootballerAttributes::Tackling,     EFootballerAttributes::Strength,     EFootballerAttributes::LongPassing  } },
		{ EFieldPosition::DR,  { EFootballerAttributes::Marking,      EFootballerAttributes::Speed,        EFootballerAttributes::Positioning,  EFootballerAttributes::Tackling,     EFootballerAttributes::Strength,     EFootballerAttributes::LongPassing  } },
		{ EFieldPosition::DC,  { EFootballerAttributes::Marking,      EFootballerAttributes::Tackling,     EFootballerAttributes::Aggression,   EFootballerAttributes::Strength,     EFootballerAttributes::JumpReach,    EFootballerAttributes::Positioning  } },
		{ EFieldPosition::DM,  { EFootballerAttributes::Positioning,  EFootballerAttributes::Marking,      EFootballerAttributes::ShortPassing, EFootballerAttributes::Tackling,     EFootballerAttributes::Strength,     EFootballerAttributes::Control	  } },
		{ EFieldPosition::ML,  { EFootballerAttributes::Control,      EFootballerAttributes::LongPassing,  EFootballerAttributes::Speed,        EFootballerAttributes::ShortPassing, EFootballerAttributes::Dribbling,    EFootballerAttributes::Shooting	  } },
		{ EFieldPosition::MR,  { EFootballerAttributes::Control,      EFootballerAttributes::LongPassing,  EFootballerAttributes::Speed,        EFootballerAttributes::ShortPassing, EFootballerAttributes::Dribbling,    EFootballerAttributes::Shooting	  } },
		{ EFieldPosition::MC,  { EFootballerAttributes::Creativity,   EFootballerAttributes::ShortPassing, EFootballerAttributes::Control,      EFootballerAttributes::Positioning,  EFootballerAttributes::LongPassing,  EFootballerAttributes::Dribbling	  } },
		{ EFieldPosition::AML, { EFootballerAttributes::Dribbling,    EFootballerAttributes::Creativity,   EFootballerAttributes::LongPassing,  EFootballerAttributes::Speed,        EFootballerAttributes::Shooting,     EFootballerAttributes::Finishing	  } },
		{ EFieldPosition::AMR, { EFootballerAttributes::Dribbling,    EFootballerAttributes::Creativity,   EFootballerAttributes::LongPassing,  EFootballerAttributes::Speed,        EFootballerAttributes::Shooting,     EFootballerAttributes::Finishing	  } },
		{ EFieldPosition::AMC, { EFootballerAttributes::ShortPassing, EFootballerAttributes::Creativity,   EFootballerAttributes::Positioning,  EFootballerAttributes::Shooting,     EFootballerAttributes::Dribbling,	  EFootballerAttributes::Control	  } },
		{ EFieldPosition::ST,  { EFootballerAttributes::Finishing,    EFootballerAttributes::Shooting,     EFootballerAttributes::Speed,        EFootballerAttributes::Positioning,  EFootballerAttributes::Dribbling,    EFootballerAttributes::Strength	  } }
	};

	auto HighlightAttributes = [&](UListTextNumberValues* Panel, const TArray<EFootballerAttributes>& FootballerAttributes, EFootballerAttributes From, EFootballerAttributes To)
	{
		TArray<int32> Indices;
		const int32 StartIndex = static_cast<int32>(From);
		const int32 EndIndex   = static_cast<int32>(To);

		for (int32 i = 0; i < FootballerAttributes.Num(); i++)
		{
			const int32 AttIndex = static_cast<int32>(FootballerAttributes[i]);
			if (AttIndex >= StartIndex && AttIndex <= EndIndex)
			{
				int32 MappedIndex = AttIndex - StartIndex;
				Indices.Add(MappedIndex);
			}
		}

		Panel->HighlightChildren(Indices);
	};

	
	check(FieldPosition_Attributes_Relations.Contains(FieldPosition));

	// Only in the case where the footballer is a GK (Goalkeeper) do we display a list of differing attributes in
	// the 'Technical' category.
	//
	// Since only a single GK-positioned footballer can exist at a time, this calculation can be made here rather
	// than recalculating it every time the position changes.
	//
	// @see https://nimblegiant.slack.com/archives/C054VQXQJP4/p1698764862078819?thread_ts=1698690384.629139&cid=C054VQXQJP4
	if(CurrentFootballerData->DesiredFieldPositions.Contains(EFieldPosition::GK))
	{
		HighlightAttributes(K2_GetListTextNumberValues_Technical(), FieldPosition_Attributes_Relations[FieldPosition], EFootballerAttributes::Reflexes,   EFootballerAttributes::OneOnOnes);
	}
	else
	{
		HighlightAttributes(K2_GetListTextNumberValues_Technical(), FieldPosition_Attributes_Relations[FieldPosition], EFootballerAttributes::Tackling,   EFootballerAttributes::Control);
	}

	HighlightAttributes(K2_GetListTextNumberValues_Physical(),  FieldPosition_Attributes_Relations[FieldPosition], EFootballerAttributes::Speed,      EFootballerAttributes::JumpReach);
	HighlightAttributes(K2_GetListTextNumberValues_Mental(),    FieldPosition_Attributes_Relations[FieldPosition], EFootballerAttributes::Creativity, EFootballerAttributes::Aggression);
	
	// Update ChartWidget
	FRadarChartValue_Blueprint Value;
	Value.TextValue =
	{
		ULocalizationBFL::LoadLocalizedAttribute(FieldPosition_Attributes_Relations[FieldPosition][0]),
		ULocalizationBFL::LoadLocalizedAttribute(FieldPosition_Attributes_Relations[FieldPosition][1]), 
		ULocalizationBFL::LoadLocalizedAttribute(FieldPosition_Attributes_Relations[FieldPosition][2]), 
		ULocalizationBFL::LoadLocalizedAttribute(FieldPosition_Attributes_Relations[FieldPosition][3]),
		ULocalizationBFL::LoadLocalizedAttribute(FieldPosition_Attributes_Relations[FieldPosition][4]),
		ULocalizationBFL::LoadLocalizedAttribute(FieldPosition_Attributes_Relations[FieldPosition][5])
	};

	Value.Values =
	{
		CurrentFootballerData->Attributes.NormalizeAttribute(static_cast<int32>(FieldPosition_Attributes_Relations[FieldPosition][0])),
		CurrentFootballerData->Attributes.NormalizeAttribute(static_cast<int32>(FieldPosition_Attributes_Relations[FieldPosition][1])),
		CurrentFootballerData->Attributes.NormalizeAttribute(static_cast<int32>(FieldPosition_Attributes_Relations[FieldPosition][2])),
		CurrentFootballerData->Attributes.NormalizeAttribute(static_cast<int32>(FieldPosition_Attributes_Relations[FieldPosition][3])),
		CurrentFootballerData->Attributes.NormalizeAttribute(static_cast<int32>(FieldPosition_Attributes_Relations[FieldPosition][4])),
		CurrentFootballerData->Attributes.NormalizeAttribute(static_cast<int32>(FieldPosition_Attributes_Relations[FieldPosition][5]))
	};

	Value.BorderColor     = FColor::FromHex("2DCF95");
	Value.Thickness       = 3;
	Value.bDrawBackground = false;
	Value.bDrawBorder     = true;

	const auto FieldRating = CurrentFootballerData->CalculateFootballerRating(FieldPosition);
	K2_OnUpdateRadarChart({Value}, FieldPosition, FieldRating.Level, FieldRating.MapOverallToStars());

	K2_GetSoccerField()->ChangeAllInteractablePositionsStatus(false);
	K2_GetSoccerField()->ChangeInteractablePositionsStatus(FieldPosition, true);
}

void UFootballerProfile::OnFootballersCardScrollBoxSelectionChanged(const int32 Index, UDualButtonScroll* /*DualButtonScroll*/)
{
	PopulateFootballerFromIndex(Index);
}

void UFootballerProfile::GetEditablePanelInfo_FootballerName(FText& OutName, FText& OutLastName, bool& OutLastNameHighlight) const
{
	OutName     = CurrentFootballerData->DisplayName.FirstName;
	OutLastName = CurrentFootballerData->DisplayName.LastName;
	OutLastNameHighlight = CurrentFootballerData->DisplayName.SelectedDisplayName == FFootballerData::FFootballerName::EDisplayName::LastName;
}

void UFootballerProfile::GetEditablePanelInfo_FootballerNumber(int32& OutNumber, TArray<int32>& OutReservedNumbers) const
{
	OutNumber = CurrentFootballerData->Number;

	TArray<int32> ReservedNumbers;
	ReservedNumbers.Reserve(CurrentTeam->TeamSelectedNumbers.Num());
	for(const int8 Number : CurrentTeam->TeamSelectedNumbers)
	{
		if(Number == OutNumber) continue;
		ReservedNumbers.Add(Number);
	}
	
	OutReservedNumbers = ReservedNumbers;
}

FISO316612 UFootballerProfile::GetEditablePanelInfo_FootballerNationality() const
{
	return *CurrentFootballerData->Nationality.LoadISO();
}

void UFootballerProfile::PopulateFootballerFromIndex(const int32 FootballersCardScrollBoxIndex)
{
	const auto Array = GenerateFootballersDataFromTeam_Deprecated();
	check(FootballersCardScrollBoxIndex < Array.Num());
	check(Array[FootballersCardScrollBoxIndex]);
	
	PopulateFootballerFromData(*Array[FootballersCardScrollBoxIndex], FText::FromString(CurrentTeam->Name));

	const UDBSBFootballerCard* FootballersCardScrollBox = K2_GetFootballersCardScrollBox();
	check(FootballersCardScrollBox);
	FootballersCardScrollBox->HighlightChild(FootballersCardScrollBoxIndex);
}

void UFootballerProfile::PopulateFootballerFromData(FFootballerData& Data, const FText& TeamName)
{
	CurrentFootballerData =	&Data;

	//~=================================================================================================================
	// HEADER
	//~=================================================================================================================
	{
		K2_OnFootballerName(Data.DisplayName.FirstName, Data.DisplayName.LastName, Data.DisplayName.SelectedDisplayName == FFootballerData::FFootballerName::EDisplayName::LastName);
		K2_OnFootballerRating(Data.Rating.Level, Data.Rating.Stars);
		K2_OnFootballerNumber(Data.Number);
		K2_OnFootballerNationality(*Data.Nationality.LoadISO());
		K2_OnFootballerAge(FMath::RoundToInt32<float>(Data.Age));
		K2_OnFootballerAgeOfRetirement(FMath::RoundToInt32<float>(Data.AgeOfRetirement));
		K2_OnFootballerPreferredPositions(Data.DesiredFieldPositions);

		K2_OnFootballerPreferredFoot(Data.PhysicalFeatures.PreferredFoot);
		K2_OnFootballerHeight(Data.PhysicalFeatures.Height);
		K2_OnFootballerWeight(Data.PhysicalFeatures.Weight);
		/** TODO: IGNORED BY UI */
		(void)Data.PhysicalFeatures.Gender;

		K2_OnFootballerRole(ULocalizationBFL::LoadLocalizedRole(Data.Role));
		K2_OnFootballerTeam(TeamName);

		K2_OnFootballerContract(Data.Contract.StartSeason.GetYear(), Data.Contract.ExpirySeason.GetYear());

		/** TODO: MISSING DATA */
		K2_OnFootballerMilestone_Left(INVTEXT("GOALS THIS SEASON"), 0);
		/** TODO: MISSING DATA */
		K2_OnFootballerMilestone_Center(INVTEXT("ASSISTS THIS SEASON"), 0);
		/** TODO: MISSING DATA */
		K2_OnFootballerMilestone_Right(INVTEXT("TOTAL INVOLVEMENT"), 0);
	}

	//~=================================================================================================================
	// GENERAL
	//~=================================================================================================================
	{
		check(Data.State.Condition >= 0 && Data.State.Condition <= 100);
		K2_OnUpdateCondition(Data.State.Condition / 100.f);
		
		check(Data.State.Morale >= 0 && Data.State.Morale <= 100);
		K2_OnUpdateMorale(Data.State.Morale / 100.f);

		// @see https://www.figma.com/file/s89fBpZYi2kpre5AdFbcUR/FOOTBALLER-PROFILE?type=design&node-id=612-169&mode=design&t=jP0h09jeSCJq4sYC-0
		static std::array SharpnessColors =
		{
			FColor::FromHex("B1140A"),
			FColor::FromHex("F13C14"),
			FColor::FromHex("FA7C20"),
			FColor::FromHex("F1BA62"),
			FColor::FromHex("B1CA6D"),
			FColor::FromHex("90E178")
		};

		check(Data.State.Sharpness >= 0 && Data.State.Sharpness <= 100);

		int32 Index = FMath::RoundToInt(Data.State.Sharpness / 100.f * (SharpnessColors.size() - 1));
		Index = FMath::Clamp(Index, 0, SharpnessColors.size() - 1);
		
		K2_OnUpdateSharpness(
			FText::AsNumber(FMath::Floor(Data.State.Sharpness)),
			SharpnessColors[Index]
		);

		check(Data.State.Injured >= 0 && Data.State.Injured <= 3);
		K2_OnUpdateInjuries(Data.State.Injured, Data.State.InjuredEndDate);
		
		K2_OnUpdateCards(Data.State.PenaltyCards[Footballer::EPenaltyCardType::Yellow], Data.State.PenaltyCards[Footballer::EPenaltyCardType::Red]);

		K2_OnUpdateRatingLevel(Data.Rating.Level);
		K2_OnUpdateOverallRating(Data.Rating.Level,   Data.Rating.MapOverallToStars());
		K2_OnUpdatePotentialRating(Data.Rating.Level, Data.Rating.MapPotentialToStars());
		K2_OnUpdateSpecialTrait(ULocalizationBFL::LoadLocalizedSpecialTrait(Data.SpecialTrait), Data.SpecialTraitLevel);
		K2_OnEnableCaptainRibbon(Data.CharacterType);

		K2_OnUpdateAffinityWithManager(Data.TeamDynamics.AffinityWithManager / 10.f, static_cast<int32>(Data.TeamDynamics.AffinityWithManager));
		K2_OnUpdateAlignmentWithTeam(Data.TeamDynamics.AlignmentWithTeam / 10.f, static_cast<int32>(Data.TeamDynamics.AlignmentWithTeam));
		K2_OnPersonalityType(Data.TeamDynamics.PersonalityType, ULocalizationBFL::LoadLocalizedPersonalityType(Data.TeamDynamics.PersonalityType));

		/** TODO: MISSING DATA */
		K2_OnTeamDynamics();
	}

	//~=================================================================================================================
	// POPUPS
	//~=================================================================================================================
	{
		check(LocalizationStringTable);
		if((Data.State.Condition / 100.f) < 1.f/3.f)
		{
			FString OutString;
			LocalizationStringTable->GetStringTable()->GetSourceString(TEXT("FootballerProfiler.General.State.Condition.Tooltip"), OutString);
			
			K2_OnPopupDisplay_Condition(true, FText::FromString(OutString));
		}
		else
		{
			K2_OnPopupDisplay_Condition(false, INVTEXT(""));
		}
		
		if((Data.State.Morale / 100.f) < 1.f/3.f)
		{
			FString OutString;
			LocalizationStringTable->GetStringTable()->GetSourceString(TEXT("FootballerProfiler.General.State.Morale.Tooltip"), OutString);
			
			K2_OnPopupDisplay_Morale(true, FText::FromString(OutString));
		}
		else
		{
			K2_OnPopupDisplay_Morale(false, INVTEXT(""));
		}
		
		if((Data.State.Sharpness / 100.f) < 1.f/3.f)
		{
			FString OutString;
			LocalizationStringTable->GetStringTable()->GetSourceString(TEXT("FootballerProfiler.General.State.Sharpness.Tooltip"), OutString);
			
			K2_OnPopupDisplay_Sharpness(true, FText::FromString(OutString));
		}
		else
		{
			K2_OnPopupDisplay_Sharpness(false, INVTEXT(""));
		}
		
		if(Data.State.Injured > 0)
		{
			FString OutString;
			LocalizationStringTable->GetStringTable()->GetSourceString(TEXT("FootballerProfiler.General.State.Injuries.Tooltip"), OutString);
			K2_OnPopupDisplay_Injuries(true, FText::Format(FText::FromString(OutString), FText::AsDate(Data.State.InjuredEndDate)));
		}
		else
		{
			K2_OnPopupDisplay_Injuries(false, INVTEXT(""));
		}
		
		if(Data.State.PenaltyCards[Footballer::EPenaltyCardType::Red] > 0)
		{
			FString OutString;
			LocalizationStringTable->GetStringTable()->GetSourceString(TEXT("FootballerProfiler.General.State.Cards.TooltipRed"), OutString);
			K2_OnPopupDisplay_Cards(true, FText::Format(FText::FromString(OutString), FText::AsDate(Data.State.PenaltyCardsBanedEndDate)));
		}
		else if(Data.State.PenaltyCards[Footballer::EPenaltyCardType::Yellow] > 0)
		{
			FString OutString;
			LocalizationStringTable->GetStringTable()->GetSourceString(TEXT("FootballerProfiler.General.State.Cards.TooltipYellow"), OutString);
			K2_OnPopupDisplay_Cards(true, FText::Format(FText::FromString(OutString), 5 - Data.State.PenaltyCards[Footballer::EPenaltyCardType::Yellow]));
		}
		else
		{
			K2_OnPopupDisplay_Cards(false, INVTEXT(""));
		}
	}

	//~=================================================================================================================
	// ATTRIBUTES
	//~=================================================================================================================
	{
		// Populate attributes panels
		auto PopulateAttributes = [&](UListTextNumberValues* Panel, EFootballerAttributes From, EFootballerAttributes To)
		{
			const int32 Offset        = static_cast<int32>(From);
			const int32 NumAttributes = 1 + static_cast<int32>(To) - Offset;

			TArray<FListTextNumberValuesType> Attributes;
			for (int32 i = 0; i < NumAttributes; i++)
			{
				EFootballerAttributes Attribute = static_cast<EFootballerAttributes>(Offset + i);
				
				FListTextNumberValuesType ValuesType;
				ValuesType.Text  = ULocalizationBFL::LoadLocalizedAttribute(Attribute);
				ValuesType.Value = Data.Attributes[static_cast<uint8>(Attribute)];
				Attributes.Add(ValuesType);
			}
			
			Panel->PopulateElements(Attributes);
		};

		// Only in the case where the footballer is a GK (Goalkeeper) do we display a list of differing attributes in
		// the 'Technical' category.
		//
		// Since only a single GK-positioned footballer can exist at a time, this calculation can be made here rather
		// than recalculating it every time the position changes.
		//
		// @see https://nimblegiant.slack.com/archives/C054VQXQJP4/p1698764862078819?thread_ts=1698690384.629139&cid=C054VQXQJP4
		if(CurrentFootballerData->DesiredFieldPositions.Contains(EFieldPosition::GK))
		{
			PopulateAttributes(K2_GetListTextNumberValues_Technical(), EFootballerAttributes::Reflexes, EFootballerAttributes::OneOnOnes);
		}
		else
		{
			PopulateAttributes(K2_GetListTextNumberValues_Technical(), EFootballerAttributes::Tackling, EFootballerAttributes::Control);
		}

		PopulateAttributes(K2_GetListTextNumberValues_Physical(), EFootballerAttributes::Speed, EFootballerAttributes::JumpReach);
		PopulateAttributes(K2_GetListTextNumberValues_Mental(), EFootballerAttributes::Creativity, EFootballerAttributes::Aggression);

		
		// Populate SoccerField
		K2_GetSoccerField()->ClearInteractablePosition();

		FFootballerData::FFootballerRating BestRating;
		EFieldPosition BestFieldPosition = EFieldPosition::None;
		for(const EFieldPosition Position : CurrentFootballerData->DesiredFieldPositions)
		{
			const FFootballerData::FFootballerRating FieldRating = CurrentFootballerData->CalculateFootballerRating(Position);
			if(FieldRating.Overall > BestRating.Overall)
			{
				BestRating        = FieldRating;
				BestFieldPosition = Position;
			}

			K2_GetSoccerField()->AddInteractablePosition(Position);
		}
		
		OnSoccerFieldPositionClicked(BestFieldPosition, true);
	}
	
	//~=================================================================================================================
	// CONTRACTS
	//~=================================================================================================================
	{
		K2_OnContractDuration(Data.Contract.ExpirySeason, Data.Contract.CalculateRemainingSeasons());
		K2_OnContractSalary(Data.Contract.Salary);
		K2_OnContractMarketValue(Data.Contract.MarketValue, Data.Contract.LastUpdateMarketValue);
		/** TODO: MISSING DATA */
		K2_OnContractOffers();
	}
	
	//~=================================================================================================================
	// HISTORY/STATS
	//~=================================================================================================================
	{
		check(LocalizationStringTable);
		
		// StartSeason
		{
			FString OutString;
			LocalizationStringTable->GetStringTable()->GetSourceString(TEXT("FootballerProfiler.HistoryAndStats.StartSeason"), OutString);

			const FString YearString = FString::Printf(TEXT("%d"), Data.Contract.StartSeason.GetYear());
			K2_OnUpdateStartSeason(FText::Format(FText::AsCultureInvariant("Start season {0}"), FText::FromString(YearString)));
		}

		// Stats (This Season)
		{
			auto PopulateStats = [&](UListTextNumberValues* Panel, const TArray<int32>& Stat)
			{
				static TArray Keys =
				{
					TEXT("FootballerProfiler.HistoryAndStats.MatchesPlayed"),
					TEXT("FootballerProfiler.HistoryAndStats.GoalsScored"),
					TEXT("FootballerProfiler.HistoryAndStats.MostGoalsInOneMatch"),
					TEXT("FootballerProfiler.HistoryAndStats.SeasonsInClub")
				};
				
				TArray<FListTextNumberValuesType> Stats;
				for(int32 i = 0; i < Keys.Num(); i++)
				{
					FString OutString;
					LocalizationStringTable->GetStringTable()->GetSourceString(Keys[i], OutString);
					
					FListTextNumberValuesType ValuesType;
					ValuesType.Text = FText::FromString(OutString);
					ValuesType.Value = Stat[i];
					Stats.Add(ValuesType);
				}
				Panel->PopulateElements(Stats);
			};

			/** TODO: MISSING DATA */
			PopulateStats(K2_GetListTextNumberValues_StatsThisSeason(), { Data.Stats.CurrentSeason.MatchesPlayed, Data.Stats.CurrentSeason.GoalsScored, Data.Stats.CurrentSeason.MostGoalsInOneMatch, Data.Stats.CurrentSeason.SeasonsInClub });
			/** TODO: MISSING DATA */
			PopulateStats(K2_GetListTextNumberValues_StatsAllSeasons(), { Data.Stats.AllSeasons.MatchesPlayed, Data.Stats.AllSeasons.GoalsScored, Data.Stats.AllSeasons.MostGoalsInOneMatch, Data.Stats.AllSeasons.SeasonsInClub });
		}

		/** TODO: MISSING DATA */
		const TArray<FAwardValue_Blueprint> Values = 
		{
			{ INVTEXT("BALÓN DE PAPEL"),     1980, 1990, nullptr },
			{ INVTEXT("BALÓN DE CORCHO"),    1990, 2000, nullptr },
			{ INVTEXT("BALÓN DE NATILLAS"),  2000, 2010, nullptr },
			{ INVTEXT("BALÓN DE LACASITOS"), 2010, 2020, nullptr },
			{ INVTEXT("BALÓN DE PALOMITAS"), 2020, 2030, nullptr },
			{ INVTEXT("BALÓN DE GOMINOLAS"), 2030, 2040, nullptr }
		};
		K2_OnUpdateAwards(Values);
	}
}

TArray<FFootballerData*> UFootballerProfile::GenerateFootballersDataFromTeam_Deprecated() const
{
	check(CurrentTeam);
	
	TArray<FFootballerData*> FootballersData;
	FootballersData.Reserve(CurrentTeam->Starters.Num() + CurrentTeam->Reserves.Num() + CurrentTeam->Substitutes.Num());
	
	for(UFootballerObject* FootballerObject :  CurrentTeam->Starters)
	{
		FootballersData.Add(&FootballerObject->Data);
	}

	for(UFootballerObject* FootballerObject :  CurrentTeam->Reserves)
	{
		FootballersData.Add(&FootballerObject->Data);
	}

	for(UFootballerObject* FootballerObject :  CurrentTeam->Substitutes)
	{
		FootballersData.Add(&FootballerObject->Data);
	}

	return FootballersData;
}

void UFootballerProfile::SaveNotes(const FText& Text)
{
	check(CurrentFootballerData);
	
	CurrentFootballerData->CustomNotes = Text.ToString();
}

void UFootballerProfile::UpdateDisplayName(const FText& NewName, const FText& NewLastName, const bool bLastNameHighlight)
{
	check(CurrentFootballerData);

	CurrentFootballerData->DisplayName.FirstName = NewName;
	CurrentFootballerData->DisplayName.LastName  = NewLastName;
	
	CurrentFootballerData->DisplayName.SelectedDisplayName = bLastNameHighlight
	? FFootballerData::FFootballerName::EDisplayName::LastName
	: FFootballerData::FFootballerName::EDisplayName::FirstName;

	K2_OnFootballerName(CurrentFootballerData->DisplayName.FirstName, CurrentFootballerData->DisplayName.LastName, CurrentFootballerData->DisplayName.SelectedDisplayName == FFootballerData::FFootballerName::EDisplayName::LastName);

	/** TODO: POOR PERFORMANCE. FIND OTHER SOLUTION */
	/** TODO: CODE DUPLICATED FROM UFootballerProfile::DisplayWidget */
	K2_GetFootballersCardScrollBox()->FillFootballersData(GenerateFootballersDataFromTeam_Deprecated());
	auto Array = GenerateFootballersDataFromTeam_Deprecated();
	for(int32 i = 0; i < Array.Num(); i++)
	{
		if(*Array[i] == *CurrentFootballerData)
		{
			PopulateFootballerFromIndex(i);
			break;
		}
	}
}

void UFootballerProfile::UpdateFootballerNumber(const int32 Number)
{
	check(CurrentFootballerData);
	
	// Type 'int8' is not supported by blueprint. So.... 
	check(Number <= TNumericLimits<decltype(CurrentFootballerData->Number)>::Max());

	CurrentFootballerData->Number = Number;
	K2_OnFootballerNumber(Number);
}

void UFootballerProfile::UpdateFootballerNationality(const FISO316612& ISO316612)
{
	check(CurrentFootballerData);
	
	CurrentFootballerData->Nationality.ISO_3166_12 = FName(ISO316612.ISO);
	K2_OnFootballerNationality(*CurrentFootballerData->Nationality.LoadISO());
}
