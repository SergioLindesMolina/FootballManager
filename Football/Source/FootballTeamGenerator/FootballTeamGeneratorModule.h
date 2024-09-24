// Copyright, 2023, by NGD Studios AB. All rights reserved.

#pragma once

#include "Modules/ModuleManager.h"
#include "Football/CoreClasses/DataStructures/Footballer.h"

/**
 * Helper and fast module to generate teams.
 * Notice that this module should be used only for debug and testing proposes and should be discarded in final version.
 *
 * This "simulate" as a very early stage the real Server functionality 
 */
class FOOTBALLTEAMGENERATOR_API FFootballTeamGeneratorModule final : public FDefaultGameModuleImpl
{
public:
	static FString GenerateRandomName();
	static FString GenerateRandomSurName();
	static FFootballerData GenerateFootballerEntity();
	static FTeam GenerateTeam();


};
