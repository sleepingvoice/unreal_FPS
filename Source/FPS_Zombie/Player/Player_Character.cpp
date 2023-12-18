
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
	CameraBoom->bUsePawnControlRotation = true; 
	
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;

	auto state = Cast<APlayer_State>(GetPlayerState());
	if(state)
	{
		state->AddWeaponListener(WeaponState);
	}
}

void APlayer_Character::BeginPlay()
{
	Super::BeginPlay();
	CameraBoom->SocketOffset = NormalSocket;
	CameraBoom->TargetArmLength = NormalArmLength;
}


void APlayer_Character::AttachWeapon(int WeaponArrNum) 
{
	EAniState_Weapon TargetState = (EAniState_Weapon)(WeaponArrNum +1);
	
	if(WeaponState!=TargetState && TargetState > EAniState_Weapon::NoWeapon)
	{
		
		if(BeforeActor) BeforeActor->Destroy();
		
		CheckWeapon = WeaponArrNum;
		
		if(WeaponArrNum < TargetWeaponArr.Num())
		{
			APlayer_Weapon_Base* SpawnWeapon = GetWorld()->SpawnActor<APlayer_Weapon_Base>(TargetWeaponArr[WeaponArrNum]);
			SpawnWeapon->InitState(WeaponArrNum+1,Cast<APlayer_State>(GetPlayerState()));
		
			const USkeletalMeshSocket* WeaponSocket = GetMesh()->GetSocketByName(WeaponSocketName);
		
			if(WeaponSocket)
			{
				WeaponSocket->AttachActor(SpawnWeapon,GetMesh());
				Cast<APlayer_Weapon_Base>(SpawnWeapon)->SetPos();
				Cast<APlayer_State>(GetPlayerState())->ChangeWeaponState(TargetState);
				BeforeActor = SpawnWeapon;
			}
		}
	}
	else if(TargetState == EAniState_Weapon::NoWeapon)
	{
		if(BeforeActor) BeforeActor->SetActorHiddenInGame(true);
		Cast<APlayer_State>(GetPlayerState())->ChangeWeaponState(TargetState);
	}
}

void APlayer_Character::SetZoom(bool Active)
{
	if(Active)
	{
		CameraBoom->SocketOffset = ZoomSocket;
		CameraBoom->TargetArmLength = ZoomArmLength;
	}
	else
	{
		CameraBoom->SocketOffset = NormalSocket;
		CameraBoom->TargetArmLength = NormalArmLength;
	}
}



