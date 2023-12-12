// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "BT_Ser_AttackDisCheck.generated.h"

/**
 * 
 */
UCLASS()
class FPS_ZOMBIE_API UBT_Ser_AttackDisCheck : public UBTService
{
	GENERATED_BODY()

private:
	UBT_Ser_AttackDisCheck();

	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
