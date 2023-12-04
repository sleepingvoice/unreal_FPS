// Fill out your copyright notice in the Description page of Project Settings.


#include "Player_Character.h"

#include "Components/BoxComponent.h"
#include "Components/CapsuleComponent.h"
#include "Engine/SkeletalMeshSocket.h"
#include "GameFramework/CharacterMovementComponent.h"


// Sets default values
APlayer_Character::APlayer_Character()
{
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;
	
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f); // ...at this rotation rate

	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
	GetCharacterMovement()->BrakingDecelerationFalling = 1500.0f;
	
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 300.0f; // The camera follows at this distance behind the character
	CameraBoom->SocketOffset = FVector(0,0,200);
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller
	
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm
}

void APlayer_Character::AttachWeapon(TSubclassOf<APlayer_Weapon_Base> Weapon) const
{
	if(Weapon)
	{
		AActor* SpawnWeapon = GetWorld()->SpawnActor<APlayer_Weapon_Base>(Weapon);
		
		const USkeletalMeshSocket* WeaponSocket = GetMesh()->GetSocketByName(WeaponSocketName);
		
		if(WeaponSocket && SpawnWeapon)
		{
			WeaponSocket->AttachActor(SpawnWeapon,GetMesh());
		}
	}
}

void APlayer_Character::BeginPlay()
{
	Super::BeginPlay();
}

