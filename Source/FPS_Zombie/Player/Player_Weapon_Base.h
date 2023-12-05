// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Player_Weapon_Base.generated.h"

UCLASS()
class FPS_ZOMBIE_API APlayer_Weapon_Base : public AActor
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category= "AttachPos")
	FVector TargetPos;

	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category= "AttachPos")
	FRotator TargetRotate;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Mesh")
	TObjectPtr<USkeletalMeshComponent> MeshComponent;
	
public:	
	// Sets default values for this actor's properties
	APlayer_Weapon_Base();

	void SetPos();

	
};
