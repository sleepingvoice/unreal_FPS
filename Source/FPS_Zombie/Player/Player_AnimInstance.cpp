// Fill out your copyright notice in the Description page of Project Settings.


#include "Player_AnimInstance.h"
#include "Player_State.h"

UPlayer_AnimInstance::UPlayer_AnimInstance()
{
	
}

void UPlayer_AnimInstance::NativeBeginPlay()
{
	Super::NativeBeginPlay();
	
	auto PlayerState = Cast<APlayer_State>(TryGetPawnOwner()->GetPlayerState());
	if(PlayerState)
	{
		PlayerState->AddMoveListener([this](EAniState_Move SetState) { MoveState = SetState; });
		PlayerState->AddWeaponListener([this](EAniState_Weapon SetWeapon){ WeaponState = SetWeapon;});
		PlayerState->AddUpperistener([this](EAnistate_UpperBody SetUpper){UpperState = SetUpper;});
	}
	
}

void UPlayer_AnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
}


