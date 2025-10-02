// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class AppliedGameDesign_UE : ModuleRules
{
	public AppliedGameDesign_UE(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] {
			"Core",
			"CoreUObject",
			"Engine",
			"InputCore",
			"EnhancedInput",
			"AIModule",
			"NavigationSystem",
			"StateTreeModule",
			"GameplayStateTreeModule",
			"Niagara",
			"UMG",
			"Slate"
		});

		PrivateDependencyModuleNames.AddRange(new string[] { });

		PublicIncludePaths.AddRange(new string[] {
			"AppliedGameDesign_UE",
			"AppliedGameDesign_UE/Variant_Strategy",
			"AppliedGameDesign_UE/Variant_Strategy/UI",
			"AppliedGameDesign_UE/Variant_TwinStick",
			"AppliedGameDesign_UE/Variant_TwinStick/AI",
			"AppliedGameDesign_UE/Variant_TwinStick/Gameplay",
			"AppliedGameDesign_UE/Variant_TwinStick/UI"
		});

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
