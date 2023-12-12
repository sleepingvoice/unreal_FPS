// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BT_Task_MoveZombie.generated.h"

/**
 * 
 */
UCLASS()
class FPS_ZOMBIE_API UBT_Task_MoveZombie : public UBTTaskNode
{
	GENERATED_BODY()

public:
	
	UBT_Task_MoveZombie();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
