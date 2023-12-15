// Fill out your copyright notice in the Description page of Project Settings.


#include "Zombie_Character.h"

#include "Zombie_AI_Controller.h"

// Sets default values
AZombie_Character::AZombie_Character()
{
	
}

void AZombie_Character::BeginPlay()
{
	Super::BeginPlay();
	AiCon = Cast<AZombie_AI_Controller>(GetController());
}

void AZombie_Character::AddStateListener(TFunction<void(EZombieAIstate state)> Lambda)
{
	dZombieAIState.AddLambda(Lambda);
}

void AZombie_Character::SetStateValue(EZombieAIstate state)
{
	if(!dZombieAIState.IsBound()) return;
	
	dZombieAIState.Broadcast(state);
}