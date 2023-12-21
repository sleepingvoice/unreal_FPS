#include "BT_Task_AttackZombie.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "FPS_Zombie/Player/Player_Character.h"
#include "FPS_Zombie/Zombie/Zombie_Character.h"
#include "Kismet/GameplayStatics.h"

UBT_Task_AttackZombie::UBT_Task_AttackZombie()
{
	NodeName = TEXT("Attack");
}


EBTNodeResult::Type UBT_Task_AttackZombie::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);
	
	APawn* ControllingPawn = OwnerComp.GetAIOwner()->GetPawn();
	if(ControllingPawn == nullptr) return EBTNodeResult::Failed;
	
	AZombie_Character* ZombieCharacter = Cast<AZombie_Character>(ControllingPawn);
	if(ZombieCharacter == nullptr) return EBTNodeResult::Failed;

	AZombie_AI_Controller* ZombieCon = Cast<AZombie_AI_Controller>(OwnerComp.GetAIOwner());
	if(ZombieCon == nullptr) return EBTNodeResult::Failed;

	APlayer_Character* PlayerCharacter = Cast<APlayer_Character>(ZombieCon->PlayerCharacter);
	if(PlayerCharacter == nullptr) return EBTNodeResult::Failed;

	ZombieCharacter->SetStateValue(EZombieAIstate::Attack);
	PlayerCharacter->NowPlayerState.Hp -= ZombieCon->GetBlackboardComponent()->GetValueAsFloat("Zombie_Damage");
	ZombieCon->bAttackPlayer = false;
	
	return EBTNodeResult::Succeeded;
}
