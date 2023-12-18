#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Player_Weapon_Base.h"
#include "Player_Enum.h"
#include "Player_State.h"
#include "Player_Character.generated.h"

UCLASS()
class FPS_ZOMBIE_API APlayer_Character : public ACharacter
{
	GENERATED_BODY()

private:
	EAniState_Weapon WeaponState = EAniState_Weapon::NoWeapon;

	
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
	
	AActor* BeforeActor = nullptr;

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FollowCamera;

	int CheckWeapon = -1;
public:
	APlayer_Character();

	virtual void BeginPlay() override;
	
	UFUNCTION(BlueprintCallable)
	void AttachWeapon(int WeaponArrNum);

	UFUNCTION(BlueprintCallable)
	void SetZoom(bool Active);
	
};
