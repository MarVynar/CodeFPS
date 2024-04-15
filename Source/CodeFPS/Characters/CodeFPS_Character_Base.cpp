// Fill out your copyright notice in the Description page of Project Settings.


#include "CodeFPS_Character_Base.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "../GameCodeTypes.h"
#include "Kismet/GameplayStatics.h"
#include "Net/UnrealNetwork.h"

#define LIGHTDAMAGEPART 4
#define MEDIUMDAMAGEPART 2

ACodeFPS_Character_Base::ACodeFPS_Character_Base()
{
	PrimaryActorTick.bCanEverTick = true;

	IsDead = false;
	HealthPoints = 100;
	HealthMaxPoints = 100;
	HealthRegenPoints = 0;

	ArmorPoints = 0;
	ArmorMaxPoints = 0;

	ShieldPoints = 0;
	ShieldMaxPoints = 0;
	ShieldRegenPoints = 0;

	IsShielded = false;

	ManaPoints = 0;
	ManaMaxPoints = 0;
	ManaRegenPoints = 0;

	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	MovementType = EMovementType::Walk;

	SprintSpeed = 1200.f;

	DefaultWalkSpeed = 600.f;
	SlowWalkSpeed = 300.f;

	CrouchModifier = 0.5f;

	DashDistance = 150000.f;

	GetMesh()->bCastDynamicShadow = true;
	GetMesh()->CastShadow = true;
	GetMesh()->SetOwnerNoSee(true);
}

void ACodeFPS_Character_Base::BeginPlay()
{
	Super::BeginPlay();
	
}

void ACodeFPS_Character_Base::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACodeFPS_Character_Base::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ACodeFPS_Character_Base::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ACodeFPS_Character_Base, HealthPoints);
	DOREPLIFETIME(ACodeFPS_Character_Base, ShieldPoints);
	DOREPLIFETIME(ACodeFPS_Character_Base, ManaPoints);
}


float ACodeFPS_Character_Base::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, FString::Printf(TEXT("Damage , %d") , DamageAmount));
	if (IsDead)
	{
		return 0;
	}

	Server_TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	return Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
}

void ACodeFPS_Character_Base::Server_TakeDamage_Implementation(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{

	//DamageEvent.IsOfType(FRadialDamageEvent::ClassID);
	float IncomeDamage = 0;// = DamageAmount;
	if (ShieldPoints >= 0) 
	{

		ShieldPoints -= DamageAmount;
		if (ShieldPoints < 0) {

			IncomeDamage = 0 - ShieldPoints;
			ShieldPoints = 0;
		}
	}
	else 
	{
		IncomeDamage = DamageAmount;
	}

	//CalculateArmor
	HealthPoints -= IncomeDamage;
	//Blood on Bone location

	if (HealthPoints <= 0) 
	{
		HealthPoints = 0;
		Server_Die(IncomeDamage>= HealthMaxPoints);
	}
	else
	{
		float DamagePart = HealthMaxPoints / IncomeDamage;
		if (DamagePart >= LIGHTDAMAGEPART)
		{
			TakeDamageLight();
		}
		if ((DamagePart >= MEDIUMDAMAGEPART) && (DamagePart < LIGHTDAMAGEPART))
		{
			TakeDamageMedium();
		}
		if (DamagePart < MEDIUMDAMAGEPART)
		{
			TakeDamageHeavy();
		}
	}
}

void ACodeFPS_Character_Base::Falling()
{
	GetCharacterMovement()->bNotifyApex = true;
}

void ACodeFPS_Character_Base::Landed(const FHitResult& Hit)
{
	Super::Landed(Hit);
	float FallHeight = (CurrentFallApex - GetActorLocation()).Z * 0.01; //100 - cm into m
	if (IsValid(FallDamageCurve))
	{
		float DamageAmount = FallDamageCurve->GetFloatValue(FallHeight);
		TakeDamage(DamageAmount, FDamageEvent(), GetController(), Hit.Actor.Get()); //AddLegDamage for Humanoid
	}
}

void ACodeFPS_Character_Base::NotifyJumpApex()
{
	Super::NotifyJumpApex();
	CurrentFallApex = GetActorLocation();
}

void ACodeFPS_Character_Base::Server_Die_Implementation(bool FatalDamage)
{
	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, TEXT("DYing"));
	IsDead = true;
	GetCharacterMovement()->DisableMovement();
	if (!FatalDamage)
	{
		if (OnDeathMontage != nullptr)
		{
			Server_PlayAnimation(OnDeathMontage);
		}
		Multicast_Die(false);
	}
	else
	{
		TakeDamageFatal();
		Multicast_Die(true);
	}
}


