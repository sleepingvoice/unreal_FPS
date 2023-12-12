// Fill out your copyright notice in the Description page of Project Settings.


#include "BT_Deco_AttackDisCheck.h"
#include "../Zombie_AI_Controller.h"

UBT_Deco_AttackDisCheck::UBT_Deco_AttackDisCheck()
{
	NodeName = "AttackDisCheck";
}

bool UBT_Deco_AttackDisCheck::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	AZombie_AI_Controller* AICon = Cast<AZombie_AI_Controller>(OwnerComp.GetAIOwner());
	if(AICon == nullptr) return false;
	
	return AICon->bAttackDis;
}
