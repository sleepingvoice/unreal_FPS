// Fill out your copyright notice in the Description page of Project Settings.


#include "BT_Task_MoveZombie.h"
#include "AIController.h"
#include "NavigationSystem.h"
#include "../Zombie_AI_Controller.h"
#include "../Zombie_Character.h"
#include "BehaviorTree/BlackboardComponent.h"

UBT_Task_MoveZombie::UBT_Task_MoveZombie()
{
	NodeName = TEXT("MoveZombie");
}

EBTNodeResult::Type UBT_Task_MoveZombie::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);
	APawn* ControllingPawn = OwnerComp.GetAIOwner()->GetPawn();
	if (nullptr == ControllingPawn) return EBTNodeResult::Failed;

	UNavigationSystemV1* NavSystem = UNavigationSystemV1::GetNavigationSystem(ControllingPawn->GetWorld());
	if (nullptr == NavSystem) return EBTNodeResult::Failed;

	auto AiCon = Cast<AZombie_AI_Controller>(OwnerComp.GetAIOwner());
	
	if(AiCon->CanChasing()) // 찾았을때
	{
		AiCon->MoveToActor(AiCon->PlayerCharacter);
		AiCon->bMoveZombie = false;
		return EBTNodeResult::Succeeded;
	}
	else // 못찾았을때 랜덤한 지역으로 이동
	{
		FNavLocation NextPatrol;

		if (NavSystem->GetRandomReachablePointInRadius(FVector::ZeroVector, AiCon->fRandomFindLength, NextPatrol))
		{
			FVector Vect = NextPatrol.Location;
			AiCon->MoveToLocation(Vect);
			AiCon->bMoveZombie = true;
			return EBTNodeResult::Succeeded;
		}
	}
	
	return EBTNodeResult::Failed;
}
