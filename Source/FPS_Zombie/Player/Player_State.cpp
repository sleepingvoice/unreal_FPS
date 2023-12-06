// Fill out your copyright notice in the Description page of Project Settings.


#include "Player_State.h"
#include "Player_Controller.h"

APlayer_State::APlayer_State()
{
	PlayerMove = EAniState_Move::Idle;
	PlayerWeapon = EAniState_Weapon::NoWeapon;
}

void APlayer_State::BeginPlay()
{
	AddMoveListener(PlayerMove);
}

void APlayer_State::AddMoveListener(EAniState_Move& State)
{
	ChangeMove.AddLambda([&](EAniState_Move Setstate){ State = Setstate; });
}

void APlayer_State::ChangeMoveState(EAniState_Move Value)
{
	if(ChangeMove.IsBound()) ChangeMove.Broadcast(Value);
}

void APlayer_State::AddWeaponListener(EAniState_Weapon& State)
{
	ChangeWeapon.AddLambda([&](EAniState_Weapon Setstate){ State = Setstate; });
}

void APlayer_State::ChangeWeaponState(EAniState_Weapon Value)
{
	if(ChangeWeapon.IsBound()) ChangeWeapon.Broadcast(Value);
}

void APlayer_State::AddUpperistener(EAnistate_UpperBody& State)
{
	ChangeUpper.AddLambda([&](EAnistate_UpperBody Setstate){ State = Setstate; });
}

void APlayer_State::ChangeUpperState(EAnistate_UpperBody Value)
{
	if(ChangeUpper.IsBound()) ChangeUpper.Broadcast(Value);
}

