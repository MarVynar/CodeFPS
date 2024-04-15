// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../EquipmentItem_Base.h"
#include "Components/BoxComponent.h" // To delete?
#include "../../../Components/CodeFPS_Proj_Spawn_Component.h"
#include "../../../Characters/CodeFPS_Character_Base.h"
#include "CodeFPS_Item_Weapon_Base.generated.h"


UENUM(BlueprintType)
enum class EWeaponType : uint8
{
	None,
	Pistol,
	Rifle,
	Shotgun
};

UCLASS(Blueprintable)
class CODEFPS_API ACodeFPS_Item_Weapon_Base : public AEquipmentItem_Base
{
	GENERATED_BODY()
	
public:
	ACodeFPS_Item_Weapon_Base();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		float Damage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	float AttackRate;  //static	

	UFUNCTION()
		void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	UFUNCTION()
		EWeaponType GetWeaponType();

	UFUNCTION()
		virtual void Attack(ACodeFPS_Character_Base* Attacker);

	UFUNCTION()
		void AttachToCharacter(ACodeFPS_Character_Base* Character);

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Mesh)
		USkeletalMeshComponent* GunComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Mesh)
		USkeletalMeshComponent* GunFirstPerson;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Collision)
		UBoxComponent* CollisionComp;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Gameplay)
	EWeaponType WeaponType;

	ACodeFPS_Character_Base* OwnerCharacter;
};
