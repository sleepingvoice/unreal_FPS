// Fill out your copyright notice in the Description page of Project Settings.


#include "BT_Deco_FindPlayer.h"
#include "../Zombie_AI_Controller.h"

UBT_Deco_FindPlayer::UBT_Deco_FindPlayer()
{
	NodeName = "FindPlayer";
}

bool UBT_Deco_FindPlayer::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	AZombie_AI_Controller* AICon = Cast<AZombie_AI_Controller>(OwnerComp.GetAIOwner());
	if(AICon == nullptr) return false;
	
	return AICon->CanChasing();
}
