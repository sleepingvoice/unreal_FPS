#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Player_Weapon_Base.h"
#include "Player_Enum.h"
#include "Player_State.h"
#include "InputActionValue.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "FPS_Zombie/Default/Player_Widget.h"

#include "Player_Character.generated.h"

USTRUCT(Atomic,BlueprintType)
struct FState
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	float Hp;

	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	float Damge;

	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	UClass* PlayerCharacter;
};


UCLASS()
class FPS_ZOMBIE_API APlayer_Character : public ACharacter
{
	GENERATED_BODY()

private:
	UPROPERTY()
	EAniState_Weapon WeaponState = EAniState_Weapon::NoWeapon;

	UPROPERTY()
	EAniState_Move MoveState = EAniState_Move::Idle;

	UPROPERTY()
	EAnistate_UpperBody UpperState = EAnistate_UpperBody::Normal;

	UPROPERTY()
	bool Zoom = false;
	
	int CheckWeapon = -1;

	FTimerHandle ShotTimer;
public:
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category= "Weapon")
	FName WeaponSocketName;

	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="Weapon")
	TArray<TSubclassOf<class APlayer_Weapon_Base>> TargetWeaponArr;

	UPROPERTY(EditAnywhere,Category="Weapon")
	FVector3d ZoomSocket;

	UPROPERTY(EditAnywhere,Category="Weapon")
	FVector3d NormalSocket;

	UPROPERTY(EditAnywhere,Category="Weapon")
	float ZoomArmLength;

	UPROPERTY(EditAnywhere,Category="Weapon")
	float NormalArmLength;
	
	APlayer_Weapon_Base* BeforeActor = nullptr;

	UPROPERTY(EditAnywhere,Category="PlayerState")
	FState NowPlayerState;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FollowCamera;

#pragma region 입력 변수
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* DefaultMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	UInputAction* Input_Jump;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	UInputAction* Input_Move;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	UInputAction* Input_Look;

	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="Input", meta = (AllowPrivateAccess = "true"))
	UInputAction* Input_LeftClick;

	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="Input", meta = (AllowPrivateAccess = "true"))
	UInputAction* Input_RightClick;

	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="Input", meta = (AllowPrivateAccess = "true"))
	UInputAction* Input_Knife;

	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="Input", meta = (AllowPrivateAccess = "true"))
	UInputAction* Input_Pistol;

	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="Input", meta = (AllowPrivateAccess = "true"))
	UInputAction* Input_Rifle;

	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category=Animation,meta=(AllowPrivateAccess="true"))
	float DownDis;
	
#pragma endregion 입력 변수

	UPROPERTY()
	UPlayer_Widget* PlayerUI;
	
	
private:
	
#pragma region 입력 함수
	
	void Move(const FInputActionValue& Value);

	void MoveStop(const FInputActionValue& Value);
	
	void Look(const FInputActionValue& Value);

	void JumpAct(const FInputActionValue& Value);

	void LeftClick(const FInputActionValue& Value);

	void LeftClickStop(const FInputActionValue& Value);

	void RightClick(const FInputActionValue& Value);
	
	void WeaponChange(const FInputActionValue& Value,int32 IWeaponValue);
	
	void CheckJump();

	void ChangeZoom(bool On);
	
#pragma endregion 입력 함수

	FVector GetMouseRayStart(UImage* ImageObj);
	
	UPlayer_Widget* GetPlayerUI();

	void ShotCheck(FVector StartPos);
	
	virtual void Tick(float DeltaSeconds) override;
public:
	APlayer_Character();

	virtual void BeginPlay() override;

	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
	
	UFUNCTION(BlueprintCallable)
	void AttachWeapon(int WeaponArrNum);
	
};
