// Fill out your copyright notice in the Description page of Project Settings.


#include "Player_Weapon_Base.h"
#include "GameFramework/Character.h"

APlayer_Weapon_Base::APlayer_Weapon_Base()
{
	PrimaryActorTick.bCanEverTick = true;
	
	MeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(FName("WeaponMesh"));
	MuzzleComponent = CreateDefaultSubobject<UNiagaraComponent>(FName("Muzzle"));
	
	SetRootComponent(MeshComponent);
	MuzzleComponent->SetupAttachment(MeshComponent);
}

void APlayer_Weapon_Base::BeginPlay()
{
	Super::BeginPlay();
	MuzzleComponent->Deactivate();
}

void APlayer_Weapon_Base::SetPos()
{
	this->SetActorRelativeLocation(TargetPos);
	this->SetActorRelativeRotation(TargetRotate);
}

// 사격 시작
void APlayer_Weapon_Base::ShotStart(ACharacter* ShotCharacter)
{
	if(MuzzleComponent && !MuzzleComponent->IsActive()) MuzzleComponent->Activate();
}

// 사격 종료
void APlayer_Weapon_Base::ShotStop()
{
	if(MuzzleComponent&&MuzzleComponent->IsActive()) MuzzleComponent->Deactivate();
}

void APlayer_Weapon_Base::ShotEffect(FVector EffectLocation)
{
	UNiagaraFunctionLibrary::SpawnSystemAtLocation
	(
		GetWorld(),
		HitEffect,
		EffectLocation + HitPlusVec
		);
}

