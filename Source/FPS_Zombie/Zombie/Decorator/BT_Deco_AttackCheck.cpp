// Fill out your copyright notice in the Description page of Project Settings.


#include "BT_Deco_AttackCheck.h"
#include "../Zombie_AI_Controller.h"

UBT_Deco_AttackCheck::UBT_Deco_AttackCheck()
{
	NodeName = "AttackCheck";
}

bool UBT_Deco_AttackCheck::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	AZombie_AI_Controller* AICon = Cast<AZombie_AI_Controller>(OwnerComp.GetAIOwner());
	if(AICon == nullptr) return false;
	
	return AICon->bAttackPlayer;
}

