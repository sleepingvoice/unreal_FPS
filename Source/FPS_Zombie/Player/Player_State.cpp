// Fill out your copyright notice in the Description page of Project Settings.


#include "Player_State.h"
#include "Player_Controller.h"

APlayer_State::APlayer_State()
{
	PlayerNormalState = EAniState_Normal::Idle;
}

void APlayer_State::BeginPlay()
{
	Cast<APlayer_Controller>(GetPawn()->Controller)->AddChangeListener(PlayerNormalState);
	UE_LOG(LogTemp,Log,TEXT("이벤트 추가"));
}

