// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "BT_Deco_AttackCheck.generated.h"

/**
 * 
 */
UCLASS()
class FPS_ZOMBIE_API UBT_Deco_AttackCheck : public UBTDecorator
{
	GENERATED_BODY()

private:
	UBT_Deco_AttackCheck();

	
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;
	
};
