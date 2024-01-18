// Fill out your copyright notice in the Description page of Project Settings.


#include "Player_Weapon_Base.h"

#include "Player_Character.h"
#include "GameFramework/Character.h"

// Sets default values
APlayer_Weapon_Base::APlayer_Weapon_Base()
{
	PrimaryActorTick.bCanEverTick = true;
	
	MeshComponent=CreateDefaultSubobject<USkeletalMeshComponent>(FName("WeaponMesh"));

	MuzzleComponent = CreateDefaultSubobject<UNiagaraComponent>(FName("Muzzle"));
	
	SetRootComponent(MeshComponent);
	MuzzleComponent->SetupAttachment(MeshComponent);
}

void APlayer_Weapon_Base::BeginPlay()
{
	Super::BeginPlay();
	MuzzleComponent->Deactivate();
}

float Checktime = 0.f;

void APlayer_Weapon_Base::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if(SetWeapon != NowWeapon && NowWeapon != EAniState_Weapon::RifleZoom) return;

	if(B_Fire) return;
	
	Checktime += DeltaSeconds;
	
	if(Checktime > WeaponDelay)
	{
		Checktime = 0;
		B_Fire = true;
	}
}

void APlayer_Weapon_Base::InitState(int value,APlayer_State* state)
{
	SetWeapon = (EAniState_Weapon)value;
	state->AddWeaponListener(NowWeapon);
}

void APlayer_Weapon_Base::SetPos()
{
	this->SetActorRelativeLocation(TargetPos);
	this->SetActorRelativeRotation(TargetRotate);
}

void APlayer_Weapon_Base::Shot(ACharacter* ShotCharacter)
{
	if(MuzzleComponent && !MuzzleComponent->IsActive()) MuzzleComponent->Activate();
	A_ShotCharacter = ShotCharacter;
	B_Fire = false;
}

void APlayer_Weapon_Base::NoShot()
{
	if(MuzzleComponent&&MuzzleComponent->IsActive()) MuzzleComponent->Deactivate();
	B_Fire = true;
}

void APlayer_Weapon_Base::ShotEffect(FVector EffectLocation)
{
	UNiagaraFunctionLibrary::SpawnSystemAtLocation
	(
		GetWorld(),
		SparksEffect,
		EffectLocation + EffectPlusVec
		);
}
