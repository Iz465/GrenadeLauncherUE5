// Copyright Epic Games, Inc. All Rights Reserved.
using UnrealBuildTool;
using System.Collections.Generic;
public class GrenadeLauncherUE5EditorTarget : TargetRules
{
	public GrenadeLauncherUE5EditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.V6;
		IncludeOrderVersion = EngineIncludeOrderVersion.Unreal5_7;
		ExtraModuleNames.Add("GrenadeLauncherUE5");
		bOverrideBuildEnvironment = true;
	}
}