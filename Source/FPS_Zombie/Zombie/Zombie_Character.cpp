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
	OnChange_BTAssets();
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

void AZombie_Character::OnChange_BTAssets()
{
	if(dZombieAIState.IsBound()) dZombieAIState.Clear();
	
	for(int i=0;i<BTAssets.Num();i++)
	{
		if(i >= 3) break;
		AddStateListener([this,i](EZombieAIstate state)
		{
			if(state == static_cast<EZombieAIstate>(i))
			{
				if(AiCon == nullptr) return;
				AiCon->RunAI(BTAssets[i]);
			}
		});
	}
}