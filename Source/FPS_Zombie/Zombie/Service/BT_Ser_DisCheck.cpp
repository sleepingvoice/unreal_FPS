// Fill out your copyright notice in the Description page of Project Settings.


#include "BT_Ser_DisCheck.h"
#include "../Zombie_AI_Controller.h"
#include "../Zombie_Character.h"
#include "Kismet/GameplayStatics.h"

UBT_Ser_DisCheck::UBT_Ser_DisCheck()
{
	NodeName = "PlayerDisCheck";
}

void UBT_Ser_DisCheck::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
	
	AActor* PlayerActor = Cast<AActor>(UGameplayStatics::GetPlayerCharacter(GetWorld(),0));
	if(PlayerActor == nullptr) return;
	
	APawn* ControllingPawn = OwnerComp.GetAIOwner()->GetPawn();
	if(ControllingPawn == nullptr) return;
	
	AZombie_AI_Controller* AICon = Cast<AZombie_AI_Controller>(ControllingPawn->GetController());
	if (AICon == nullptr) return;
	
	AZombie_Character* ZombiChar = Cast<AZombie_Character>(ControllingPawn);
	if(ZombiChar == nullptr) return;
	
	float DistancePlayer = ControllingPawn->GetDistanceTo(PlayerActor);
	
	if(ZombiChar->bChasingPlayer) //멀어지면 안쫒아가게 되어있는 경우
	{
		if(DistancePlayer > AICon->fFindDitanceLimit) // 플레이어까지의 거리가 멀때
		{
			UE_LOG(LogTemp,Log,TEXT("멀어짐"));
			AICon->bChasingPlayer = false;
			AICon->bPlayerFind = false;
		}
		else
		{
			AICon->bChasingPlayer = true;
		}
	}

	if(ZombiChar->bChasingLand) // 일정범위이상 이동안하게 되어있을때
	{
		float DistanceSpawnPoint = FVector::Dist(ControllingPawn->GetActorLocation(),ZombiChar->vPlayerSpawnLocation);
		float SpawnpointLimit = AICon->fFindDitanceLimit + AICon->fRandomFindLength;
		if(SpawnpointLimit < DistanceSpawnPoint) // 한계거리보다 멀리 갔을때
		{
			AICon->bChasingLand = false;
			AICon->bPlayerFind = false;
		}
		else
		{
			AICon->bChasingPlayer = true;
		}
	}

}

