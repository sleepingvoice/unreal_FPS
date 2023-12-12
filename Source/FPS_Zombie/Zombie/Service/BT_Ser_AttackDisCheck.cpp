// Fill out your copyright notice in the Description page of Project Settings.


#include "BT_Ser_AttackDisCheck.h"
#include "../Zombie_AI_Controller.h"
#include "../Zombie_Character.h"
#include "Kismet/GameplayStatics.h"

UBT_Ser_AttackDisCheck::UBT_Ser_AttackDisCheck()
{
	
}

void UBT_Ser_AttackDisCheck::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	AActor* PlayerActor = Cast<AActor>(UGameplayStatics::GetPlayerCharacter(GetWorld(),0));
	if(PlayerActor == nullptr) return;
	
	APawn* ControllingPawn = OwnerComp.GetAIOwner()->GetPawn();
	if(ControllingPawn == nullptr) return;

	AZombie_AI_Controller* AICon = Cast<AZombie_AI_Controller>(ControllingPawn);
	if (AICon == nullptr) return;

	AZombie_Character* PlayerCharacter = Cast<AZombie_Character>(PlayerActor);
	if(PlayerCharacter) return;
	
	float DistancePlayer = ControllingPawn->GetDistanceTo(PlayerCharacter);

	if(DistancePlayer < AICon->fAttackDistanceLimit) // 공격 범위 안인경우
	{
		AICon->bAttackDis = true;
	}
	else
	{
		AICon->bAttackDis = false;
	}
}