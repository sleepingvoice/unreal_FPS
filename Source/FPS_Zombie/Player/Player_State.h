// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Player_Enum.h"
#include "GameFramework/PlayerState.h"
#include "Player_State.generated.h"

UCLASS()
class FPS_ZOMBIE_API APlayer_State : public APlayerState
{
	GENERATED_BODY()
	
public:
	UPROPERTY()
	EAniState_Normal PlayerNormalState;

	UPROPERTY()
	EWeapon_Value WeaponValue;

public:
	APlayer_State();
	
	virtual void BeginPlay() override;
};
