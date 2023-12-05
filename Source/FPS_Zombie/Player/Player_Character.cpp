
#include "Player_Character.h"
#include "Components/CapsuleComponent.h"
#include "Engine/SkeletalMeshSocket.h"
#include "GameFramework/CharacterMovementComponent.h"



APlayer_Character::APlayer_Character()
{
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;
	
	GetCharacterMovement()->bOrientRotationToMovement = true; 	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f); 


	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
	GetCharacterMovement()->BrakingDecelerationFalling = 1500.0f;
	
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 300.0f; 
	CameraBoom->SocketOffset = FVector(0,0,200);
	CameraBoom->bUsePawnControlRotation = true; 
	
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;
}

void APlayer_Character::AttachWeapon(int WeaponArrNum) 
{
	if(TargetWeaponArr.Num() > WeaponArrNum && CheckWeapon!=WeaponArrNum)
	{
		if(BeforeActor)
		{
			BeforeActor->SetActorHiddenInGame(true);
		}
		
		CheckWeapon = WeaponArrNum;

		EAniState_Weapon TargetState = (EAniState_Weapon)(WeaponArrNum +1);
		
		if(!WeaponActorMap.Contains(TargetState))
		{
			AActor* SpawnWeapon = GetWorld()->SpawnActor<APlayer_Weapon_Base>(TargetWeaponArr[WeaponArrNum]);
			WeaponActorMap.Add(TargetState,SpawnWeapon);
		}
		
		const USkeletalMeshSocket* WeaponSocket = GetMesh()->GetSocketByName(WeaponSocketName);
		
		if(WeaponSocket && WeaponActorMap.Contains(TargetState))
		{
			WeaponSocket->AttachActor(WeaponActorMap[TargetState],GetMesh());
			Cast<APlayer_Weapon_Base>(WeaponActorMap[TargetState])->SetPos();
			Cast<APlayer_State>(GetPlayerState())->ChangeWeaponState(TargetState);
			WeaponActorMap[TargetState]->SetActorHiddenInGame(false);
			BeforeActor = WeaponActorMap[TargetState];
		}


	}
}


