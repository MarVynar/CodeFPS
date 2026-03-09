// Fill out your copyright notice in the Description page of Project Settings.


#include "CodeFPS_SkeletonKnight_Base.h"
#include "Kismet/GameplayStatics.h"
#include "../../Actors/Equipment/Weapons/Projectiles/CodeFPS_Proj_Base.h"

ACodeFPS_SkeletonKnight_Base::ACodeFPS_SkeletonKnight_Base()
{
	ShieldCollision =  CreateDefaultSubobject<UBoxComponent>(TEXT("ShieldCollision"));
	ShieldCollision->OnComponentBeginOverlap.AddDynamic(this, &ACodeFPS_SkeletonKnight_Base::OnShieldHit);
	ShieldCollision->SetupAttachment(GetMesh(), HumanoidRGripSocketLeft3P);
	ShieldCollision->SetBoxExtent(FVector(15.0f, 35.0f, 55.0f));
	WeaponCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("WeaponCollision"));
	WeaponCollision->OnComponentBeginOverlap.AddDynamic(this, &ACodeFPS_SkeletonKnight_Base::OnWeaponHit);
	WeaponCollision->OnComponentEndOverlap.AddDynamic(this, &ACodeFPS_SkeletonKnight_Base::OnWeaponEndOverlap);
	WeaponCollision->SetupAttachment(GetMesh(), HumanoidRGripSocket3P);
	WeaponCollision->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	SlowWalkSpeed = 200;
}

void ACodeFPS_SkeletonKnight_Base::BeginPlay()
{
	Super::BeginPlay();

	FActorSpawnParameters spawnParameters;
	spawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	//AbilityWarcry.AbilityActor = GetWorld()->SpawnActor<ACodeFPS_Ability_Base>(AbilityWarcry.AbilityActorClass, GetActorLocation(), GetActorRotation(), spawnParameters);
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

/*
void ACodeFPS_SkeletonKnight_Base::OnAbilityBegin()
{
	/*
	if (StructEquals(AbilityInfoCurrent, AbilityBlock))
	{
		BlockStart();
	}/
}

void ACodeFPS_SkeletonKnight_Base::OnAbilityEnd()
{
}
*/
void ACodeFPS_SkeletonKnight_Base::OnShieldHit(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Server_OnShieldHit(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex,bFromSweep,SweepResult);
}

void ACodeFPS_SkeletonKnight_Base::OnWeaponHit(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor != this && !HitTargets.Contains(OtherActor))
	{
		HitTargets.Add(OtherActor);
		Server_OnWeaponHit(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);
	}
}

void ACodeFPS_SkeletonKnight_Base::OnWeaponEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	HitTargets.Remove(OtherActor);
}

void ACodeFPS_SkeletonKnight_Base::Server_OnShieldHit_Implementation(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	GEngine->AddOnScreenDebugMessage(4, 3.0f, FColor::Yellow, OtherActor->GetName());
	if (OtherActor->IsA(ACodeFPS_Proj_Base::StaticClass()))
	{
		OtherActor->Destroy();
	}
}

void ACodeFPS_SkeletonKnight_Base::Server_OnWeaponHit_Implementation(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor != this)
	{
		TSubclassOf<UDamageType> DmgTypeClass = AttackInfoCurrent.DmgTypeClass ? *DmgTypeClass : UDamageType::StaticClass();
		AController* EventInstigator = UGameplayStatics::GetPlayerController(GetWorld(), 0);
		OtherActor->TakeDamage(AttackInfoCurrent.AttackDamage + DamageAmp, FDamageEvent(DmgTypeClass), EventInstigator, this);
		if (AttackInfoCurrent.AttackHitSound != nullptr)
		{
			Server_PlaySoundAtLocation(AttackInfoCurrent.AttackHitSound, WeaponCollision->GetComponentLocation()); // 
		}

	}
}

void ACodeFPS_SkeletonKnight_Base::Block()
{
	//UseAbility(AbilityBlock);
}

void ACodeFPS_SkeletonKnight_Base::BlockStart()
{
}

void ACodeFPS_SkeletonKnight_Base::Warcry()
{
}
