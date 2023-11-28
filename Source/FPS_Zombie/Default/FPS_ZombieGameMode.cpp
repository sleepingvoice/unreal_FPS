// Copyright Epic Games, Inc. All Rights Reserved.

#include "FPS_ZombieGameMode.h"
#include "FPS_ZombieCharacter.h"
#include "UObject/ConstructorHelpers.h"

AFPS_ZombieGameMode::AFPS_ZombieGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
