// Fill out your copyright notice in the Description page of Project Settings.


#include "EquipmentComponent.h"
#include "../Characters/Humanoid/Players/CodeFPS_Char_Player.h"
#include "../GameCodeTypes.h"
#include "../Core/CodeFPS_GameMode.h"
#include "Kismet/GameplayStatics.h"
#include "Net/UnrealNetwork.h"
#include "../Actors/Equipment/Weapons/CodeFPS_Weapon_Shooting_Base.h"

void UEquipmentComponent::Multicast_SpawnWeapon_Implementation()
{
	if ((CurrentWeapon != nullptr) && (OwnerCharacter != nullptr))
	{
		CurrentWeapon->AttachToCharacter(OwnerCharacter);
	}
}

void UEquipmentComponent::Server_SpawnWeapon_Implementation()
{
		if (!IsValid(SelectedWeaponClass))
		{
			return;
		}
		Multicast_SpawnWeapon();
}

void UEquipmentComponent::BeginPlay()
{
	Super::BeginPlay();

	if (GetOwner()->IsA<ACodeFPS_Char_Humanoid_Base>()) //"UEquipmentComponent:: Bad Owner"
	{
		OwnerCharacter = StaticCast< ACodeFPS_Char_Humanoid_Base*>(GetOwner());
		//GEngine->AddOnScreenDebugMessage(7, 9, FColor::Emerald, OwnerCharacter->GetName());
		/*
		if (StaticCast< ACodeFPS_GameMode*>(GetWorld()->GetAuthGameMode())->IsWeaponsAllowed())
		{
			Server_SpawnWeapon();
		}
		//*/
		CurrentWeapon = GetWorld()->SpawnActor<ACodeFPS_Item_Weapon_Base>(SelectedWeaponClass);
		Server_SpawnWeapon();
	}
}

void UEquipmentComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UEquipmentComponent, CurrentWeapon);
}

void UEquipmentComponent::FireCurrentWeapon()
{
	if (CurrentWeapon != nullptr)
	{
		CurrentWeapon->Attack(OwnerCharacter);
	}
}

void UEquipmentComponent::Multi_print(int i, FString string)
{
	GEngine->AddOnScreenDebugMessage(i, 9, FColor::Purple, string);
}

int UEquipmentComponent::GetAmmoInClipMax()
{
	ACodeFPS_Weapon_Shooting_Base* ShootingWeapon = Cast< ACodeFPS_Weapon_Shooting_Base>(CurrentWeapon);
	if (ShootingWeapon != nullptr)
	{
		return ShootingWeapon->AmmoInClipMax;
	}
	else return 0;
}

int UEquipmentComponent::GetAmmoInClipCurrent()
{
	ACodeFPS_Weapon_Shooting_Base* ShootingWeapon = Cast< ACodeFPS_Weapon_Shooting_Base>(CurrentWeapon);
	if (ShootingWeapon != nullptr)
	{
		return ShootingWeapon->AmmoInClipCurrent;
	}
	else return 0;
}

void UEquipmentComponent::Server_ReloadStart_Implementation()
{
}

void UEquipmentComponent::Server_ReloadEnd_Implementation()
{
	//GEngine->AddOnScreenDebugMessage(7, 9.0f, FColor::Orange, TEXT("ReloadEnd"));
	ACodeFPS_Weapon_Shooting_Base* ShootingWeapon = Cast< ACodeFPS_Weapon_Shooting_Base>(CurrentWeapon);
	if (ShootingWeapon!= nullptr)
	{
		ShootingWeapon->Server_Reload();
	}
	//else GEngine->AddOnScreenDebugMessage(2, 9.0f, FColor::Yellow, TEXT("EqNoWeap"));
}

void UEquipmentComponent::Server_UserDies_Implementation()
{
	//Spawn weapon
	CurrentWeapon->Destroy();
	//DestroyComponent(true);
}
