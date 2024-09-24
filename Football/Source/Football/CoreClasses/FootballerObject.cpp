// Copyright, 2023, by NGD Studios AB. All rights reserved.


#include "FootballerObject.h"

#include <Football/UtilsFunctionLibrary.h>
#include <Football/UI/LocalizationBFL.h>


EFootballerLineUp UFootballerObject::GetLineUpPosition() const
{
	return Data.LineUpPosition;
}

TArray<EFieldPosition> UFootballerObject::GetDesiredPositions() const
{
	return Data.DesiredFieldPositions;
}

EFieldPosition UFootballerObject::GetSelectedFieldPosition() const
{
	return Data.SelectedFieldPosition;
}

FString UFootballerObject::GetName() const
{
	//@todo(jcastro) The BP that calls this should use FText and have a more distinctive identifier than just "GetName"
	// as it could be FirstName, LastName, or DisplayName
	return Data.DisplayName.FirstName.ToString();
}

FString UFootballerObject::GetDisplayName() const
{
	//@todo(jcastro) The BP that calls this should use FText
	return Data.DisplayName.GetDisplayName().ToString();
}

uint8 UFootballerObject::GetNumber() const
{
	return Data.Number;
}

void UFootballerObject::GetRating(float& Stars, float& Overall, float &Potential, ERatingLevel &Level) const
{
	Stars = Data.Rating.Stars;
	Overall = Data.Rating.Overall;
	Level = Data.Rating.Level;
	Potential = Data.Rating.Potential;
}

int32 UFootballerObject::GetId() const
{
	return Data.Id;
}

float UFootballerObject::GetShootingAttribute() const
{
	return Data.Attributes[static_cast<int32>(EFootballerAttributes::Shooting)];
}

void UFootballerObject::SetKickerPreviewInfo(const FString& InName, EPreferredFootType Foot, uint8 InNumber, EFieldPosition FieldPosition)
{
	//@todo(jcastro) The BP that calls this should use FText and have a more distinctive identifier than just "InName"
	// as it could be FirstName, LastName, or DisplayName
	Data.DisplayName = FFootballerData::FFootballerName(
		FText::FromString(InName),
		INVTEXT("N/A from UFootballerObject::SetKickerPreviewInfo")
	);
	Data.PhysicalFeatures.PreferredFoot = Foot;
	Data.Number = InNumber;
	Data.SelectedFieldPosition = FieldPosition;
}

