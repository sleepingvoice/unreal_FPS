// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "FPS_Zombie/Zombie/Zombie_Enum.h"
#include "BT_Task_ChangeState.generated.h"

/**
 * 
 */
UCLASS()
class FPS_ZOMBIE_API UBT_Task_ChangeState : public UBTTaskNode
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere,Blueprintable)
	EZombieAIstate TargetState;
	
private:
	UBT_Task_ChangeState();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	
};
