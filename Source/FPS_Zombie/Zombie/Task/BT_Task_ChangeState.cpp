// Fill out your copyright notice in the Description page of Project Settings.


#include "BT_Task_ChangeState.h"
#include "AIController.h"
#include "FPS_Zombie/Zombie/Zombie_Character.h"

UBT_Task_ChangeState::UBT_Task_ChangeState()
{
	NodeName = TEXT("ChangeZombieState");
}

EBTNodeResult::Type UBT_Task_ChangeState::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	APawn* ControllingPawn = OwnerComp.GetAIOwner()->GetPawn();
	if (nullptr == ControllingPawn) return EBTNodeResult::Failed;

	auto ZombieCharacter = Cast<AZombie_Character>(ControllingPawn);
	if(nullptr == ZombieCharacter) return EBTNodeResult::Failed;
	
	ZombieCharacter->SetStateValue(TargetState);
	return EBTNodeResult::Succeeded;
}
