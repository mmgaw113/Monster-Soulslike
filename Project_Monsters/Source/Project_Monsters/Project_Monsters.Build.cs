// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Project_Monsters : ModuleRules
{
	public Project_Monsters(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[]
		{
			"AIModule",
			"Core", 
			"CoreUObject", 
			"Engine", 
			"GameplayAbilities",
			"GameplayTags",
			"GameplayTasks",
			"InputCore", 
			"EnhancedInput", 
			"UMG"
		});
	}
}
