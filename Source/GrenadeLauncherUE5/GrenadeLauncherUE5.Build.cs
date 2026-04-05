// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class GrenadeLauncherUE5 : ModuleRules
{
	public GrenadeLauncherUE5(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput" });
	}
}
