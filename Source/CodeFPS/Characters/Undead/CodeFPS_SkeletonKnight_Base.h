// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../CodeFPS_Character_Base.h"
#include "../../../CodeFPS/Components/AIDecisionParametersComponent.h"
#include "CodeFPS_SkeletonKnight_Base.generated.h"


UDELEGATE(BlueprintAuthorityOnly) //BlueprintAuthorityOnly  (BlueprintCallable)
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FEventOnWarcryAnimEnded);

UCLASS()
class CODEFPS_API ACodeFPS_SkeletonKnight_Base : public ACodeFPS_Character_Base
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Mesh)
		UBoxComponent* ShieldCollision;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Mesh)
		UBoxComponent* WeaponCollision;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AttackParameters)
		UAnimMontage* BlockMontage;

	TArray<AActor*> HitTargets; //AActor? ACodeFPS_Character_Base*

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AttackParameters)
		FAttackInfo AttackSwing;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AttackParameters)
		FAttackInfo AttackStab;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AttackParameters)
		FAttackInfo AttackUppercut;

	UAIDecisionParametersComponent* DecisionComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Abilities)
	FAbilityInfo AbilityBlock;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Abilities)
	FAbilityInfo AbilityWarcry;

	void OnAttackBegin() override;

	void OnAttackEnd() override;

	//void OnAbilityBegin() override;

	//void OnAbilityEnd() override;

	bool IsBlocking;

	UFUNCTION()
	void OnShieldHit(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void OnWeaponHit(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void OnWeaponEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UFUNCTION(Server, Reliable)
		void Server_OnShieldHit(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION(Server, Reliable)
		void Server_OnWeaponHit(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

public:
	ACodeFPS_SkeletonKnight_Base();

	UFUNCTION(BlueprintCallable)
		void Block();
	UFUNCTION(BlueprintCallable)
		void BlockStart();
	//UFUNCTION(BlueprintCallable)
	//	void BlockEnd();
	UFUNCTION(BlueprintCallable)
		void Warcry();

	UPROPERTY(BlueprintAssignable)
	FEventOnWarcryAnimEnded EventOnWarcryAnimEnded;
};
