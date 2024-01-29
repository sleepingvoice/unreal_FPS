
#include "Player_Character.h"

#include "Player_GameMode.h"
#include "Components/CapsuleComponent.h"
#include "Engine/SkeletalMeshSocket.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"


APlayer_Character::APlayer_Character()
{
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;
	
	GetCharacterMovement()->bOrientRotationToMovement = false; 	
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

	NowPlayerState = FState();
	NowPlayerState.Damge = 10;
	NowPlayerState.Hp = 10;
	NowPlayerState.PlayerCharacter = GetClass();
}

void APlayer_Character::BeginPlay()
{
	Super::BeginPlay();
	CameraBoom->SocketOffset = NormalSocket;
	CameraBoom->TargetArmLength = NormalArmLength;

	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}

	auto PlayCharacterState = Cast<APlayer_State>(GetPlayerState());
	if(PlayCharacterState)
	{
		PlayCharacterState->AddMoveListener([this](EAniState_Move SetState) { MoveState = SetState; });
		PlayCharacterState->AddWeaponListener([this](EAniState_Weapon SetWeapon){ WeaponState = SetWeapon;});
		PlayCharacterState->AddUpperistener([this](EAnistate_UpperBody SetUpper){UpperState = SetUpper;});
	}
}


void APlayer_Character::Tick(float DeltaSeconds)
{
	if(MoveState == EAniState_Move::Jump) // 점프중일때
	{
		auto Movement = GetMovementComponent()->Velocity; //떨어지는 중이면
		if(Movement.Z < 0)
		{
			Cast<APlayer_State>(GetPlayerState())->ChangeMoveState(EAniState_Move::Fall); // 상태변화
		}
	}
	
	if(MoveState == EAniState_Move::Fall) // 떨어질때
	{
		CheckJump();
	}

	if(PlayerUI == nullptr)
		PlayerUI = Cast<UPlayer_Widget>((Cast<APlayer_GameMode>(UGameplayStatics::GetGameMode(GetWorld())))->NowUIWidget);
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

#pragma region 입력 관련 함수

void APlayer_Character::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent))
	{
		EnhancedInputComponent->BindAction(Input_Jump, ETriggerEvent::Started, this,
			&APlayer_Character::JumpAct);
		EnhancedInputComponent->BindAction(Input_Jump, ETriggerEvent::Completed, this,
			&APlayer_Character::StopJumping);
		
		EnhancedInputComponent->BindAction(Input_Move, ETriggerEvent::Triggered, this,
			&APlayer_Character::Move);
		EnhancedInputComponent->BindAction(Input_Move, ETriggerEvent::Completed, this,
			&APlayer_Character::MoveStop);
		
		EnhancedInputComponent->BindAction(Input_Look, ETriggerEvent::Triggered, this,
			&APlayer_Character::Look);

		EnhancedInputComponent->BindAction(Input_LeftClick, ETriggerEvent::Started, this,
			&APlayer_Character::LeftClick);
		EnhancedInputComponent->BindAction(Input_LeftClick, ETriggerEvent::Completed, this,
			&APlayer_Character::LeftClickStop);
		EnhancedInputComponent->BindAction(Input_RightClick, ETriggerEvent::Started, this,
			&APlayer_Character::RightClick);

		EnhancedInputComponent->BindAction(Input_Knife,ETriggerEvent::Started,this,
			&APlayer_Character::WeaponChange,0);
		EnhancedInputComponent->BindAction(Input_Pistol,ETriggerEvent::Started,this,
			&APlayer_Character::WeaponChange,1);
		EnhancedInputComponent->BindAction(Input_Rifle,ETriggerEvent::Started,this,
			&APlayer_Character::WeaponChange,2);
	}
}


void APlayer_Character::Move(const FInputActionValue& Value)
{
	FVector2D MovementVector = Value.Get<FVector2D>();
	
	const FRotator Rotation = this->GetControlRotation();
	const FRotator YawRotation(0, Rotation.Yaw, 0);
	
	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

	AddMovementInput(GetActorForwardVector(), MovementVector.Y);
	AddMovementInput(GetActorRightVector(), MovementVector.X);
	
	Cast<APlayer_State>(GetPlayerState())->ChangeMoveState(EAniState_Move::Walk);
}

void APlayer_Character::MoveStop(const FInputActionValue& Value)
{
	Cast<APlayer_State>(GetPlayerState())->ChangeMoveState(EAniState_Move::Idle);
}


void APlayer_Character::Look(const FInputActionValue& Value)
{
	FVector2D LookAxisVector = Value.Get<FVector2D>();
	
	AddControllerYawInput(LookAxisVector.X);
}

float MoveSpeed = 0;

void APlayer_Character::JumpAct(const FInputActionValue& Value)
{
	Jump();
	Cast<APlayer_State>(GetPlayerState())->ChangeMoveState(EAniState_Move::Jump);
	
	if(MoveState != EAniState_Move::Jump)
	{
		MoveSpeed = GetCharacterMovement()->MaxWalkSpeed;
		GetCharacterMovement()->MaxWalkSpeed = MoveSpeed/2;
	}
}

void APlayer_Character::LeftClick(const FInputActionValue& Value)
{
	if(WeaponState != EAniState_Weapon::Rifle) return;

	BeforeActor->ShotStart(this);
	Cast<APlayer_State>(GetPlayerState())->ChangeUpperState(EAnistate_UpperBody::Shot);
	MoveSpeed = GetCharacterMovement()->MaxWalkSpeed;
	GetCharacterMovement()->MaxWalkSpeed = MoveSpeed*0.5f;

	
	FTimerDelegate TimerDelegate;
	TimerDelegate.BindLambda([this]()
	{
		ShotCheck(GetMouseRayStart(GetPlayerUI()->ShotImage));
	});
	
	GetWorldTimerManager().SetTimer(ShotTimer, TimerDelegate, .1f, true);
}

