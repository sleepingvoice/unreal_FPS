// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


	UENUM(BlueprintType)
	enum class EAniState_Move : uint8
	{
		Idle = 0 UMETA(DisplayName = "Idle"),
		Walk = 1 UMETA(DisplayName = "Walk"),
		Run = 2 UMETA(DisplayName = "Run"),
		Jump = 3 UMETA(DisplayName = "Jump"),
		Fall = 4 UMETA(DisplayerName = "Fall")
	};

UENUM(BlueprintType)
enum class EAniState_Weapon : uint8
{
	NoWeapon = 0 UMETA(DisplayName = "NoWeapon"),
	Knife = 1 UMETA(DisplayName = "Knife"),
	Pistol = 2 UMETA(DisplayName = "Pistol"),
	Rifle = 3 UMETA(DisplayName = "Rifle")
};
