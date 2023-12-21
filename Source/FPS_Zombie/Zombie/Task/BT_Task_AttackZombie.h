// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BT_Task_AttackZombie.generated.h"

/**
 * 
 */
UCLASS()
class FPS_ZOMBIE_API UBT_Task_AttackZombie : public UBTTaskNode
{
	GENERATED_BODY()

	UBT_Task_AttackZombie();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
