// Fill out your copyright notice in the Description page of Project Settings.


#include "BT_Deco_MoveCheck.h"
#include "../Zombie_AI_Controller.h"
#include "Kismet/GameplayStatics.h"

UBT_Deco_MoveCheck::UBT_Deco_MoveCheck()
{
	NodeName = "MoveCheck";
}


bool UBT_Deco_MoveCheck::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	AZombie_AI_Controller* AICon = Cast<AZombie_AI_Controller>(OwnerComp.GetAIOwner());
	if(AICon == nullptr) return false;

	return !(AICon->bMoveZombie); // 안움직이면 움직일수있는 상태임
}
