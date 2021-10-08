using UnrealBuildTool;

public class Flow : ModuleRules
{
	public Flow(ReadOnlyTargetRules Target) : base(Target)
	{
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PrivateDependencyModuleNames.AddRange(new[] 
		{
            "Core",
			"CoreUObject",
            "DeveloperSettings",
			"Engine",
            "GameplayTags",
            "LevelSequence",
			"MovieScene",
			"MovieSceneTracks",
            "Slate",
            "SlateCore",
            "AIModule" // For the blackboard stuff
        });

        if (Target.Type == TargetType.Editor)
        {
            PublicDependencyModuleNames.Add("UnrealEd");
        }
    }
}
