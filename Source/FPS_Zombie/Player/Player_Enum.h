// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


	UENUM(BlueprintType)
	enum class EAniState_Normal : uint8
	{
		Idle = 0 UMETA(DisplayName = "Idle"),
		Walk = 1 UMETA(DisplayName = "Walk"),
		Run = 2 UMETA(DisplayName = "Run"),
		Jump = 3 UMETA(DisplayName = "Jump"),
		Fall = 4 UMETA(DisplayerName = "Fall")
	};

