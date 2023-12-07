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
	UPROPERTY()
	bool MoveZombie = false;

	UPROPERTY()
	bool DetectePlayer = false;

	UPROPERTY()
	bool PlayerFollow = false;

	UPROPERTY()
	float MoveTargetRange = 0;

	
private:
	AZombie_Character();

	
};
