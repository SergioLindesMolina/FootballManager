// Copyright, 2023, by NGD Studios AB. All rights reserved.


#include "MatchGameState.h"
#include "MatchPlayerController.h"
#include "MatchGameMode.h"


FMatchResult AMatchGameState::ServerSimulate(AMatchPlayerController* PlayerA, AMatchPlayerController* PlayerB)
{
	check(GetLocalRole() == ROLE_Authority);

	FMatchResult Result;

	HalfNumber = 1;
	OnOrdinaryTimeBegin.Broadcast(HalfNumber);
	GetWorldTimerManager().SetTimer(TimerHandle, this, &AMatchGameState::OnEndTimer, OrdinaryTime * 60.0f, false);
	FootballMatchState = EFootballMatchState::OrdinaryTime;

	return Result;
}


bool AMatchGameState::IsTie()
{
	return false;
}


void AMatchGameState::OnEndTimer()
{
	switch (FootballMatchState)
	{
	case EFootballMatchState::OrdinaryTime:
		DoOrdinaryTimeEnd();
		break;
	case EFootballMatchState::HalfTime:
		DoHalfTimeEnd();
		break;
	case EFootballMatchState::ExtraTime:
		DoExtraTimeEnd();
		break;
	case EFootballMatchState::ExtraTimeHalfTime:
		DoExtraTimeHalfTimeEnd();
		break;
	}
}

void AMatchGameState::FinishFootballMatch()
{
	GetWorld()->GetAuthGameMode<AMatchGameMode>()->EndMatch();
	GetWorldTimerManager().ClearTimer(TimerHandle);
	OnMatchFinished.Broadcast();
}

void AMatchGameState::DoOrdinaryTimeEnd()
{
	OnOrdinaryTimeEnd.Broadcast(HalfNumber);

	if (HalfNumber == 1)
	{
		FootballMatchState = EFootballMatchState::HalfTime;
		GetWorldTimerManager().SetTimer(TimerHandle, this, &AMatchGameState::OnEndTimer, HalfTimeTime * 60.0f, false);
		OnHalfTimeBegin.Broadcast(HalfNumber);
	}
	else
	{
		if (IsTie())
		{
			HalfNumber = 1;
			DoExtraTimeBegin();
		}
		else
		{
			FinishFootballMatch();
		}
	}
}

void AMatchGameState::DoExtraTimeBegin()
{
	FootballMatchState = EFootballMatchState::ExtraTime;
	GetWorldTimerManager().SetTimer(TimerHandle, this, &AMatchGameState::OnEndTimer, ExtraTime * 60.0f, false);

	OnExtraTimeBegin.Broadcast(HalfNumber);
}

void AMatchGameState::DoExtraTimeEnd()
{
	OnExtraTimeEnd.Broadcast(HalfNumber);

	if (HalfNumber == 1)
	{
		GetWorldTimerManager().SetTimer(TimerHandle, this, &AMatchGameState::OnEndTimer, HalfTimeExtraTime * 60.0f, false);
		OnExtraTimeHalfTimeBegin.Broadcast(HalfNumber);
	}
	else
	{
		FinishFootballMatch();
	}
}

void AMatchGameState::DoHalfTimeEnd()
{
	OnHalfTimeEnd.Broadcast(HalfNumber);

	HalfNumber = 2;
	FootballMatchState = EFootballMatchState::OrdinaryTime;
	GetWorldTimerManager().SetTimer(TimerHandle, this, &AMatchGameState::OnEndTimer, OrdinaryTime * 60.0f, false);

	OnOrdinaryTimeBegin.Broadcast(HalfNumber);

}

void AMatchGameState::DoExtraTimeHalfTimeEnd()
{
	OnExtraTimeHalfTimeEnd.Broadcast(HalfNumber);

	HalfNumber = 2;
	FootballMatchState = EFootballMatchState::ExtraTime;
	GetWorldTimerManager().SetTimer(TimerHandle, this, &AMatchGameState::OnEndTimer, ExtraTime * 60.0f, false);
	
	OnExtraTimeBegin.Broadcast(HalfNumber);
}