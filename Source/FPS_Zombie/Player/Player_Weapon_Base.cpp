// Fill out your copyright notice in the Description page of Project Settings.


#include "Player_Weapon_Base.h"

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
	MuzzleComponent->Deactivate();
}



void APlayer_Weapon_Base::SetPos()
{
	this->SetActorRelativeLocation(TargetPos);
	this->SetActorRelativeRotation(TargetRotate);
}

void APlayer_Weapon_Base::Shot(ACharacter* ShotCharacter)
{
	if(MuzzleComponent && !MuzzleComponent->IsActive()) MuzzleComponent->Activate();

	if(SparksEffect)
	{
		FVector StartPos = MeshComponent->GetSocketLocation(BoneName);
		FVector FinishPos = StartPos + ShotCharacter->GetActorForwardVector() * AttackRange;
	
		FHitResult HitResult;
		FCollisionQueryParams Params = FCollisionQueryParams::DefaultQueryParam;
		Params.AddIgnoredActor(ShotCharacter);
	
		if(GetWorld()->LineTraceSingleByChannel(HitResult,StartPos,FinishPos,ECC_PhysicsBody, Params))
		{
			UNiagaraFunctionLibrary::SpawnSystemAtLocation
			(
				GetWorld(),
				SparksEffect,
				HitResult.ImpactPoint + EffectPlusVec
				);

			//디버그용
			//DrawDebugLine(GetWorld(), StartPos, HitResult.Location, FColor::Green, false,2.0f);
		}
		else
		{
			//디버그용
			//DrawDebugLine(GetWorld(), StartPos, FinishPos, FColor::Red, false, 2.0f);
		}
	}
}



void APlayer_Weapon_Base::NoShot()
{
	if(MuzzleComponent&&MuzzleComponent->IsActive()) MuzzleComponent->Deactivate();
}