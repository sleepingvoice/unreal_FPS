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
	Rifle = 3 UMETA(DisplayName = "Rifle"),
	RifleZoom = 4 UMETA(DisplayName = "RifleZoom")
};

UENUM(BlueprintType)
enum class EAnistate_UpperBody : uint8
{
	Normal = 0 UMETA(DisplayName = "Normal"),
	Shot = 1 UMETA(DisPlayName = "ShotStart"),
	Reload = 2 UMETA(DisPlayName = "Reload"),
	Hit = 3 UMETA(DisPlayName = "Hit")
};