// Fill out your copyright notice in the Description page of Project Settings.


#include "Player_GameMode.h"

#include "Player_Character.h"
#include "Blueprint/UserWidget.h"

APlayer_GameMode::APlayer_GameMode()
{
	
}

void APlayer_GameMode::BeginPlay()
{
	Super::BeginPlay();

	if(NowUIWidget != nullptr)
	{
		NowUIWidget->RemoveFromViewport();
		NowUIWidget = nullptr;
	}
	if(UserMainWidget != nullptr)
	{
		NowUIWidget = CreateWidget(GetWorld(),UserMainWidget);
		if(NowUIWidget != nullptr)
		{
			NowUIWidget->AddToViewport();
		}
	}
}
