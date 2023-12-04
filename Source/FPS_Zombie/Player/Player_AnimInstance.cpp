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
	
	PlayerCon = Cast<APlayer_Controller>(TryGetPawnOwner()->Controller);
	if(PlayerCon != nullptr)
	{
		PlayerCon->AddChangeListener(NormalState);
	}
	
}

void UPlayer_AnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
}


