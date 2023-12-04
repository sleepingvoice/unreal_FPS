// Fill out your copyright notice in the Description page of Project Settings.


#include "Player_Weapon_Base.h"
#include "Components/SphereComponent.h"

// Sets default values
APlayer_Weapon_Base::APlayer_Weapon_Base()
{
	PrimaryActorTick.bCanEverTick = true;
	
	MeshComponent=CreateDefaultSubobject<USkeletalMeshComponent>(FName("WeaponMesh"));
	RootComponent = MeshComponent;
}