TArray<FString> UFootballerObject::GetAllProperties() const
{
	TArray<FString> Ret;

	Ret.Add(FString::Printf(TEXT("Number: %d"), Data.Number));
	Ret.Add(FString::Printf(TEXT("FirstName: %s"), *Data.DisplayName.FirstName.ToString()));
	Ret.Add(FString::Printf(TEXT("LastName: %s"), *Data.DisplayName.LastName.ToString()));
	Ret.Add(FString::Printf(TEXT("DisplayName: %s"), *Data.DisplayName.GetDisplayName().ToString()));

	const UEnum* const CharacterTypeEnum = StaticEnum<ECharacterType>();
	Ret.Add(FString::Printf(TEXT("CharacterType: %s"), *CharacterTypeEnum->GetNameStringByValue((int64)Data.CharacterType)));
	Ret.Add(FString::Printf(TEXT("CharcterType Priority: %d"), Data.CharacterTypePriority));

	Ret.Add(FString::Printf(TEXT("Age: %f"), Data.Age));
	Ret.Add(FString::Printf(TEXT("AgeOfRetirnement : %d"), Data.AgeOfRetirement ));
	Ret.Add(FString::Printf(TEXT("Nationality: %s"), *Data.Nationality.LoadISO()->DisplayName.ToString()));

	FString DesiredPositionsText(TEXT("DesiredFieldPositions: "));
	const UEnum* const FieldPositionEnum = StaticEnum<EFieldPosition>();
	for (int32 i=0; i<Data.DesiredFieldPositions.Num(); ++i)
	{
		DesiredPositionsText += FieldPositionEnum->GetNameStringByValue((int64)Data.DesiredFieldPositions[i]) + ", ";
	}
	Ret.Add(DesiredPositionsText);
	Ret.Add(FString::Printf(TEXT("SelectedFieldPosition: %s"), *FieldPositionEnum->GetNameStringByValue((int64)Data.SelectedFieldPosition)));
	
	const UEnum* const FootballerRoleEnum = StaticEnum<EFootballerRole>();
	Ret.Add(FString::Printf(TEXT("Role: %s"), *FootballerRoleEnum->GetNameStringByValue((int64)Data.Role)));

	const UEnum* const FootballerSpecialTraitEnum = StaticEnum<ESpecialTrait>();
	Ret.Add(FString::Printf(TEXT("Special Trait : %s"), *FootballerSpecialTraitEnum->GetNameStringByValue((int64)Data.SpecialTrait)));
	Ret.Add(FString::Printf(TEXT("Special Trait Level : %d"), Data.SpecialTraitLevel));
	Ret.Add(FString::Printf(TEXT("Trait Points : %d"), Data.TraitPoints));

	Ret.Add("Attributes:");
	for(int32 i = 0; i < static_cast<int32>(EFootballerAttributes::MAX_COUNT); i++)
	{
		const auto Attribute = static_cast<EFootballerAttributes>(i);
		Ret.Add(FString::Printf(TEXT("\t%s: %f"), *ULocalizationBFL::LoadLocalizedAttribute(Attribute).ToString(), Data.Attributes[i]));
	}

	Ret.Add("State:");
	Ret.Add(FString::Printf(TEXT("\tCondition: %f"), Data.State.Condition));
	Ret.Add(FString::Printf(TEXT("\tMorale: %f"), Data.State.Morale));
	Ret.Add(FString::Printf(TEXT("\tSharpness: %f"), Data.State.Sharpness));
	Ret.Add(FString::Printf(TEXT("\tInjured: %f"), Data.State.Injured));
	Ret.Add(FString::Printf(TEXT("\tCards, Yellow/Red: %d/%d"), Data.State.PenaltyCards[0], Data.State.PenaltyCards[1]));

	Ret.Add("TeamDynamics:");
	Ret.Add(FString::Printf(TEXT("\tAffinityWithManager: %f"), Data.TeamDynamics.AffinityWithManager));
	Ret.Add(FString::Printf(TEXT("\tAlignmentWithTeam: %f"), Data.TeamDynamics.AlignmentWithTeam));
	Ret.Add(FString::Printf(TEXT("\tAlignmentWithTeam: %f"), Data.TeamDynamics.AlignmentWithTeam));
	
	const UEnum* const PersonalityTypeEnum = StaticEnum<EPersonalityType>();
	Ret.Add(FString::Printf(TEXT("\tPersonalityType: %s"), *PersonalityTypeEnum->GetNameStringByValue((int64)Data.TeamDynamics.PersonalityType)));
	Ret.Add(FString::Printf(TEXT("\tAlignmentWithTeam: %f"), Data.TeamDynamics.AlignmentWithTeam));
	Ret.Add("\tRelationshipsWithOtherFootballers: []");

	Ret.Add("Contract:");
	Ret.Add(FString::Printf(TEXT("\tExpirySeason: %s"), *Data.Contract.ExpirySeason.ToString()));
	Ret.Add(FString::Printf(TEXT("\tStartSeason: %s"), *Data.Contract.StartSeason.ToString()));
	Ret.Add(FString::Printf(TEXT("\tSalary: %f"), Data.Contract.Salary));
	Ret.Add(FString::Printf(TEXT("\tMarketValue: %f"), Data.Contract.MarketValue));
	Ret.Add(FString::Printf(TEXT("\tLastUpdateMarketValue: %s"), *Data.Contract.LastUpdateMarketValue.ToString()));
	const UEnum* const ContractStatusEnum = StaticEnum<EContractStatus>();
	Ret.Add(FString::Printf(TEXT("\tStatus: %s"), *ContractStatusEnum->GetNameStringByValue((int64)Data.Contract.Status)));
	
	Ret.Add("PhysicalFeatures:");
	Ret.Add(FString::Printf(TEXT("\tHeight: %f"), Data.PhysicalFeatures.Height));
	Ret.Add(FString::Printf(TEXT("\tWeight: %f"), Data.PhysicalFeatures.Weight));
	const UEnum* const PreferredFootEnum = StaticEnum<EPreferredFootType>();
	Ret.Add(FString::Printf(TEXT("\tPreferredFoot: %s"), *PreferredFootEnum->GetNameStringByValue((int64)Data.PhysicalFeatures.PreferredFoot)));
	const UEnum* const GenderEnum = StaticEnum<EFootballerGender>();
	Ret.Add(FString::Printf(TEXT("\tGender: %s"), *GenderEnum->GetNameStringByValue((int64)Data.PhysicalFeatures.Gender)));

	Ret.Add("Rating:");
	Ret.Add(FString::Printf(TEXT("\tStars: %f"), Data.Rating.Stars));
	Ret.Add(FString::Printf(TEXT("\tOverall: %f"), Data.Rating.Overall));
	Ret.Add(FString::Printf(TEXT("\tPotential: %f"), Data.Rating.Potential));
	const UEnum* const RatingLevelEnum = StaticEnum<ERatingLevel>();
	Ret.Add(FString::Printf(TEXT("\tLevel: %s"), *RatingLevelEnum->GetNameStringByValue((int64)Data.Rating.Level)));
	
	const UEnum* const LineUpFootEnum = StaticEnum<EFootballerLineUp>();
	Ret.Add(FString::Printf(TEXT("LineUpPosition: %s"), *LineUpFootEnum->GetNameStringByValue((int64)Data.LineUpPosition)));

	return Ret;
}

EPreferredFootType UFootballerObject::GetPreferredFoot() const
{
	return Data.PhysicalFeatures.PreferredFoot;
}

float UFootballerObject::GetAfinityWithManager() const
{
	return Data.TeamDynamics.AffinityWithManager;
}

ESpecialTrait UFootballerObject::GetSpecialTrait() const
{
	return Data.SpecialTrait;
}
