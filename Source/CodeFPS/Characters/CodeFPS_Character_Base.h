// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "../Interfaces/Interface_Interactive.h"
#include "Engine/DataTable.h"
#include "CodeFPS_Character_Base.generated.h"

class UCharacterMovementComponent;

USTRUCT(BlueprintType)
struct FAttackInfo : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AttackParameters) // EditAnywhere, BlueprintReadWrite, Category = AttackParameters
		float AttackRange;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AttackParameters)
		float AttackDamage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AttackParameters)
		UAnimMontage* AttackMontage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AttackParameters)
		USoundBase* AttackSound;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AttackParameters)//, meta = (AllowPrivateAccess = "true"))
		TSubclassOf<UDamageType> DmgTypeClass;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AttackParameters)
		bool StopsOnAttack;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AttackParameters)
		FVector HitFeedback;
};

USTRUCT(BlueprintType)
struct FAbilityInfo : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AbilityParameters) // EditAnywhere, BlueprintReadWrite, Category = AttackParameters
		float AbilityRange;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AbilityParameters)
		UAnimMontage* AbilityMontage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AbilityParameters)
		USoundBase* AbilitySound;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AbilityParameters)
		float RequiredMana;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AbilityParameters)
		float RequiredStamina;
};


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FEventOnAttackEnded, FAttackInfo, AttackInfo);
DECLARE_DYNAMIC_DELEGATE_OneParam(FEventOnAttackEnd, FAttackInfo, AttackInfo);

template <typename T>
bool StructEquals(const T& First, const T& Second)
{
	return T::StaticStruct()->CompareScriptStruct(&First, &Second, 0);
}

UENUM(BlueprintType)
enum class EMovementType : uint8
{
	Stop,
	Walk,
	SlowWalk,
	Sprint,
	Crouch
};

UCLASS()
class CODEFPS_API ACodeFPS_Character_Base : public ACharacter //, public IInterface_Interactive
{
	GENERATED_BODY()

	UFUNCTION(Server, Reliable)
	void Server_TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser);

	virtual void Falling() override;
	virtual void Landed(const FHitResult& Hit) override;
	virtual void NotifyJumpApex() override;

	FVector CurrentFallApex;

public:
	ACodeFPS_Character_Base();

	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

protected:
	virtual void BeginPlay() override;

	UFUNCTION(NetMulticast, Reliable)
		void Multicast_EnableRagdoll(); 

	UFUNCTION(Server, Reliable)
		void Server_EnableRagdoll();

	UFUNCTION()
		virtual void TakeDamageLight(); // Remove BlueprintCallable// BlueprintNativeEvent ?? // transfer damaged bone?
	UFUNCTION()
		virtual void TakeDamageMedium();
	UFUNCTION()
		virtual void TakeDamageHeavy();
	UFUNCTION()
		virtual void TakeDamageFatal();

	UFUNCTION()
		bool CheckAbilityRequirements(FAbilityInfo Ability);

	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite, Category = Health)
		float HealthPoints;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Health)
		float HealthMaxPoints;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Health)
		float HealthRegenPoints;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Health)
		bool IsDead;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Health)
		class UCurveFloat* FallDamageCurve;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animations)
		class UAnimMontage* OnDeathMontage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animations)
		class UAnimMontage* OnMediumDamageMontage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animations)
		class UAnimMontage* OnHeavyDamageMontage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Audio)
		class USoundBase* OnDeathSound;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Audio)
		class USoundBase* OnMediumDamageSound;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Audio)
		class USoundBase* OnHeavyDamageSound;
	

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Armor)
		float ArmorPoints;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Armor)
		float ArmorMaxPoints;

	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite, Category = Shield)
		float ShieldPoints;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Shield)
		float ShieldMaxPoints;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Shield)
		float ShieldRegenPoints;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Shield)
		bool IsShielded;

	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite, Category = Mana)
		float ManaPoints;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Mana)
		float ManaMaxPoints;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Mana)
		float ManaRegenPoints;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Movement)
		float CrouchModifier;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Movement)
		float DefaultWalkSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Movement)
		float SlowWalkSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Movement)
		float SprintSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Movement)
		float DashDistance;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Movement)
		int DashAmount;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Movement)

	EMovementType MovementType;

	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite, Category = Stamina)
		float StaminaPoints;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stamina)
		float StaminaMaxPoints;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stamina)
		float StaminaRegenPoints;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Faction)
		FText Faction;

	FTimerHandle DeathMontageTimer;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AttackParameters)
	UDataTable* AttacksDataTable;

	FAttackInfo AttackInfoCurrent;
	FAbilityInfo AbilityInfoCurrent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool IsAttacking = false; // TEmporary, replace with Delegates

