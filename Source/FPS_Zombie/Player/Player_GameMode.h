#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Player_GameMode.generated.h"

UCLASS()
class FPS_ZOMBIE_API APlayer_GameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly,Category="현재 UI",meta=(AllowPrivateAccess = "true"))
	UUserWidget* NowUIWidget;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="타겟 UI")
	TSubclassOf<UUserWidget> UserMainWidget;

private:
	virtual void BeginPlay() override;
	
	APlayer_GameMode(); 
};
