// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CodeFPS_Item_Weapon_Base.h"
#include "Projectiles/CodeFPS_Proj_Base.h"
#include "CodeFPS_Weapon_Shooting_Base.generated.h"

/**
 * 
 */
UENUM(BlueprintType)
enum  EAmmoType {

	PistolAmmo UMETA(DisplayName = "Pistol Ammo"),
	ShotgunAmmo UMETA(DisplayName = "Shotgun Ammo"),
	RifleAmmo UMETA(DisplayName = "Rifle Ammo")
};

UCLASS()
class CODEFPS_API ACodeFPS_Weapon_Shooting_Base : public ACodeFPS_Item_Weapon_Base
{
	GENERATED_BODY()
	

public:
	ACodeFPS_Weapon_Shooting_Base();

	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UFUNCTION()
	EAmmoType GetAmmoType();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		int AmmoInClipMax; //static	

	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		int AmmoInClipCurrent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		int AmmoMax; // static	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		int AmmoStashCurrent;

	UFUNCTION()
		int GetAmmoInClipMax(); //static

	UFUNCTION()
		int GetAmmoInClipCurrent();

	UFUNCTION()
		int GetAmmoMax(); //static	

	//UFUNCTION()
	void Attack(ACodeFPS_Character_Base* Attacker) override;

	UFUNCTION(Server, Reliable)
		void Server_Attack(ACodeFPS_Character_Base* Attacker);

	UFUNCTION(NetMulticast, Reliable)
		void Multicast_Attack();

	UFUNCTION(Server, Reliable)
		void Server_Reload();

	//UFUNCTION(Server, Reliable)
		void MC_Multiprint(int i, FString string);

protected:
	EAmmoType AmmoType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Paramters")
		bool IsAutomatic = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Paramters")
		float SpreadRadius;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		class UCodeFPS_Proj_Spawn_Component* WeaponBarrel;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TSubclassOf<class AActor> bulletClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sounds")
		USoundBase* FireSound;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sounds")
		USoundBase* ReloadEjectSound;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sounds")
		USoundBase* ReloadInsertSound;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sounds")
		USoundBase* EmptySound;


	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UParticleSystem* FireEffect;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	//ACodeFPS_Proj_Base* bullet;
	UFUNCTION()
		FVector GetTraceHitLocation();
};