void ACodeFPS_Character_Base::Die_Implementation(bool FatalDamage)
{
	//Destroy();
}

void ACodeFPS_Character_Base::Multicast_Die_Implementation(bool FatalDamage)
{
	//GEngine->AddOnScreenDebugMessage(3, 15.0f, FColor::Purple, TEXT("DYingMC"));
	Die(FatalDamage);
}

void ACodeFPS_Character_Base::Heal(int AddHealth)
{
	HealthPoints += AddHealth;
	if (HealthPoints > HealthMaxPoints) HealthPoints = HealthMaxPoints;
}

void ACodeFPS_Character_Base::Server_PlayAnimation_Implementation(UAnimMontage* Montage)
{
	//GEngine->AddOnScreenDebugMessage(4, 15.0f, FColor::Green, TEXT("ServAnim"));
	Multicast_PlayAnimation(Montage);
}

void ACodeFPS_Character_Base::Multicast_PlayAnimation_Implementation(UAnimMontage* Montage)
{
	float Duration = PlayAnimMontage(Montage);
	//GEngine->AddOnScreenDebugMessage(5, 15.0f, FColor::Cyan, TEXT("AnimMC"));
}


void ACodeFPS_Character_Base::Server_EnableRagdoll_Implementation()
{
	Multicast_EnableRagdoll();
}

void ACodeFPS_Character_Base::Multicast_EnableRagdoll_Implementation()
{
	GetMesh()->SetCollisionProfileName(CollisionProfileRagdoll);
	GetMesh()->SetSimulatePhysics(true);
}
void ACodeFPS_Character_Base::Server_PlaySound_Implementation(USoundBase* Sound)
{
	Multicast_PlaySound(Sound);
}
void ACodeFPS_Character_Base::Multicast_PlaySound_Implementation(USoundBase* Sound)
{
	UGameplayStatics::PlaySoundAtLocation(GetWorld(), Sound, GetActorLocation());
}
FText ACodeFPS_Character_Base::GetFaction()
{
	return Faction;
}
bool ACodeFPS_Character_Base::AnotherCharacterFromSameFaction(ACodeFPS_Character_Base* Another)
{
	return Faction.EqualTo(Another->GetFaction());
}

void ACodeFPS_Character_Base::MoveForward(float Value)
{
	if (Value != 0.0f)
	{
		if (Value <= 0.0f) SprintEnd();
		AddMovementInput(GetActorForwardVector(), Value);
	}
}

void ACodeFPS_Character_Base::MoveRight(float Value)
{
	if (Value != 0.0f)
	{
		SprintEnd();
		AddMovementInput(GetActorRightVector(), Value);
	}
}


void ACodeFPS_Character_Base::Sprint()
{
}

void ACodeFPS_Character_Base::SprintStart()
{
	if (MovementType == EMovementType::Crouch)
	{
		UnCrouch();
	}
	MovementType = EMovementType::Sprint;
	GetCharacterMovement()->MaxWalkSpeed = SprintSpeed;
}

void ACodeFPS_Character_Base::SprintEnd()
{
	MovementType = EMovementType::Walk;
	GetCharacterMovement()->MaxWalkSpeed = DefaultWalkSpeed;
}
void ACodeFPS_Character_Base::WalkStart()
{
	GetCharacterMovement()->MaxWalkSpeed = SlowWalkSpeed;
	MovementType = EMovementType::SlowWalk;
}
void ACodeFPS_Character_Base::WalkEnd()
{
	GetCharacterMovement()->MaxWalkSpeed = DefaultWalkSpeed;
	MovementType = EMovementType::Walk;
}
void ACodeFPS_Character_Base::StopMovementStart()
{
	GetCharacterMovement()->MaxWalkSpeed = 0.f;
	MovementType = EMovementType::Stop;
}
void ACodeFPS_Character_Base::StopMovementEnd()
{
	GetCharacterMovement()->MaxWalkSpeed = DefaultWalkSpeed;
	MovementType = EMovementType::Walk;
}

