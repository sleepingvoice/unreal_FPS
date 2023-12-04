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
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* DefaultMappingContext;

	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* Input_Jump;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* Input_Move;

	/** Look Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* Input_Look;

	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category=Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* Input_LeftClick;

	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category=Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* Input_RightClick;

	UPROPERTY()
	APlayer_Character* PlayerCharacter;

	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category=Animation,meta=(AllowPrivateAccess="true"))
	float DownDis;

	UPROPERTY()
	APlayer_State* PlayCharacterState;

	EAniState_Move MoveState = EAniState_Move::Idle;
	EAniState_Weapon WeaponState = EAniState_Weapon::NoWeapon;

public:
	void Move(const FInputActionValue& Value);

	void MoveStop(const FInputActionValue& Value);
	
	void Look(const FInputActionValue& Value);

	void Jump(const FInputActionValue& Value);

	void JumpStop(const FInputActionValue& Value);

	void LeftClick(const FInputActionValue& Value);

	void RightClick(const FInputActionValue& Value);
	
	void CheckJump();
private:
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;
	


	
};
