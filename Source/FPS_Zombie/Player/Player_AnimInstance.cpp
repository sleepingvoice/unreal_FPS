// Fill out your copyright notice in the Description page of Project Settings.


#include "Player_AnimInstance.h"
#include "Player_State.h"

APlayer_State* Target;

UPlayer_AnimInstance::UPlayer_AnimInstance()
{
	
}

void UPlayer_AnimInstance::NativeBeginPlay()
{
	Super::NativeBeginPlay();
	
	auto PlayerState = Cast<APlayer_State>(TryGetPawnOwner()->GetPlayerState());
	if(PlayerState)
	{
		PlayerState->AddMoveListener(MoveState);
		PlayerState->AddWeaponListener(WeaponState);
		PlayerState->AddUpperistener(UpperState);
	}
	
}

void UPlayer_AnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
}


