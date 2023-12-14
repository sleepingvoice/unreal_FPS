// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Zombie_AI_Controller.h"
#include "Animation/AnimInstance.h"
#include "Zombie_AnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class FPS_ZOMBIE_API UZombie_AnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:

	UZombie_AnimInstance();
	
	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	bool CheckRun = false;
	
private:
	UPROPERTY()
	AZombie_AI_Controller* AiCon;
	
	virtual void NativeBeginPlay() override;
	
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;
};
