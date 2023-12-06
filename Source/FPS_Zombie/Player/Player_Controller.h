// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "EnhancedInputComponent.h"
#include "InputActionValue.h"
#include "EnhancedInputSubsystems.h"
#include "Player_Character.h"
#include "Player_State.h"
#include "Player_Controller.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FMulti_MoveState,EAniState_Move);

UCLASS()
class FPS_ZOMBIE_API APlayer_Controller : public APlayerController
{
	GENERATED_BODY()

public:
	virtual void SetupInputComponent() override;
	
private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input_Mapping", meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* DefaultMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input_Mapping", meta = (AllowPrivateAccess = "true"))
	UInputAction* Input_Jump;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input_Mapping", meta = (AllowPrivateAccess = "true"))
	UInputAction* Input_Move;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input_Mapping", meta = (AllowPrivateAccess = "true"))
	UInputAction* Input_Look;

	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="Input_Mapping", meta = (AllowPrivateAccess = "true"))
	UInputAction* Input_LeftClick;

	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="Input_Mapping", meta = (AllowPrivateAccess = "true"))
	UInputAction* Input_RightClick;

	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="Input_Mapping", meta = (AllowPrivateAccess = "true"))
	UInputAction* Input_Knife;

	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="Input_Mapping", meta = (AllowPrivateAccess = "true"))
	UInputAction* Input_Pistol;

	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="Input_Mapping", meta = (AllowPrivateAccess = "true"))
	UInputAction* Input_Rifle;
	
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category=Animation,meta=(AllowPrivateAccess="true"))
	float DownDis;

	UPROPERTY()
	APlayer_Character* PlayerCharacter;
	
	UPROPERTY()
	APlayer_State* PlayCharacterState;

	EAniState_Move MoveState = EAniState_Move::Idle;
	EAniState_Weapon WeaponState = EAniState_Weapon::NoWeapon;
	EAnistate_UpperBody UpperState = EAnistate_UpperBody::Normal;

public:
	void Move(const FInputActionValue& Value);

	void MoveStop(const FInputActionValue& Value);
	
	void Look(const FInputActionValue& Value);

	void Jump(const FInputActionValue& Value);

	void JumpStop(const FInputActionValue& Value);

	void LeftClick(const FInputActionValue& Value);

	void LeftClickStop(const FInputActionValue& Value);

	void RightClick(const FInputActionValue& Value);

	void KinfeHold(const FInputActionValue& Value);

	void PistolHold(const FInputActionValue& Value);

	void RifleHold(const FInputActionValue& Value);
	
	void CheckJump();
private:
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;
	


	
};
