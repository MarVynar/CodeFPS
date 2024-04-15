// Fill out your copyright notice in the Description page of Project Settings.


#include "CodeFPS_Item_Weapon_Base.h"
#include "../../../Characters/Humanoid/Players/CodeFPS_Char_Player.h"
#include "../../../GameCodeTypes.h"

ACodeFPS_Item_Weapon_Base::ACodeFPS_Item_Weapon_Base()
{
	PrimaryActorTick.bCanEverTick = true;

	// Create a gun mesh component
	GunComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Gun"));
	//GunComponent->SetOnlyOwnerSee(false);			// otherwise won't be visible in the multiplayer
	GunComponent->bCastDynamicShadow = true;
	GunComponent->CastShadow = true;
	GunComponent->SetOwnerNoSee(true);

	GunComponent->SetupAttachment(RootComponent);

	CollisionComp = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision"));
	CollisionComp->SetBoxExtent(FVector(15.0f, 15.0f, 15.0f));
	//CollisionComp->BodyInstance.SetCollisionProfileName("Projectile");
	CollisionComp->OnComponentHit.AddDynamic(this, &ACodeFPS_Item_Weapon_Base::OnHit);		
	CollisionComp->SetupAttachment(GunComponent);

	GunFirstPerson = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("FP_Gun"));
	GunComponent->SetOwnerNoSee(false);
	GunFirstPerson->SetOnlyOwnerSee(true);			
	GunFirstPerson->bCastDynamicShadow = false;
	GunFirstPerson->CastShadow = false;
	GunFirstPerson->SetupAttachment(GunComponent);
}

void ACodeFPS_Item_Weapon_Base::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	{
		//Player->AddWeapon(this);
	}
}

EWeaponType ACodeFPS_Item_Weapon_Base::GetWeaponType()
{
	return WeaponType;
}

void ACodeFPS_Item_Weapon_Base::Attack(ACodeFPS_Character_Base* Attacker)
{
}

void ACodeFPS_Item_Weapon_Base::AttachToCharacter(ACodeFPS_Character_Base* Character)
{
	ACodeFPS_Char_Humanoid_Base* OwnerHumanoid = Cast<ACodeFPS_Char_Humanoid_Base>(Character);
	if (OwnerHumanoid != nullptr)
	{
		OwnerCharacter = OwnerHumanoid;
		AttachToComponent(Character->GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, HumanoidRGripSocket3P);
		GunFirstPerson->SetSkeletalMesh(GunComponent->SkeletalMesh);
		ACodeFPS_Char_Player* OwnerPlayer = Cast<ACodeFPS_Char_Player>(Character);
		if (OwnerPlayer != nullptr)
		{
			GunFirstPerson->AttachToComponent(OwnerPlayer->GetMesh1P(), FAttachmentTransformRules::KeepRelativeTransform, HumanoidRGripSocket1P);
		}
	}
}

