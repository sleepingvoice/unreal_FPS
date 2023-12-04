// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "Player_Character.h"
#include "Player_Controller.h"
#include "Player_Enum.h"
#include "Player_AnimInstance.generated.h"

UCLASS()
class FPS_ZOMBIE_API UPlayer_AnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	EAniState_Normal NormalState = EAniState_Normal::Idle;

	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	APlayer_Controller* PlayerCon;
	
private:
	APlayer_Character* Player;
	
public :
	UPlayer_AnimInstance();
	
	virtual void NativeBeginPlay() override;
	
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

};
