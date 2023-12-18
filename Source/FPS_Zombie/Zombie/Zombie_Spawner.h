// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Zombie_Character.h"
#include "Components/SphereComponent.h"
#include "GameFramework/Actor.h"
#include "Zombie_Spawner.generated.h"

USTRUCT(Atomic,BlueprintType)
struct FMonsterSpawnType
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	FString KeyValue;
	
	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	float Hp;

	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	float Damge;

	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	UClass* ZombieCharacter;
};

UCLASS()
class FPS_ZOMBIE_API AZombie_Spawner : public AActor
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	TArray<FMonsterSpawnType> SpawnTypeArr;

	UPROPERTY()
	float SpawnRange;

	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	USphereComponent* DebugSphere;

	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	float SpawnValue;

private:
	virtual void BeginPlay() override;

	void SpawnMonster(FMonsterSpawnType SpawnType);

	FVector GetCollisionPointBelowLocation(const FVector& StartLocation);
public:	
	AZombie_Spawner();
};
