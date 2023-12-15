// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Zombie_AI_Controller.h"
#include "GameFramework/Character.h"
#include "Zombie_Enum.h"
#include "BehaviorTree/BehaviorTree.h"
#include "Zombie_Character.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FMulti_ZombieAiState,EZombieAIstate);

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

	UPROPERTY(EditAnywhere,Blueprintable,Category = "AI")
	TArray<UBehaviorTree*> BTAssets;
	
private:
	UPROPERTY()
	EZombieAIstate AIstate = EZombieAIstate::Idle;

	FMulti_ZombieAiState dZombieAIState;

	UPROPERTY()
	AZombie_AI_Controller* AiCon;

public:
	void AddStateListener(TFunction<void(EZombieAIstate state)> Lambda);

	UFUNCTION(BlueprintType)
	void SetStateValue(EZombieAIstate Value);
	
private:
	AZombie_Character();
	
	virtual  void BeginPlay() override;
};
