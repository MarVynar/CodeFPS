// Fill out your copyright notice in the Description page of Project Settings.


#include "CodeFPS_Ab_Grunt_Base.h"
#include "Kismet/GameplayStatics.h"
#include "CodeFPS_Ab_Grunt_Base.h"

ACodeFPS_Ab_Grunt_Base::ACodeFPS_Ab_Grunt_Base()
{
	LeftHandCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("LeftHandCollision"));
	LeftHandCollision->OnComponentBeginOverlap.AddDynamic(this, &ACodeFPS_Ab_Grunt_Base::OnLeftHandHit);
	LeftHandCollision->OnComponentEndOverlap.AddDynamic(this, &ACodeFPS_Ab_Grunt_Base::OnLeftHandEndOverlap);
	LeftHandCollision->SetupAttachment(GetMesh(), "hand_l"); //Socket // HumanoidRGripSocketLeft3P
	LeftHandCollision->SetBoxExtent(FVector(15.0f, 35.0f, 55.0f));
	RightHandCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("RightHandCollision"));
	RightHandCollision->OnComponentBeginOverlap.AddDynamic(this, &ACodeFPS_Ab_Grunt_Base::OnRightHandHit);
	RightHandCollision->OnComponentEndOverlap.AddDynamic(this, &ACodeFPS_Ab_Grunt_Base::OnRightHandEndOverlap);
	RightHandCollision->SetupAttachment(GetMesh(), "hand_rSocket"); // , HumanoidRGripSocket3P); //Socket
	RightHandCollision->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	SlowWalkSpeed = 200;
}

void ACodeFPS_Ab_Grunt_Base::BeginPlay()
{
	Super::BeginPlay();

	FActorSpawnParameters spawnParameters;
	spawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	//AbilityWarcry.AbilityActor = GetWorld()->SpawnActor<ACodeFPS_Ability_Base>(AbilityWarcry.AbilityActorClass, GetActorLocation(), GetActorRotation(), spawnParameters);
}

void ACodeFPS_Ab_Grunt_Base::OnAttackBegin()
{
	RightHandCollision->SetCollisionEnabled(ECollisionEnabled::QueryOnly); // Add Left Hand
}

void ACodeFPS_Ab_Grunt_Base::OnAttackEnd()
{
	RightHandCollision->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	Super::OnAttackEnd();
}

void ACodeFPS_Ab_Grunt_Base::OnRightHandHit(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor != this && !HitTargetsRight.Contains(OtherActor))
	{
		HitTargetsRight.Add(OtherActor);
		Server_OnRightHandHit(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);
	}
}

void ACodeFPS_Ab_Grunt_Base::OnLeftHandHit(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor != this && !HitTargetsLeft.Contains(OtherActor))
	{
		HitTargetsLeft.Add(OtherActor);
		Server_OnLeftHandHit(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);
	}
}

void ACodeFPS_Ab_Grunt_Base::OnRightHandEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	HitTargetsRight.Remove(OtherActor);
}

void ACodeFPS_Ab_Grunt_Base::OnLeftHandEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	HitTargetsLeft.Remove(OtherActor);
}

void ACodeFPS_Ab_Grunt_Base::Server_OnRightHandHit_Implementation(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor != this)
	{
		TSubclassOf<UDamageType> DmgTypeClass = AttackInfoCurrent.DmgTypeClass ? *DmgTypeClass : UDamageType::StaticClass();
		AController* EventInstigator = UGameplayStatics::GetPlayerController(GetWorld(), 0);
		OtherActor->TakeDamage(AttackInfoCurrent.AttackDamage + DamageAmp, FDamageEvent(DmgTypeClass), EventInstigator, this);
		if (AttackInfoCurrent.AttackHitSound != nullptr)
		{
			Server_PlaySoundAtLocation(AttackInfoCurrent.AttackHitSound, RightHandCollision->GetComponentLocation()); // 
		}

	}
}

void ACodeFPS_Ab_Grunt_Base::Server_OnLeftHandHit_Implementation(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor != this)
	{
		TSubclassOf<UDamageType> DmgTypeClass = AttackInfoCurrent.DmgTypeClass ? *DmgTypeClass : UDamageType::StaticClass();
		AController* EventInstigator = UGameplayStatics::GetPlayerController(GetWorld(), 0);
		OtherActor->TakeDamage(AttackInfoCurrent.AttackDamage + DamageAmp, FDamageEvent(DmgTypeClass), EventInstigator, this);
		if (AttackInfoCurrent.AttackHitSound != nullptr)
		{
			Server_PlaySoundAtLocation(AttackInfoCurrent.AttackHitSound, LeftHandCollision->GetComponentLocation()); // 
		}

	}
}

/*
void ACodeFPS_Ghoul_Base::EatStart()
{
	IsEating = true;
}

void ACodeFPS_Ghoul_Base::EatEnd()
{
	IsEating = false;
}

void ACodeFPS_Ghoul_Base::Shout()
{
}

*/