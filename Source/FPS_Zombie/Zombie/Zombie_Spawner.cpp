#include "Zombie_Spawner.h"

#include "BehaviorTree/BlackboardComponent.h"

AZombie_Spawner::AZombie_Spawner()
{
	DebugSphere = CreateDefaultSubobject<USphereComponent>(FName("DebugSpawnSphere"));
	DebugSphere->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	RootComponent  = DebugSphere;
	
}

void AZombie_Spawner::BeginPlay()
{
	Super::BeginPlay();
	SpawnRange = DebugSphere->GetScaledSphereRadius();
	
	if(SpawnTypeArr.Num() == 0) return;
	
	for(int i=0;i<SpawnValue;i++)
	{
		SpawnMonster(SpawnTypeArr[FMath::RandRange(0,SpawnTypeArr.Num()-1)]); // 설정한 랜덤한 상태 소환
	}
}

void AZombie_Spawner::SpawnMonster(FMonsterSpawnType SpawnType)
{
	AZombie_Character* SpawnZombie = GetWorld()->SpawnActor<AZombie_Character>(SpawnType.ZombieCharacter);
	//생성

	if(SpawnZombie == nullptr)
	{
		UE_LOG(LogTemp,Log,TEXT("다 없음"));
		return;
	}
	
	auto controller = SpawnZombie->Controller;
	if(controller == nullptr)
	{
		UE_LOG(LogTemp,Log,TEXT("컨트롤러 없음"));
		return;
	}
	
	auto Aicontroller = Cast<AAIController>(controller);
	if(Aicontroller == nullptr)
	{
		UE_LOG(LogTemp,Log,TEXT("Ai컨트롤러 없음"));
		return;
	}
	
	UBlackboardComponent* BlackBoardClass = Cast<AAIController>(SpawnZombie->Controller)->GetBlackboardComponent();
	if(BlackBoardClass == nullptr)
	{
		UE_LOG(LogTemp,Log,TEXT("블랙보드 클래스 없음"));
		return;
	}
	
	BlackBoardClass->SetValueAsClass(FName("Zombie_Character"),Cast<UClass>(SpawnZombie));
	BlackBoardClass->SetValueAsFloat(FName("Zombie_Hp"),SpawnType.Hp);
	BlackBoardClass->SetValueAsFloat(FName("Zombie_Damage"),SpawnType.Damge);
	BlackBoardClass->SetValueAsString(FName("Zombie_ID"),SpawnType.KeyValue);
	//값 지정

	FVector SpanwLocation;
	while (true)
	{
		float RandomX = FMath::FRandRange(-SpawnRange, SpawnRange);
		float RandomZ = FMath::FRandRange(-SpawnRange, SpawnRange);

		SpanwLocation = this->GetActorLocation()+ FVector3d(RandomX,0,RandomZ);
		SpanwLocation = GetCollisionPointBelowLocation(SpanwLocation);
		
		if(SpanwLocation != FVector::ZeroVector) break;
	}
	//위치 지정

	SpawnZombie->SetActorLocation(SpanwLocation);
}

FVector AZombie_Spawner::GetCollisionPointBelowLocation(const FVector& StartLocation)
{
	FVector EndLocation = StartLocation - FVector::UpVector * (this->GetActorLocation().Y + SpawnRange); // Y가 0인 좌표까지 내린다.
    
	FHitResult HitResult;
	FCollisionQueryParams CollisionParams;
	CollisionParams.AddIgnoredActor(GetOwner()); 
	
	if (GetWorld()->LineTraceSingleByChannel(HitResult, StartLocation, EndLocation, ECC_Visibility, CollisionParams)) // 충돌체크
	{
		FVector CollisionPoint = HitResult.ImpactPoint;

		//디버그용
		//DrawDebugPoint(GetWorld(), CollisionPoint, 10.0f, FColor::Red, false, 2.0f);

		return CollisionPoint;
	}

	// 충돌이 없는 경우
	return FVector::ZeroVector;
}
