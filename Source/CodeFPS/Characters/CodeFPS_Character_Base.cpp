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

	DamageAmp = 0;

	GetMesh()->bCastDynamicShadow = true;
	GetMesh()->CastShadow = true;
	GetMesh()->SetOwnerNoSee(true);

	InteractionCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("InteractionCollision"));
	InteractionCollision->SetupAttachment(GetMesh());
	InteractionCollision->SetBoxExtent(FVector(50.0f, 80.0f, 100.0f));
	InteractionCollision->SetRelativeLocation(FVector(0.f, 65.f, 95.f));
	//AbilityComponent = CreateDefaultSubobject<UAbilityComponent>(TEXT("AbilityComponent"));
}

void ACodeFPS_Character_Base::BeginPlay()
{
	Super::BeginPlay();
	
	InteractionCollision->OnComponentBeginOverlap.AddDynamic(this, &ACodeFPS_Character_Base::OnInteractionCollisionBegin);
	InteractionCollision->OnComponentEndOverlap.AddDynamic(this, &ACodeFPS_Character_Base::OnInteractionCollisionEnd);
	/*
	TArray<AActor*> Childs;
	GetAllChildActors(Childs, true);
	for each (AActor* Iter in Childs)
	{
		if (Iter->IsA(ACodeFPS_Ability_Base::StaticClass()))
		{
			ACodeFPS_Ability_Base* AbilityTemp = Cast < ACodeFPS_Ability_Base>(Iter);
			if (AbilityTemp != nullptr)
			{
				FActorSpawnParameters spawnParameters;
				spawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
				AbilityTemp.AbilityActor = GetWorld()->SpawnActor<ACodeFPS_Proj_Base>(bulletClass, WeaponBarrel->GetComponentLocation(), AtTargetRotation, spawnParameters);
			}
		}
	}*/
	if (OnSpawnMontage != nullptr)
	{
		Server_PlayAnimation(OnSpawnMontage);
	}
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
	DOREPLIFETIME(ACodeFPS_Character_Base, DamageAmp);
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

void ACodeFPS_Character_Base::UpdateDamageAmplifier(float DamageAmpModification, bool Amplify)
{
	Server_UpdateDamageAmplifier(DamageAmp, Amplify);
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
	GEngine->AddOnScreenDebugMessage(10, 15.0f, FColor::Purple, FString::Printf(TEXT("HP , %f"), HealthPoints));
	HealthPoints -= IncomeDamage;
	//Blood on Bone location
	GEngine->AddOnScreenDebugMessage(11, 15.0f, FColor::Red, FString::Printf(TEXT("HP , %f, %f"), HealthPoints , IncomeDamage));
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

void ACodeFPS_Character_Base::Server_UpdateDamageAmplifier_Implementation(float DamageAmpModification, bool Amplify)
{
	DamageAmp = (Amplify) ? DamageAmp + DamageAmpModification : DamageAmp - DamageAmpModification;
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

void ACodeFPS_Character_Base::Server_OnDeathAnimEnded_Implementation()
{
	Multicast_OnDeathAnimEnded();
}

void ACodeFPS_Character_Base::Multicast_OnDeathAnimEnded_Implementation()
{
	OnDeathAnimEnded();
}

void ACodeFPS_Character_Base::OnDeathAnimEnded_Implementation()
{
	Destroy();
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
void ACodeFPS_Character_Base::Server_PlaySoundAtLocation_Implementation(USoundBase* Sound, FVector Location)
{
	Multicast_PlaySoundAtLocation(Sound, Location);
}
void ACodeFPS_Character_Base::Multicast_PlaySoundAtLocation_Implementation(USoundBase* Sound, FVector Location)
{
	UGameplayStatics::PlaySoundAtLocation(GetWorld(), Sound, Location);
}
FText ACodeFPS_Character_Base::GetFaction()
{
	return Faction;
}
bool ACodeFPS_Character_Base::AnotherCharacterFromSameFaction(ACodeFPS_Character_Base* Another)
{
	return Faction.EqualTo(Another->GetFaction());
}

void ACodeFPS_Character_Base::OnInteractionCollisionBegin_Implementation(UPrimitiveComponent* overlappedComponent, AActor* otherActor, UPrimitiveComponent* otherComp, int otherBodyIndex, bool fromSweep, const FHitResult& sweepResult)
{
}

void ACodeFPS_Character_Base::OnInteractionCollisionEnd_Implementation(UPrimitiveComponent* overlappedComponent, AActor* otherActor, UPrimitiveComponent* otherComp, int otherBodyIndex)
{
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
	SetMovementType(EMovementType::Sprint);
	//MovementType = EMovementType::Sprint;
	//GetCharacterMovement()->MaxWalkSpeed = SprintSpeed;
}

void ACodeFPS_Character_Base::SprintEnd()
{
	SetMovementType(EMovementType::Walk);
	//MovementType = EMovementType::Walk;
	//GetCharacterMovement()->MaxWalkSpeed = DefaultWalkSpeed;
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

void ACodeFPS_Character_Base::SetMovementType(EMovementType NewMovementType)
{
	MovementType = NewMovementType;
	switch (MovementType)
	{
	case EMovementType::Stop: GetCharacterMovement()->MaxWalkSpeed = 0.f; break;
	case EMovementType::Walk: GetCharacterMovement()->MaxWalkSpeed = DefaultWalkSpeed; break;
	case EMovementType::SlowWalk: GetCharacterMovement()->MaxWalkSpeed = SlowWalkSpeed; break;
	case EMovementType::Sprint: GetCharacterMovement()->MaxWalkSpeed = SprintSpeed; break;
	}
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
	return ((ManaPoints >= Ability.RequiredMana) && (StaminaPoints >= Ability.RequiredStamina));
}

void ACodeFPS_Character_Base::Interact()
{
}

void ACodeFPS_Character_Base::Attack(FAttackInfo AttackInfo)
{
	if (AttackInfo.StopsOnAttack)
	{
		StopMovementStart();
		GEngine->AddOnScreenDebugMessage(4, 15.0f, FColor::Red, FString::Printf(TEXT("StoppingStarted")));
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
		GEngine->AddOnScreenDebugMessage(6, 15.0f, FColor::Red, FString::Printf(TEXT("StoppingEnded")));
	}
	EventOnAttackEnded.Broadcast(AttackInfoCurrent);
//	EventOnAttackEnd.Broadcast(AttackInfoCurrent);
	IsAttacking = false;
}

/*
void ACodeFPS_Character_Base::UseAbility(FAbilityInfo AbilityInfo)
{
	//
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
		if (AbilityInfoCurrent.AbilityActor != nullptr)
		{
			AbilityInfoCurrent.AbilityActor->UseAbility();
		}
		OnAbilityBegin();
	}//
}
*/
void ACodeFPS_Character_Base::UseAbility(ACodeFPS_Ability_Base* Ability)
{
	if ((Ability != nullptr)&&(!Ability->IsActiveAbility())&&(CheckAbilityRequirements(Ability->AbilityInfo))) {
		if (Ability->AbilityInfo.AbilityMontage != nullptr)
		{
			Server_PlayAnimation(Ability->AbilityInfo.AbilityMontage);
		}
		if (Ability->AbilityInfo.AbilitySound != nullptr)
		{
			Server_PlaySound(Ability->AbilityInfo.AbilitySound);
		}
		//AbilityInfoCurrent = Ability->AbilityInfo;
		if (Ability!= nullptr) //(AbilityInfoCurrent.AbilityActor != nullptr)
		{
			//AbilityInfoCurrent.AbilityActor->UseAbility();
			Ability->UseAbility();
		}
		//OnAbilityBegin();
	}
}

void ACodeFPS_Character_Base::OnAbilityBegin()
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

void ACodeFPS_Character_Base::OnAbilityEnd()
{
}

void ACodeFPS_Character_Base::Server_AbilitySpawn_Implementation(TSubclassOf<class AActor> ActorClass, FVector SpawnLocation)
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

void ACodeFPS_Character_Base::OnFire()
{
}

FVector ACodeFPS_Character_Base::GetHeadLocation()
{
	return GetMesh()->GetSocketLocation(HumanoidHeadSocket);
}

FRotator ACodeFPS_Character_Base::GetHeadRotation()
{
	GEngine->AddOnScreenDebugMessage(9, 15.0f, FColor::Orange, FString::Printf(TEXT("Rot , %d, %d, %d"), GetMesh()->GetSocketRotation(HumanoidHeadSocket).Vector().X, GetMesh()->GetSocketRotation(HumanoidHeadSocket).Vector().Y, GetMesh()->GetSocketRotation(HumanoidHeadSocket).Vector().Z));
	GEngine->AddOnScreenDebugMessage(10, 15.0f, FColor::Yellow, FString::Printf(TEXT("RotR , %f, %f, %f"), GetMesh()->GetSocketRotation(HumanoidHeadSocket).Roll, GetMesh()->GetSocketRotation(HumanoidHeadSocket).Pitch, GetMesh()->GetSocketRotation(HumanoidHeadSocket).Yaw));

	return GetMesh()->GetSocketRotation(HumanoidHeadSocket);
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
