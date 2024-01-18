// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/CanvasPanel.h"
#include "Components/Image.h"
#include "Player_Widget.generated.h"

/**
 * 
 */
UCLASS()
class FPS_ZOMBIE_API UPlayer_Widget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintReadWrite)
	UImage* ShotImage;
};
