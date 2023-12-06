#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"
#include "Player_Weapon_Base.generated.h"

UCLASS()
class FPS_ZOMBIE_API APlayer_Weapon_Base : public AActor
{
	GENERATED_BODY()

private:
	
public:
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category= "AttachPos")
	FVector TargetPos;

	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category= "AttachPos")
	FRotator TargetRotate;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Mesh")
	USkeletalMeshComponent* MeshComponent;

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category="Effect")
	UNiagaraComponent* MuzzleComponent;
	
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="Effect")
	FName BoneName;

	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="Effect")
	UNiagaraSystem* SparksEffect;
	
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="Effect")
	FVector EffectPlusVec;

	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="Weapon")
	float AttackRange;

	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="Weapon")
	float CheckAttackTime;


private:
	virtual void BeginPlay() override;
	
public:	
	// Sets default values for this actor's properties
	APlayer_Weapon_Base();

	void SetPos();

	UFUNCTION()
	void Shot(ACharacter* ShotCharacter);

	UFUNCTION()
	void NoShot();
	
};
