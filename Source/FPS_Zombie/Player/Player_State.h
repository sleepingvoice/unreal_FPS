// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Player_Enum.h"
#include "GameFramework/PlayerState.h"
#include "Player_State.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FMulti_MoveState,EAniState_Move);
DECLARE_MULTICAST_DELEGATE_OneParam(FMUlti_WeaponState,EAniState_Weapon);

UCLASS()
class FPS_ZOMBIE_API APlayer_State : public APlayerState
{
	GENERATED_BODY()
	
public:
	UPROPERTY()
	EAniState_Move PlayerMove;

	UPROPERTY()
	EAniState_Weapon PlayerWeapon;

private:
	FMulti_MoveState ChangeMove;

	FMUlti_WeaponState ChangeWeapon;

public:
	APlayer_State();
	
	virtual void BeginPlay() override;

	void AddMoveListener(EAniState_Move& State);

	void AddWeaponListener(EAniState_Weapon& State);
	
	UFUNCTION(BlueprintCallable)
	void ChangeMoveState(EAniState_Move Value);

	UFUNCTION(BlueprintCallable)
	void ChangeWeaponState(EAniState_Weapon Value);
};
