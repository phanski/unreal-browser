// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class cpp2 : ModuleRules
{
	public cpp2(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		// Core
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput" });

		// Custom
		PublicDependencyModuleNames.AddRange(new string[] { "glTFRuntime", "LuaMachine", "WebSockets" });
        //PublicDependencyModuleNames.Add();
        PrivateDependencyModuleNames.AddRange(new string[] {  });
		//PublicIncludePaths.AddRange(new string[] { "RealtimeMeshComponent/Public", "RealtimeMeshComponent/Classes" });
		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });
		
		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
