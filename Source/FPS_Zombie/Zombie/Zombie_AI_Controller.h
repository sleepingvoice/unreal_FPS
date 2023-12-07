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
	bool CheckMove;

	UPROPERTY(EditAnywhere,Blueprintable,Category="AI")
	float DitanceLimit;
	
	// 블랙보드 값
	static const FName Key_LimitDistance;
	static const FName Key_PlayerActor;
	
private:
	UPROPERTY()
	APlayerController* MonsterCon;

	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="AI",meta=(AllowPrivateAccess="true"))
	class UBehaviorTree* BTAsset;

public:
	UPROPERTY(EditAnywhere,Blueprintable,Category="AI")
	TArray<int32> TargetNum;
private:
	AZombie_AI_Controller();
	
	virtual void OnPossess(APawn* InPawn) override;
	
	void RunAI();

	virtual void OnMoveCompleted(FAIRequestID RequestID, EPathFollowingResult::Type Result) override;

	UFUNCTION(Blueprintable)
	void OnPawnDetected(const TArray<AActor*>& DetectedPawns);
};