void ACodeFPS_Character_Base::TakeDamageLight()
{
	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("LightDamage")));
}

void ACodeFPS_Character_Base::TakeDamageMedium()
{
	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Orange, FString::Printf(TEXT("mediumDamage")));
	if (OnMediumDamageMontage != nullptr)
	{
		Server_PlayAnimation(OnMediumDamageMontage);
	}
	if (OnMediumDamageSound != nullptr)
	{
		Server_PlaySound(OnMediumDamageSound);
	}
}

void ACodeFPS_Character_Base::TakeDamageHeavy()
{
	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, FString::Printf(TEXT("HeavyDamage")));
	if (OnHeavyDamageMontage != nullptr)
	{
		Server_PlayAnimation(OnHeavyDamageMontage);
		// Movement break
	}
	if (OnHeavyDamageSound != nullptr)
	{
		Server_PlaySound(OnHeavyDamageSound);
	}
}

void ACodeFPS_Character_Base::TakeDamageFatal()
{
	
}

bool ACodeFPS_Character_Base::CheckAbilityRequirements(FAbilityInfo Ability)
{
	return ((ManaPoints > Ability.RequiredMana) && (StaminaPoints > Ability.RequiredStamina));
}

void ACodeFPS_Character_Base::Interact()
{
}

void ACodeFPS_Character_Base::Attack(FAttackInfo AttackInfo)
{
	if (AttackInfo.StopsOnAttack)
	{
		StopMovementStart();
		//GEngine->AddOnScreenDebugMessage(1, 15.0f, FColor::Red, FString::Printf(TEXT("Stopping")));
	}
	if (AttackInfo.AttackMontage != nullptr)
	{
		Server_PlayAnimation(AttackInfo.AttackMontage);
	}
	if (AttackInfo.AttackSound != nullptr)
	{
		Server_PlaySound(AttackInfo.AttackSound);
	}
	AttackInfoCurrent = AttackInfo;
	IsAttacking = true;
}

void ACodeFPS_Character_Base::OnAttackBegin()
{
}

void ACodeFPS_Character_Base::OnAttackEnd()
{
	if (AttackInfoCurrent.StopsOnAttack)
	{
		StopMovementEnd();
	}
	EventOnAttackEnded.Broadcast(AttackInfoCurrent);
	IsAttacking = false;
}

void ACodeFPS_Character_Base::UseAbility(FAbilityInfo AbilityInfo)
{
	if (CheckAbilityRequirements(AbilityInfo)) {
		if (AbilityInfo.AbilityMontage != nullptr)
		{
			Server_PlayAnimation(AbilityInfo.AbilityMontage);
		}
		if (AbilityInfo.AbilitySound != nullptr)
		{
			Server_PlaySound(AbilityInfo.AbilitySound);
		}
		AbilityInfoCurrent = AbilityInfo;
	}
}

void ACodeFPS_Character_Base::OnAbilityBegin()
{
}

void ACodeFPS_Character_Base::OnAbilityEnd()
{
}

void ACodeFPS_Character_Base::OnFire()
{
}

FVector ACodeFPS_Character_Base::GetHeadLocation()
{
	return GetMesh()->GetSocketLocation(HumanoidHeadSocket);
}


void ACodeFPS_Character_Base::Jump()
{
	Super::Jump();
}

void ACodeFPS_Character_Base::AddControllerYawInput(float Value)
{
	Super::AddControllerYawInput(Value);
}

void ACodeFPS_Character_Base::TurnAtRate(float Rate)
{
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void ACodeFPS_Character_Base::AddControllerPitchInput(float Value)
{
	Super::AddControllerPitchInput(Value);
}

void ACodeFPS_Character_Base::LookUpAtRate(float Rate)
{
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

/*
void ACodeFPS_Character_Base::Crouch()
{
	Super::Crouch();
}
void ACodeFPS_Character_Base::Uncrouch()
{
	Super::UnCrouch();
}*/

void ACodeFPS_Character_Base::Dash_Implementation()
{
}
