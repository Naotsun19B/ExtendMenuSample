// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class SamplePlugin : ModuleRules
{
	public SamplePlugin(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
			}
			);
			
		
		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				"CoreUObject",
				"Engine",
				"Slate",
				"SlateCore",
				"LevelEditor",	// ’Ç‰Á.
			}
			);
	}
}
