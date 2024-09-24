// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class FootballEditorTarget : TargetRules
{
	public FootballEditorTarget( TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.V5;
		IncludeOrderVersion = EngineIncludeOrderVersion.Unreal5_2;

        ExtraModuleNames.AddRange(new string[] { "Football", "FootballTeamGenerator" });
    }
}
