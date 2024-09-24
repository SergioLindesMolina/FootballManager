// Copyright, 2023, by NGD Studios AB. All rights reserved.


#include "PostMatchSplashScreenMVP.h"
#include "Football/CoreClasses/DataStructures/Footballer.h"

void UPostMatchSplashScreenMVP::UpdateMVP(const FFootballerData& Footballer, const int32 Goals, const int32 Shoots, const int32 Performance)
{
	K2_OnUpdateMVP(Footballer.DisplayName.FirstName.ToString(), Footballer.DisplayName.LastName.ToString(), Footballer.SelectedFieldPosition
		, Footballer.Number, Footballer.Rating.Overall, Footballer.Rating.Stars, Footballer.Rating.Level, Goals, Shoots, Performance);
}
