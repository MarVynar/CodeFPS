// Fill out your copyright notice in the Description page of Project Settings.


#include "CodeFPS_Weapon_Shooting_Base.h"
#include "../../../GameCodeTypes.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "../../../Characters/CodeFPS_Character_Base.h"
#include "Net/UnrealNetwork.h"

ACodeFPS_Weapon_Shooting_Base::ACodeFPS_Weapon_Shooting_Base()
{
	WeaponBarrel = CreateDefaultSubobject<UCodeFPS_Proj_Spawn_Component>(TEXT("Barrel"));
	//WeaponBarrel->SetupAttachment(GunComponent, WeaponMuzzleSocket); //GunFirstPerson
	WeaponBarrel->SetupAttachment(GunFirstPerson, WeaponMuzzleSocket);

	AmmoInClipMax = 13;
	AmmoInClipCurrent = AmmoInClipMax;
	AmmoMax = 91;
}

int ACodeFPS_Weapon_Shooting_Base::GetAmmoInClipMax()
{
	return AmmoInClipMax;
}

int ACodeFPS_Weapon_Shooting_Base::GetAmmoInClipCurrent()
{
	return AmmoInClipCurrent;
}

int ACodeFPS_Weapon_Shooting_Base::GetAmmoMax()
{
	return AmmoMax;
}

void ACodeFPS_Weapon_Shooting_Base::Attack(ACodeFPS_Character_Base* Attacker)
{
	Server_Attack(Attacker);
}

void ACodeFPS_Weapon_Shooting_Base::Server_Reload_Implementation()
{
	if ((AmmoInClipCurrent < AmmoInClipMax) && (AmmoStashCurrent >= (AmmoInClipMax- AmmoInClipCurrent)))
	{
		AmmoStashCurrent -= AmmoInClipMax - AmmoInClipCurrent;
		AmmoInClipCurrent = AmmoInClipMax;
	}
	else
	{
		AmmoInClipCurrent = AmmoStashCurrent;
		AmmoStashCurrent = 0;
	}
	
}

void ACodeFPS_Weapon_Shooting_Base::MC_Multiprint(int i, FString string) //_Implementation
{
	GEngine->AddOnScreenDebugMessage(i, 9, FColor::Yellow, string);
}

FVector ACodeFPS_Weapon_Shooting_Base::GetTraceHitLocation()
{
	FHitResult Hit;

	FCollisionQueryParams CollisionQueryParams;
	CollisionQueryParams.AddIgnoredActor(this);
	CollisionQueryParams.bTraceComplex = false;

	FCollisionResponseParams CollisionResponseParams;

	FVector StartLocation = OwnerCharacter->GetHeadLocation();
	GetWorld()->LineTraceSingleByChannel(
		Hit,
		StartLocation,
		StartLocation + OwnerCharacter->GetActorRotation().Vector() * 50000.0f,
		ECollisionChannel::ECC_Visibility,
		CollisionQueryParams,
		CollisionResponseParams
	);
	if (Hit.bBlockingHit)
	{
		GEngine->AddOnScreenDebugMessage(2, 1.0f, FColor::Blue, FString::Printf(TEXT("LineTrace Hit with %s"), *Hit.Actor.Get()->GetName()));
	}
	return Hit.Location;
}

void ACodeFPS_Weapon_Shooting_Base::Server_Attack_Implementation(ACodeFPS_Character_Base* Attacker)
{
	if (AmmoInClipCurrent > 0)
	{
		FActorSpawnParameters spawnParameters;

		spawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		FRotator AtTargetRotation = UKismetMathLibrary::FindLookAtRotation(WeaponBarrel->GetComponentLocation(), GetTraceHitLocation());
		ACodeFPS_Proj_Base* bullet = GetWorld()->SpawnActor<ACodeFPS_Proj_Base>(bulletClass, WeaponBarrel->GetComponentLocation(), AtTargetRotation, spawnParameters);
		bullet->SetShooter(Attacker);
		AmmoInClipCurrent--;
		Multicast_Attack();
	}
	else
	{
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), EmptySound, GetActorLocation()); // Multisound
	}
}

void ACodeFPS_Weapon_Shooting_Base::Multicast_Attack_Implementation()
{
	UGameplayStatics::PlaySoundAtLocation(GetWorld(), FireSound, WeaponBarrel->GetComponentLocation());
	if ((OwnerCharacter != nullptr) && (OwnerCharacter->GetController() == UGameplayStatics::GetPlayerController(GetWorld(), 0)))
	{
		UGameplayStatics::SpawnEmitterAttached(FireEffect, WeaponBarrel);
	}
	else
	{
		UGameplayStatics::SpawnEmitterAttached(FireEffect, GunComponent, WeaponMuzzleSocket);
		AActor* OwnerA = GetOwner();
	}
}

void ACodeFPS_Weapon_Shooting_Base::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ACodeFPS_Weapon_Shooting_Base, AmmoInClipCurrent);
}

EAmmoType ACodeFPS_Weapon_Shooting_Base::GetAmmoType()
{
	return AmmoType;
}