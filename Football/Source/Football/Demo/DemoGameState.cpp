// Copyright, 2023, by NGD Studios AB. All rights reserved.

#include "DemoGameState.h"

#include <Football/UI/UserWidget/MatchHud/ManagerRenderTarget/ManagerRenderTargetWidget.h>
#include <Football/Demo/HeadCoachReaction/RenderTargetScenario.h>
#include <UWidget/Scoreboard.h>


void ADemoGameState::BeginPlay()
{
	UScoreboard* Scoreboard = nullptr;
	for (TObjectIterator<UScoreboard> It; It; ++It)
	{
		if (It->GetWorld() == GetWorld())
		{
			Scoreboard = *It;
		}
	}
	
	if (Scoreboard)
	{
		Scoreboard->SetTeamsInfo(TEXT("CRG"), TEXT("ATH"));
		Scoreboard->SetScore(0, 0);
	}

	for(TObjectIterator<UManagerRenderTargetWidget> It; It; ++It)
	{
		if(It->GetWorld() == GetWorld())
		{
			ManagerRenderTarget.Add(*It);
		}
	}

	for(TObjectIterator<ARenderTargetScenario> It; It; ++It)
	{
		if(It->GetWorld() == GetWorld()) 
		{
			RenderTargetScenario.Add(*It);
		}
	}
}
//Select 0 to LocalHeadCoach or 1 to RivalHeadCoach
void ADemoGameState::ToggleManager(int RenderTargetNum, int AnimationNum)
{
	if(!ManagerRenderTarget.IsEmpty() && RenderTargetNum < MAX_RENDERTARGET_NUM)
	{
		if(ManagerRenderTarget[RenderTargetNum]->GetVisibility() == ESlateVisibility::Hidden)
		{
			ManagerRenderTarget[RenderTargetNum]->SetVisibility(ESlateVisibility::Visible);
			RenderTargetScenario[RenderTargetNum]->PlayAnimation(AnimationNum);
		}
		else
		{
			ManagerRenderTarget[RenderTargetNum]->SetVisibility(ESlateVisibility::Hidden);
		}
	}
}
