// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class FirstUnrealProject : ModuleRules
{
	public FirstUnrealProject(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] {
			"Core",
			"CoreUObject",
			"Engine",
			"InputCore",
			"EnhancedInput",
			"AIModule",
			"StateTreeModule",
			"GameplayStateTreeModule",
			"UMG",
			"Slate"
		});

		PrivateDependencyModuleNames.AddRange(new string[] { });

		PublicIncludePaths.AddRange(new string[] {
			"FirstUnrealProject",
			"FirstUnrealProject/Variant_Platforming",
			"FirstUnrealProject/Variant_Platforming/Animation",
			"FirstUnrealProject/Variant_Combat",
			"FirstUnrealProject/Variant_Combat/AI",
			"FirstUnrealProject/Variant_Combat/Animation",
			"FirstUnrealProject/Variant_Combat/Gameplay",
			"FirstUnrealProject/Variant_Combat/Interfaces",
			"FirstUnrealProject/Variant_Combat/UI",
			"FirstUnrealProject/Variant_SideScrolling",
			"FirstUnrealProject/Variant_SideScrolling/AI",
			"FirstUnrealProject/Variant_SideScrolling/Gameplay",
			"FirstUnrealProject/Variant_SideScrolling/Interfaces",
			"FirstUnrealProject/Variant_SideScrolling/UI"
		});

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
