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

public:
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category= "Weapon")
	FName WeaponSocketName;

	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="Weapon")
	TArray<TSubclassOf<class APlayer_Weapon_Base>> TargetWeaponArr;

	AActor* BeforeActor = nullptr;
private:
	TMap<EAniState_Weapon,AActor*> WeaponActorMap;
	


	EAniState_Weapon WeaponState = EAniState_Weapon::NoWeapon;
private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FollowCamera;

	int CheckWeapon = -1;
public:
	APlayer_Character();

	UFUNCTION(BlueprintCallable)
	void AttachWeapon(int WeaponArrNum);
};
