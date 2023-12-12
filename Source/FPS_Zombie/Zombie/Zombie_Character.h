// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Zombie_Character.generated.h"

UCLASS()
class FPS_ZOMBIE_API AZombie_Character : public ACharacter
{
	GENERATED_BODY()
public:
	//플레이어와 일정거리 이상 멀어질시 쫒아갈것인지?
	UPROPERTY(EditAnywhere,Blueprintable,Category="AI") 
	bool bChasingPlayer;

	//생성지점과 일정거리 이상 멀어질시 쫒아갈것인지?
	UPROPERTY(EditAnywhere,Blueprintable,Category="AI")
	bool bChasingLand;


	UPROPERTY()
	float fMoveTargetRange = 0;

	UPROPERTY()
	FVector3d vPlayerSpawnLocation;
	
private:
	AZombie_Character();

	
};
