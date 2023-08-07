// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Project_Item_Inven : ModuleRules
{
	public Project_Item_Inven(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay", "UMG" });
	}
}
