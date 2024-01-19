#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"
#include "Player_Enum.h"
#include "Player_Weapon_Base.generated.h"

UCLASS()
class FPS_ZOMBIE_API APlayer_Weapon_Base : public AActor
{
	GENERATED_BODY()

	//변수
private:
	
public:
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category= "Attach")
	FVector TargetPos;

	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category= "Attach")
	FRotator TargetRotate;

	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category= "Attach")
	EAniState_Weapon TargetWeapon;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Mesh")
	USkeletalMeshComponent* MeshComponent;

	UPROPERTY(EditAnywhere,Category="Weapon")
	float AttackDelay;
	
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category="Effect")
	UNiagaraComponent* MuzzleComponent;
	
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="Effect")
	UNiagaraSystem* HitEffect;
	
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="Effect")
	FVector HitPlusVec; // 이펙트 보정 값

	//함수
private:
	virtual void BeginPlay() override;
	
public:	
	APlayer_Weapon_Base();

	void SetPos();

	UFUNCTION()
	void ShotStart(ACharacter* ShotCharacter);

	UFUNCTION()
	void ShotStop();

	UFUNCTION()
	void ShotEffect(FVector EffectLocation);
};
