// Fill out your copyright notice in the Description page of Project Settings.


#include "Player_Controller.h"

#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PawnMovementComponent.h"

void APlayer_Controller::SetupInputComponent()
{
	Super::SetupInputComponent();

	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent))
	{
		EnhancedInputComponent->BindAction(Input_Jump, ETriggerEvent::Started, this, &APlayer_Controller::Jump);
		EnhancedInputComponent->BindAction(Input_Jump, ETriggerEvent::Completed, this, &APlayer_Controller::JumpStop);
		
		EnhancedInputComponent->BindAction(Input_Move, ETriggerEvent::Triggered, this, &APlayer_Controller::Move);
		EnhancedInputComponent->BindAction(Input_Move, ETriggerEvent::Completed, this, &APlayer_Controller::MoveStop);
		
		EnhancedInputComponent->BindAction(Input_Look, ETriggerEvent::Triggered, this, &APlayer_Controller::Look);

		EnhancedInputComponent->BindAction(Input_LeftClick, ETriggerEvent::Triggered, this, &APlayer_Controller::LeftClick);
		EnhancedInputComponent->BindAction(Input_RightClick, ETriggerEvent::Triggered, this, &APlayer_Controller::RightClick);

		EnhancedInputComponent->BindAction(Input_Knife,ETriggerEvent::Triggered,this,&APlayer_Controller::KinfeHold);
		EnhancedInputComponent->BindAction(Input_Pistol,ETriggerEvent::Triggered,this,&APlayer_Controller::PistolHold);
		EnhancedInputComponent->BindAction(Input_Rifle,ETriggerEvent::Triggered,this,&APlayer_Controller::RifleHold);
	}
}

void APlayer_Controller::BeginPlay()
{
	Super::BeginPlay();

	PlayerCharacter = Cast<APlayer_Character>(GetPawn());
	if (APlayerController* PlayerController = Cast<APlayerController>(GetPawn()->Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			UE_LOG(LogTemp,Log,TEXT("이건가?"));
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}

	PlayCharacterState = Cast<APlayer_State>(GetPawn()->GetPlayerState());
	if(PlayCharacterState)
	{
		PlayCharacterState->AddMoveListener(MoveState);
		PlayCharacterState->AddWeaponListener(WeaponState);
	}
}

void APlayer_Controller::Tick(float DeltaSeconds)
{
	if(MoveState == EAniState_Move::Jump) // 점프중일때
	{
		auto Movement = PlayerCharacter->GetMovementComponent()->Velocity; //떨어지는 중이면
		if(Movement.Z < 0)
		{
			PlayCharacterState->ChangeMoveState(EAniState_Move::Fall); // 상태변화
		}
	}
	
	if(MoveState == EAniState_Move::Fall) // 떨어질때
	{
		CheckJump();
	}
}



void APlayer_Controller::Move(const FInputActionValue& Value)
{
	FVector2D MovementVector = Value.Get<FVector2D>();
	
	const FRotator Rotation = this->GetControlRotation();
	const FRotator YawRotation(0, Rotation.Yaw, 0);
	
	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
	
	GetPawn()->AddMovementInput(ForwardDirection, MovementVector.Y);
	GetPawn()->AddMovementInput(RightDirection, MovementVector.X);
	
	if(MoveState == EAniState_Move::Idle)
	{
		PlayCharacterState->ChangeMoveState(EAniState_Move::Walk);
	}
}

void APlayer_Controller::MoveStop(const FInputActionValue& Value)
{
	if(MoveState == EAniState_Move::Walk)
	{
		PlayCharacterState->ChangeMoveState(EAniState_Move::Idle);
	}
}


void APlayer_Controller::Look(const FInputActionValue& Value)
{
	FVector2D LookAxisVector = Value.Get<FVector2D>();
	
	GetPawn()->AddControllerYawInput(LookAxisVector.X);
	GetPawn()->AddControllerPitchInput(LookAxisVector.Y);
}

float MoveSpeed = 0;
void APlayer_Controller::Jump(const FInputActionValue& Value)
{
	PlayerCharacter -> Jump();
	if(MoveState != EAniState_Move::Jump)
	{
		MoveSpeed = PlayerCharacter->GetCharacterMovement()->MaxWalkSpeed;
		PlayerCharacter->GetCharacterMovement()->MaxWalkSpeed = MoveSpeed/2;
		PlayCharacterState->ChangeMoveState(EAniState_Move::Jump);
	}
}

void APlayer_Controller::JumpStop(const FInputActionValue& Value)
{
	PlayerCharacter -> StopJumping();
}


void APlayer_Controller::LeftClick(const FInputActionValue& Value)
{
	
}

void APlayer_Controller::RightClick(const FInputActionValue& Value)
{
	
}

void APlayer_Controller::KinfeHold(const FInputActionValue& Value)
{
	PlayerCharacter->AttachWeapon(0);
}

void APlayer_Controller::PistolHold(const FInputActionValue& Value)
{
	PlayerCharacter->AttachWeapon(1);
}


void APlayer_Controller::RifleHold(const FInputActionValue& Value)
{
	PlayerCharacter->AttachWeapon(2);
}

void APlayer_Controller::CheckJump()
{
	FHitResult HitResult;
	FCollisionQueryParams Params = FCollisionQueryParams::DefaultQueryParam;
	Params.AddIgnoredActor(PlayerCharacter);

	FVector DownVector = PlayerCharacter->GetActorLocation() - PlayerCharacter->GetActorUpVector();

	FVector Start = PlayerCharacter->GetActorLocation();
	FVector End = PlayerCharacter->GetActorLocation() - PlayerCharacter->GetActorUpVector() * DownDis;
	
	bool bResult = GetWorld()->LineTraceSingleByChannel(OUT HitResult,Start,End,ECC_PhysicsBody,Params);
	
	if(bResult)
	{
		PlayerCharacter->GetCharacterMovement()->MaxWalkSpeed = MoveSpeed;
		PlayCharacterState->ChangeMoveState(EAniState_Move::Idle);
	}
}
