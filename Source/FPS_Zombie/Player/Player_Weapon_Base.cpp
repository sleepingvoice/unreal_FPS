// Fill out your copyright notice in the Description page of Project Settings.


#include "Player_Weapon_Base.h"
#include "Components/SphereComponent.h"
#include "Engine/SkeletalMeshSocket.h"

const USkeletalMeshSocket* WeaponSocket = nullptr;

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
	MuzzleComponent->Deactivate();
}



void APlayer_Weapon_Base::SetPos()
{
	this->SetActorRelativeLocation(TargetPos);
	this->SetActorRelativeRotation(TargetRotate);
}

FTimerHandle GravityTimerHandle;
float GravityTime = .1f;

void APlayer_Weapon_Base::Shot()
{
	MuzzleComponent->Activate();
}

void APlayer_Weapon_Base::NoShot()
{
	MuzzleComponent->Deactivate();
}