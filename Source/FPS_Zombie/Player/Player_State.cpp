// Fill out your copyright notice in the Description page of Project Settings.


#include "Player_State.h"



APlayer_State::APlayer_State()
{
	PlayerMove = EAniState_Move::Idle;
	PlayerWeapon = EAniState_Weapon::NoWeapon;
	PlayerUpperBody = EAnistate_UpperBody::Normal;
}

void APlayer_State::BeginPlay()
{
	Super::BeginPlay();
	
	AddMoveListener([this](EAniState_Move SetState) { PlayerMove = SetState; });
	AddWeaponListener([this](EAniState_Weapon SetWeapon){ PlayerWeapon = SetWeapon;});
	AddUpperistener([this](EAnistate_UpperBody SetUpper){PlayerUpperBody = SetUpper;});
}

void APlayer_State::AddMoveListener(TFunction<void(EAniState_Move)> State)
{
	ChangeMove.AddLambda(State);
}


void APlayer_State::ChangeMoveState(EAniState_Move Value)
{
	if(!MoveLimitCheck(Value)) return; // 만약 변경이 불가능하다면 리턴
	
	if(ChangeMove.IsBound()) ChangeMove.Broadcast(PlayerMove);
}

void APlayer_State::AddWeaponListener(TFunction<void(EAniState_Weapon)> State)
{
	ChangeWeapon.AddLambda(State);
}

void APlayer_State::ChangeWeaponState(EAniState_Weapon Value)
{
	PlayerWeapon = Value;
	
	if(ChangeWeapon.IsBound()) ChangeWeapon.Broadcast(PlayerWeapon);
}

void APlayer_State::AddUpperistener(TFunction<void(EAnistate_UpperBody)> State)
{
	ChangeUpper.AddLambda(State);
}

void APlayer_State::ChangeUpperState(EAnistate_UpperBody Value)
{
	if(ChangeUpper.IsBound()) ChangeUpper.Broadcast(Value);
}

bool APlayer_State::MoveLimitCheck(const EAniState_Move& ChangeState)
{
	if(CheckFunction.ChangeMove(PlayerMove,ChangeState))
	{
		PlayerMove = ChangeState;
		return true;
	}
		
	return false;
}