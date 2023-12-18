// Fill out your copyright notice in the Description page of Project Settings.


#include "Zombie_AnimInstance.h"

#include "Zombie_Character.h"

UZombie_AnimInstance::UZombie_AnimInstance()
{
	
}

void UZombie_AnimInstance::NativeBeginPlay()
{
	Super::NativeBeginPlay();
	AiCon = Cast<AZombie_AI_Controller>(TryGetPawnOwner()->Controller);
	Cast<AZombie_Character>(TryGetPawnOwner())->AddStateListener([&](EZombieAIstate Setstate){ AiState = Setstate; });
}


void UZombie_AnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
	if(AiCon)
	{
		CheckRun = AiCon->bMoveZombie;
	}
}
