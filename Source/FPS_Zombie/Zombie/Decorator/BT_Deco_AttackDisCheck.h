// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "BT_Deco_AttackDisCheck.generated.h"

/**
 * 
 */
UCLASS()
class FPS_ZOMBIE_API UBT_Deco_AttackDisCheck : public UBTDecorator
{
	GENERATED_BODY()

private:
	UBT_Deco_AttackDisCheck();

	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;
	
};
