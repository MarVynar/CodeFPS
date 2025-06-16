// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
//#include "GameFramework/Actor.h"
#include "GameFramework/Character.h"
#include "Engine/DataTable.h"
#include "CodeFPS_Ability_Base.generated.h"

//*
UENUM(BlueprintType)
enum class EAbilityEffect : uint8
{
	Damage,
	Heal,
	Shield,
	Invincibility,
	SpeedUp,
	SlowDown,
	PowerUp,
	Weaken,
	Spawn
};

class ACodeFPS_Ability_Base;

USTRUCT(BlueprintType)
struct FAbilityInfo : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AbilityParameters) // EditAnywhere, BlueprintReadWrite, Category = AttackParameters
		float AbilityRange;														// 0\-1 = self?
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AbilityParameters) // EditAnywhere, BlueprintReadWrite, Category = AttackParameters
		float AbilityAngle;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AbilityParameters)
		UAnimMontage* AbilityMontage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AbilityParameters)
		USoundBase* AbilitySound;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AbilityParameters)
		float RequiredMana;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AbilityParameters)
		float RequiredStamina;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AbilityParameters)
		EAbilityEffect AbilityEffect;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AbilityParameters)
		float EffectTime;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AbilityParameters)
		float EffectPower;
//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AbilityParameters)
	//	TSubclassOf<class AActor> ActorToSpawn;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AbilityParameters)
	TSubclassOf<class AActor> AbilityActorClass;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AbilityParameters)
	ACodeFPS_Ability_Base* AbilityActor;
};
//*/
UCLASS()
class CODEFPS_API ACodeFPS_Ability_Base : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACodeFPS_Ability_Base();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(Replicated, VisibleAnywhere, BlueprintReadOnly)
	bool IsActive;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AbilityParameters)
	FAbilityInfo AbilityInfo;

/*
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AbilityParameters) // EditAnywhere, BlueprintReadWrite, Category = AttackParameters
		float AbilityRange;														// 0\-1 = self?
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AbilityParameters) // EditAnywhere, BlueprintReadWrite, Category = AttackParameters
		float AbilityAngle;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AbilityParameters)
		UAnimMontage* AbilityMontage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AbilityParameters)
		float AbilityCooldown;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AbilityParameters)
		USoundBase* AbilitySound;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AbilityParameters)
		float RequiredMana;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AbilityParameters)
		float RequiredStamina;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AbilityParameters)
		EAbilityEffect AbilityEffect;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AbilityParameters)
		float EffectTime;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AbilityParameters)
		float EffectPower;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AbilityParameters)
		TSubclassOf<class AActor> ActorToSpawn; */
	// Particle Effect
// Particle Active Effect 
	UFUNCTION( BlueprintCallable)
		void UseAbility();
	UFUNCTION(BlueprintCallable)
		virtual void OnAbilityBegin();
	UFUNCTION(BlueprintCallable)
		virtual void OnAbilityEnd();
	UFUNCTION(Server, Reliable)
		void Server_AbilitySpawn(TSubclassOf<class AActor> ActorClass, FVector SpawnLocation);
//	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
//		void AbilityEffect();
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
		void Serv_AbilityEffect();
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
		void MC_AbilityEffect();
	UFUNCTION(Server, Reliable)
		void Server_AbilityEffect();
	UFUNCTION(NetMulticast, Reliable)
		void Multicast_AbilityEffect();
	UFUNCTION(BlueprintCallable)
		void RemoveEffect();
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
		void Serv_RemoveEffect();
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
		void MC_RemoveEffect();
	UFUNCTION(Server, Reliable)
		void Server_RemoveEffect();
	UFUNCTION(NetMulticast, Reliable)
		void Multicast_RemoveEffect();
	UFUNCTION(BlueprintCallable)
		bool IsActiveAbility();

	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
};