public:
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UFUNCTION(Server, Reliable)
		void Server_Die(bool FatalDamage);

	UFUNCTION(NetMulticast, Reliable)
		void Multicast_Die(bool FatalDamage) ; // Needed? +BlueprintNativeEvent

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
		void Die(bool FatalDamage);

	UFUNCTION()
		virtual void Heal(int AddHealth);

	UFUNCTION(Server, Reliable)
		void Server_PlayAnimation(UAnimMontage* Montage);

	UFUNCTION(NetMulticast, Reliable)
		void Multicast_PlayAnimation(UAnimMontage* Montage);
	UFUNCTION(Server, Reliable)
		void Server_PlaySound(USoundBase* Sound); // Into separate component?

	UFUNCTION(NetMulticast, Reliable)
		void Multicast_PlaySound(USoundBase* Sound);

	UFUNCTION(BlueprintCallable)
		FText GetFaction();
	UFUNCTION(BlueprintCallable)
		bool AnotherCharacterFromSameFaction(ACodeFPS_Character_Base* Another);

	virtual void MoveForward(float Value);

	virtual void MoveRight(float Value);

	virtual void Jump();

	virtual void AddControllerYawInput(float Value);
	virtual void TurnAtRate(float Rate);
	virtual void AddControllerPitchInput(float Value);
	virtual void LookUpAtRate(float Rate);

	UFUNCTION(BlueprintCallable)
	virtual	void Sprint();

	UFUNCTION(BlueprintCallable)
	virtual	void SprintStart();

	UFUNCTION(BlueprintCallable)
	virtual	void SprintEnd();

	UFUNCTION(BlueprintCallable)
	virtual	void WalkStart();
	
	UFUNCTION(BlueprintCallable)
	virtual	void WalkEnd();

	UFUNCTION(BlueprintCallable)
	virtual	void StopMovementStart();

	UFUNCTION(BlueprintCallable)
	virtual	void StopMovementEnd();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable) // BlueprintImplementableEvent BlueprintNativeEvent
	void Dash();

	//UFUNCTION()
	//void Crouch() override;
	//UFUNCTION()
	//void UnCrouch() override;

	UFUNCTION(BlueprintCallable)
	virtual void Attack(FAttackInfo AttackInfo);
	UFUNCTION(BlueprintCallable)
	virtual void OnAttackBegin();
	UFUNCTION(BlueprintCallable)
	virtual void OnAttackEnd();

	FEventOnAttackEnded EventOnAttackEnded;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FEventOnAttackEnd EventOnAttackEnd;

	UFUNCTION(BlueprintCallable)
		virtual void UseAbility (FAbilityInfo AbilityInfo);
	UFUNCTION(BlueprintCallable)
		virtual void OnAbilityBegin();
	UFUNCTION(BlueprintCallable)
		virtual void OnAbilityEnd();

	UFUNCTION(BlueprintCallable)
	virtual void OnFire();

	UFUNCTION(BlueprintCallable)
		FVector GetHeadLocation();

	UFUNCTION()
	virtual void Interact();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
		float BaseTurnRate;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
		float BaseLookUpRate;
};
