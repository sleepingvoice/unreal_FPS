// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Zombie_AI_Controller.generated.h"


UCLASS()
class FPS_ZOMBIE_API AZombie_AI_Controller : public AAIController
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere,Blueprintable,Category="AI")
	float fRandomFindLength;
	
	UPROPERTY(EditAnywhere,Blueprintable,Category="AI")
	float fFindDitanceLimit;

	UPROPERTY(EditAnywhere,Blueprintable,Category="AI")
	float fAttackDistanceLimit;

	//좀비가 이동중인지 체크
	UPROPERTY()
	bool bMoveZombie = false;
	
	//플레이어를 공격가능한지 확인
    UPROPERTY()
	bool bAttackPlayer = false;

	//플레이어를 찾았는지 확인
	UPROPERTY()
	bool bPlayerFind = false;
	
	//플레이어를 공격가능한 범위인지 확인
	UPROPERTY()
	bool bAttackDis = false;

	//플레이어를 쫒아갈수있는지 확인 
	UPROPERTY()
	bool bChasingPlayer = false;

	//스폰지점으로부터 플레이어를 쫒아가도 되는지 확인
	UPROPERTY()
	bool bChasingLand = false;

	UPROPERTY()
	ACharacter* PlayerCharacter;
	
	// 블랙보드 값
	static const FName Key_LimitDistance;
	static const FName Key_PlayerActor;
	
private:
	UPROPERTY()
	APlayerController* MonsterCon;

	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="AI",meta=(AllowPrivateAccess="true"))
	UBehaviorTree* BTAsset;
public:
	bool CanChasing();

	void RunAI(UBehaviorTree* btAsset);

	virtual void OnPossess(APawn* InPawn) override;
	
private:
	AZombie_AI_Controller();

	virtual void BeginPlay() override;
	
	virtual void OnMoveCompleted(FAIRequestID RequestID, EPathFollowingResult::Type Result) override;

	UFUNCTION(Blueprintable)
	void OnPawnDetected(const TArray<AActor*>& DetectedPawns);
	
};
