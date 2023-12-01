// Fill out your copyright notice in the Description page of Project Settings.


#include "Player_Controller.h"
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
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}

	ChangeNormal.AddLambda([&](EAniState_Normal state){ NormalState = state; });
	ChangeNormal.AddLambda([](EAniState_Normal state){ UE_LOG(LogTemp,Log,TEXT("%d"),state) });
}

void APlayer_Controller::Tick(float DeltaSeconds)
{
	if(NormalState == EAniState_Normal::Jump) // 점프중일때
	{
		auto Movement = PlayerCharacter->GetMovementComponent()->Velocity; //떨어지는 중이면
		if(Movement.Z < 0)
		{
			ChangeNormalState(EAniState_Normal::Fall); // 상태변화
		}
	}
	
	if(NormalState == EAniState_Normal::Fall) // 떨어질때
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
	
	if(NormalState == EAniState_Normal::Idle)
	{
		ChangeNormalState(EAniState_Normal::Walk);
	}
}

void APlayer_Controller::MoveStop(const FInputActionValue& Value)
{
	if(NormalState == EAniState_Normal::Walk)
	{
		ChangeNormalState(EAniState_Normal::Idle);
	}
}


void APlayer_Controller::Look(const FInputActionValue& Value)
{
	FVector2D LookAxisVector = Value.Get<FVector2D>();
	
	GetPawn()->AddControllerYawInput(LookAxisVector.X);
	GetPawn()->AddControllerPitchInput(LookAxisVector.Y);
}

void APlayer_Controller::Jump(const FInputActionValue& Value)
{
	PlayerCharacter -> Jump();
	if(NormalState != EAniState_Normal::Jump)
	{
		ChangeNormal.Broadcast(EAniState_Normal::Jump);
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


void APlayer_Controller::AddChangeListener(EAniState_Normal& State)
{
	ChangeNormal.AddLambda([&](EAniState_Normal state){ State = state; });
}

void APlayer_Controller::ChangeNormalState(EAniState_Normal Value)
{
	ChangeNormal.Broadcast(Value);
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
		ChangeNormalState(EAniState_Normal::Idle);
	}
}
