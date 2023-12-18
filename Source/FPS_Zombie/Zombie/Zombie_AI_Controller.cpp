// Fill out your copyright notice in the Description page of Project Settings.


#include "Zombie_AI_Controller.h"
#include "Zombie_Character.h"
#include "Kismet/GameplayStatics.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"

const FName AZombie_AI_Controller::Key_LimitDistance(TEXT("DistanceLimit"));
const FName AZombie_AI_Controller::Key_PlayerActor(TEXT("PlayerActor"));

AZombie_AI_Controller::AZombie_AI_Controller()
{
	MonsterCon = Cast<APlayerController>(GetPawn());
	
	SetPerceptionComponent(*CreateOptionalDefaultSubobject<UAIPerceptionComponent>(TEXT("AIPerception")));

	GetPerceptionComponent()->OnPerceptionUpdated.AddDynamic(this, &AZombie_AI_Controller::OnPawnDetected);
	
}

void AZombie_AI_Controller::BeginPlay()
{
	Super::BeginPlay();
}



void AZombie_AI_Controller::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	
	RunAI();
}


void AZombie_AI_Controller::RunAI()
{
	if(BTAsset!=nullptr)
	{
		RunBehaviorTree(BTAsset);
	}
}

void AZombie_AI_Controller::OnMoveCompleted(FAIRequestID RequestID, EPathFollowingResult::Type Result)
{
	Super::OnMoveCompleted(RequestID, Result);
	bMoveZombie = false;
}

void AZombie_AI_Controller::OnPawnDetected(const TArray<AActor*>& DetectedPawns)
{
	for(int i = 0;i<DetectedPawns.Num();i++)
	{
		if(DetectedPawns[i] == Cast<AActor>(UGameplayStatics::GetPlayerCharacter(GetWorld(),0)))
		{
			bPlayerFind = true;
			PlayerCharacter = Cast<ACharacter>(DetectedPawns[i]);
		}
		return;
	}
}


bool AZombie_AI_Controller::CanChasing()
{
	auto player =Cast<AZombie_Character>(GetPawn());
	if(!player) return false;
	if(player->bChasingPlayer && !bChasingPlayer) return false;
	if(player->bChasingLand && !bChasingLand) return false;
	return bPlayerFind;
}
