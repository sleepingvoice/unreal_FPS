#pragma once

UENUM(BlueprintType)
enum class EZombieAIstate : uint8
{
	Idle = 0 UMETA(DisplayName = "Idle"),
	Find = 1 UMETA(DisplayName = "Find"),
	Attack = 2 UMETA(DisplayName = "Attack")
};
