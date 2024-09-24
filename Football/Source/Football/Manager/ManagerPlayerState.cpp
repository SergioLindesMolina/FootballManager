// Copyright, 2023, by NGD Studios AB. All rights reserved.


#include "ManagerPlayerState.h"

bool AManagerPlayerState::TrySpend(int32 MoneyToSpend)
{
	if (TotalMoney >= MoneyToSpend)
	{
		TotalMoney -= MoneyToSpend;
		return true;
	}

	return false;
}

void AManagerPlayerState::SetMoney(int32 Money)
{
	TotalMoney = Money;
}