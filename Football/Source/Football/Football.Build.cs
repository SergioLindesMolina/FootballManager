// Fill out your copyright notice in the Description page of Project Settings.

using System.IO;
using UnrealBuildTool;

public class Football : ModuleRules
{
	public Football(ReadOnlyTargetRules target) : base(target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
		PublicDependencyModuleNames.AddRange(new[] 
		{
			// Epic Modules
	 		"Core", 
	 		"CoreUObject", 
	 		"Engine", 
	 		"InputCore", 
	 		"HTTP", 
	 		"Json", 
	 		"JsonUtilities", 
	 		"UMG", 
	 		"Slate", 
	 		"SlateCore",
			"LevelSequence",
			"MovieScene",
			"EnhancedInput",
			"MoviePlayer",
	        
			// Nimble Modules
	        "UserInterface",
	        "DialogueSystem",
	        "CursorSubsystem",
	        
	        // Development Modules
	        //"FootballTeamGenerator"
	 	});

		
		
		// @todo(jcastro): Make a DataAsset to Dialogues instead of doing this
		foreach(var asset in Directory.GetFiles(Path.Combine(ModuleDirectory, "..", "..", "Content", "Football", "Dialogues"), "*", SearchOption.AllDirectories))
		{
			RuntimeDependencies.Add(asset);
		}
		
		// DEBUG PROPUSE ONLY
		// @todo(jcastro) remove in final version
		foreach(var asset in Directory.GetFiles(Path.Combine(ModuleDirectory, "..", "..", "Content", "Football", "Teams"), "*", SearchOption.AllDirectories))
		{
			RuntimeDependencies.Add(asset);
		}
		
		if (target.Configuration != UnrealTargetConfiguration.Shipping)
		{
			PublicDependencyModuleNames.Add("ImGui");
		}
	}
}
