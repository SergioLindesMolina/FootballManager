// Copyright, 2023, by NGD Studios AB. All rights reserved.

using UnrealBuildTool;

public class FootballTeamGenerator : ModuleRules
{
	public FootballTeamGenerator(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
		PublicDependencyModuleNames.AddRange(new string[]
		{
			"Core",
			"CoreUObject",
			"Engine",
			
			"Football"
		});

		PublicDefinitions.Add("FOOTBALL_TEAM_GENERATOR");
	}
}
