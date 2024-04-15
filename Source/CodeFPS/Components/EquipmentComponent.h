// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "../Actors/Equipment/Weapons/CodeFPS_Item_Weapon_Base.h"
#include "EquipmentComponent.generated.h"

class ACodeFPS_Char_Humanoid_Base;


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CODEFPS_API UEquipmentComponent : public UActorComponent
{
	GENERATED_BODY()

	ACodeFPS_Char_Humanoid_Base* OwnerCharacter;

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Loadout")
		TSubclassOf<class ACodeFPS_Item_Weapon_Base> SelectedWeaponClass; //TArray?
	UPROPERTY(Replicated, VisibleAnywhere, BlueprintReadOnly, Category = "Loadout")
		ACodeFPS_Item_Weapon_Base* CurrentWeapon;

public:	
	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UFUNCTION()
		void FireCurrentWeapon();

	UFUNCTION(NetMulticast, Reliable) // Client
		void Multicast_SpawnWeapon();

	UFUNCTION(Server, Reliable)
		void Server_SpawnWeapon();

	///DEBUG///
	//UFUNCTION(NetMulticast, Reliable)
		void Multi_print(int i, FString string);

	UFUNCTION(Server, Reliable)
		void Server_UserDies();

	UFUNCTION(Server, Reliable)
	void Server_ReloadStart();
	UFUNCTION(Server, Reliable)
	void Server_ReloadEnd();

	int GetAmmoInClipMax();
	int GetAmmoInClipCurrent();
};
