// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class CodeFPS : ModuleRules
{
	public CodeFPS(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay", "AIModule", "GameplayTasks", "UMG", "NavigationSystem" });
	}
}
