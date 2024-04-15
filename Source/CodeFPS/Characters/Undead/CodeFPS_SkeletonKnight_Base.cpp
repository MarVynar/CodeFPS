// Fill out your copyright notice in the Description page of Project Settings.


#include "CodeFPS_SkeletonKnight_Base.h"
#include "Kismet/GameplayStatics.h"

ACodeFPS_SkeletonKnight_Base::ACodeFPS_SkeletonKnight_Base()
{
	ShieldCollision =  CreateDefaultSubobject<UBoxComponent>(TEXT("ShieldCollision"));
	ShieldCollision->OnComponentBeginOverlap.AddDynamic(this, &ACodeFPS_SkeletonKnight_Base::OnShieldHit);
	ShieldCollision->SetupAttachment(GetMesh(), HumanoidRGripSocketLeft3P);
	WeaponCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("WeaponCollision"));
	WeaponCollision->OnComponentBeginOverlap.AddDynamic(this, &ACodeFPS_SkeletonKnight_Base::OnWeaponHit);
	WeaponCollision->SetupAttachment(GetMesh(), HumanoidRGripSocket3P);
	WeaponCollision->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void ACodeFPS_SkeletonKnight_Base::OnAttackBegin()
{
	WeaponCollision->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
}

void ACodeFPS_SkeletonKnight_Base::OnAttackEnd()
{
	WeaponCollision->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	Super::OnAttackEnd();
}

void ACodeFPS_SkeletonKnight_Base::OnAbilityBegin()
{
	if (StructEquals(AbilityInfoCurrent, AbilityBlock))
	{
		BlockStart();
	}
}

void ACodeFPS_SkeletonKnight_Base::OnAbilityEnd()
{
}

void ACodeFPS_SkeletonKnight_Base::OnShieldHit(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Server_OnShieldHit(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex,bFromSweep,SweepResult);
}

void ACodeFPS_SkeletonKnight_Base::OnWeaponHit(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Server_OnWeaponHit(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex,bFromSweep, SweepResult);
}

void ACodeFPS_SkeletonKnight_Base::Server_OnShieldHit_Implementation(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
}

void ACodeFPS_SkeletonKnight_Base::Server_OnWeaponHit_Implementation(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor != this)
	{
		TSubclassOf<UDamageType> DmgTypeClass = AttackInfoCurrent.DmgTypeClass ? *DmgTypeClass : UDamageType::StaticClass();
		AController* EventInstigator = UGameplayStatics::GetPlayerController(GetWorld(), 0);
		OtherActor->TakeDamage(AttackInfoCurrent.AttackDamage, FDamageEvent(DmgTypeClass), EventInstigator, this);
	}
}

void ACodeFPS_SkeletonKnight_Base::Block()
{
	UseAbility(AbilityBlock);
}

void ACodeFPS_SkeletonKnight_Base::BlockStart()
{
}

void ACodeFPS_SkeletonKnight_Base::Warcry()
{
}
