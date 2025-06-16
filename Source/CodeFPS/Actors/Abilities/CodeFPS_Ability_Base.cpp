// Fill out your copyright notice in the Description page of Project Settings.


#include "CodeFPS_Ability_Base.h"
#include "Net/UnrealNetwork.h"

// Sets default values
ACodeFPS_Ability_Base::ACodeFPS_Ability_Base()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	IsActive = false;
}

// Called when the game starts or when spawned
void ACodeFPS_Ability_Base::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACodeFPS_Ability_Base::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

/*
void ACodeFPS_Ability_Base::UseAbility_Implementation()
{
	
}*/


void ACodeFPS_Ability_Base::UseAbility()
{
	/*if (CheckAbilityRequirements(AbilityInfo)) {
		if (AbilityInfo.AbilityMontage != nullptr)
		{
			Server_PlayAnimation(AbilityInfo.AbilityMontage);
		}
		if (AbilityInfo.AbilitySound != nullptr)
		{
			Server_PlaySound(AbilityInfo.AbilitySound);
		}
		AbilityInfoCurrent = AbilityInfo;
		OnAbilityBegin();
		AbilityEffect();
	}*/
	Server_AbilityEffect();
}

void ACodeFPS_Ability_Base::OnAbilityBegin()
{
	/*
	TArray <AActor*> ActorsToApply;
	if (AbilityInfoCurrent.AbilityRange == 0)
	{
		ActorsToApply.Add(this);
	}
	else
	{
		FHitResult Hit;
		TArray< FHitResult> HitResults;

		FCollisionQueryParams CollisionQueryParams;
		CollisionQueryParams.AddIgnoredActor(this);
		CollisionQueryParams.bTraceComplex = false;
		//TArray<EObjectType>

		//UKismetSystemLibrary::CapsuleTraceMultiForObjects(this,) LineTraceMultiForObjects
		for (float angle = (this->GetActorRotation().Yaw - AbilityInfoCurrent.AbilityAngle/2); angle <= (this->GetActorRotation().Yaw - AbilityInfoCurrent.AbilityAngle/2); angle++)
		{
			UKismetSystemLibrary::LineTraceMultiForObjects(this,
				GetMesh()->GetComponentLocation(),
				GetMesh()->GetComponentLocation() + FVector(AbilityInfoCurrent.AbilityRange * FMath::Cos(angle), AbilityInfoCurrent.AbilityRange * FMath::Sin(angle), GetMesh()->GetComponentLocation().Z),
				{ UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_WorldDynamic) },
				false,
				{ },
				EDrawDebugTrace::ForDuration,
				HitResults,
				true);

			for each (FHitResult Iter in HitResults)
			{
				ActorsToApply.AddUnique(Iter.Actor.Get());
			}

		}

	}
	for each (AActor* Iter in ActorsToApply)
	{


		switch (AbilityInfoCurrent.AbilityEffect)
		{
		case EAbilityEffect::Damage: break;
		case EAbilityEffect::Heal: break;
		case EAbilityEffect::Shield: break;
		case EAbilityEffect::Invincibility: break;
		case EAbilityEffect::SpeedUp: break;
		case EAbilityEffect::SlowDown: break;
		case EAbilityEffect::PowerUp: break;
		case EAbilityEffect::Weaken: break;
		case EAbilityEffect::Spawn:
			FVector SpawnPoint;
			Server_AbilitySpawn(AbilityInfoCurrent.ActorToSpawn, Iter->GetActorLocation()+SpawnPoint);
			break;
			default: break;
		}
	} */
}

void ACodeFPS_Ability_Base::OnAbilityEnd()
{
}

bool ACodeFPS_Ability_Base::IsActiveAbility()
{
	return IsActive;
}

void ACodeFPS_Ability_Base::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ACodeFPS_Ability_Base, IsActive);
}

void ACodeFPS_Ability_Base::MC_AbilityEffect_Implementation()
{
}

void ACodeFPS_Ability_Base::Serv_AbilityEffect_Implementation()
{
}

void ACodeFPS_Ability_Base::Multicast_AbilityEffect_Implementation()
{
	MC_AbilityEffect();
}
/*
void ACodeFPS_Ability_Base::AbilityEffect_Implementation()
{
}*/

void ACodeFPS_Ability_Base::Server_AbilityEffect_Implementation()
{
	if (AbilityInfo.EffectTime > 0)
	{
		IsActive = true;
	}
	Serv_AbilityEffect();
	Multicast_AbilityEffect();
}

void ACodeFPS_Ability_Base::Server_AbilitySpawn_Implementation(TSubclassOf<class AActor> ActorClass, FVector SpawnLocation)
{
	//FActorSpawnParameters spawnParameters;

	//spawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	//AActor* SpawnedActor;
	//if (OwnerCharacter->IsA(ACodeFPS_Char_Player::StaticClass()))
	{
		//FRotator AtTargetRotation; //= UKismetMathLibrary::FindLookAtRotation(WeaponBarrel->GetComponentLocation(), GetTraceHitLocation(HumanoidHeadSocket));
		//SpawnedActor = GetWorld()->SpawnActor<ActorClass>(ActorClass, SpawnLocation, AtTargetRotation, spawnParameters);  // Correct Animation needed for Char
	}
}

void ACodeFPS_Ability_Base::Serv_RemoveEffect_Implementation()
{
}

void ACodeFPS_Ability_Base::MC_RemoveEffect_Implementation()
{
}

void ACodeFPS_Ability_Base::Server_RemoveEffect_Implementation()
{
	IsActive = false;
	Serv_RemoveEffect();
	Multicast_RemoveEffect();
}

void ACodeFPS_Ability_Base::Multicast_RemoveEffect_Implementation()
{
	MC_RemoveEffect();
}

void ACodeFPS_Ability_Base::RemoveEffect()
{
	Server_RemoveEffect();
}