void APlayer_Character::LeftClickStop(const FInputActionValue& Value)
{
	if(WeaponState != EAniState_Weapon::Rifle) return;

	Cast<APlayer_Weapon_Base>(BeforeActor)->ShotStop();
	Cast<APlayer_State>(GetPlayerState())->ChangeUpperState(EAnistate_UpperBody::Normal);
	GetCharacterMovement()->MaxWalkSpeed = MoveSpeed;
	
	GetWorldTimerManager().ClearTimer(ShotTimer);
}

void APlayer_Character::RightClick(const FInputActionValue& Value)
{
	ChangeZoom(!Zoom);
}

void APlayer_Character::WeaponChange(const FInputActionValue& Value,int32 IWeaponValue)
{
	if(IWeaponValue < 3)
		AttachWeapon(IWeaponValue);
}

void APlayer_Character::CheckJump()
{
	FHitResult HitResult;
	FCollisionQueryParams Params = FCollisionQueryParams::DefaultQueryParam;
	Params.AddIgnoredActor(this);

	FVector Start = GetActorLocation();
	FVector End = GetActorLocation() - GetActorUpVector() * DownDis;
	
	bool bResult = GetWorld()->LineTraceSingleByChannel(OUT HitResult,Start,End,ECC_PhysicsBody,Params);
	
	if(bResult)
	{
		GetCharacterMovement()->MaxWalkSpeed = MoveSpeed;
		Cast<APlayer_State>(GetPlayerState())->ChangeMoveState(EAniState_Move::Idle);
	}
}


FVector APlayer_Character::GetMouseRayStart(UImage* ImageObj)
{
	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	if (!PlayerController)
		return FVector::ZeroVector;


	FGeometry geo = ImageObj->GetPaintSpaceGeometry();
	FVector2D paintPos = geo.GetAbsolutePosition();

	FVector WorldLocation, WorldDirection;
	PlayerController->DeprojectScreenPositionToWorld(paintPos.X, paintPos.Y, WorldLocation, WorldDirection);
	
	return WorldLocation;
}


#pragma endregion 입력 관련 함수


UPlayer_Widget* APlayer_Character::GetPlayerUI()
{
	if(PlayerUI == nullptr)
		PlayerUI = Cast<UPlayer_Widget>((Cast<APlayer_GameMode>(UGameplayStatics::GetGameMode(GetWorld())))->NowUIWidget);

	return PlayerUI;
}


void APlayer_Character::ShotCheck(FVector StartPos)
{
	FTransform CameraTransform = FollowCamera->GetComponentTransform();
	
	FVector CamForward = CameraTransform.GetUnitAxis(EAxis::X);
	CamForward += CameraTransform.GetLocation();
	
	FVector ActorForward = GetActorLocation()+ GetActorForwardVector();
	
	float AngleRadians = FMath::Acos(FVector::DotProduct(CamForward.GetSafeNormal(), ActorForward.GetSafeNormal()));
	
	float TangentValue = FMath::Tan(AngleRadians);
	
	float LengthOfVectorA = (FMath::IsNearlyZero(AngleRadians)) ? 0.0f : FVector::DotProduct(ActorForward, CamForward.GetSafeNormal()) / TangentValue;
	
	FHitResult HitResult;
	FCollisionQueryParams Params = FCollisionQueryParams::DefaultQueryParam;
	Params.AddIgnoredActor(this);

	//DrawDebugBox(GetWorld(),StartPos,FVector(10,10,10),FColor::Green,false,5);
	//DrawDebugBox(GetWorld(),GetActorLocation()+ GetActorForwardVector() * LengthOfVectorA,FVector(10,10,10),FColor::Red,false,5);
	
	if(GetWorld()->LineTraceSingleByChannel(HitResult,StartPos,GetActorLocation()+ GetActorForwardVector() * LengthOfVectorA,ECC_PhysicsBody, Params))
	{
		BeforeActor->ShotEffect(HitResult.Location);
		//이펙트 스폰

		//디버그용
		//DrawDebugLine(GetWorld(), StartPos, HitResult.Location, FColor::Green, false,2.0f);
	}
	else
	{
		//디버그용
		//DrawDebugLine(GetWorld(), StartPos, GetActorLocation()+ GetActorForwardVector() * LengthOfVectorA, FColor::Red, false, 2.0f);
	}
}

void APlayer_Character::ChangeZoom(bool On)
{
	if(On)
	{
		CameraBoom->SocketOffset = ZoomSocket;
		CameraBoom->TargetArmLength = ZoomArmLength;
		FollowCamera->SetRelativeRotation(FRotator(0,0,0));
		MoveSpeed = GetCharacterMovement()->MaxWalkSpeed;
		GetCharacterMovement()->MaxWalkSpeed = MoveSpeed*0.8f;
		Zoom = true;
	}
	else
	{
		CameraBoom->SocketOffset = NormalSocket;
		CameraBoom->TargetArmLength = NormalArmLength;
		FollowCamera->SetRelativeRotation(FRotator(-20,0,0));
		MoveSpeed = GetCharacterMovement()->MaxWalkSpeed;
		GetCharacterMovement()->MaxWalkSpeed = MoveSpeed;
		Zoom = false;
	}
}
