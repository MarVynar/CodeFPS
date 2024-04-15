// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../CodeFPS_Character_Base.h"
#include "../../../CodeFPS/Components/AIDecisionParametersComponent.h"
#include "CodeFPS_SkeletonKnight_Base.generated.h"

UCLASS()
class CODEFPS_API ACodeFPS_SkeletonKnight_Base : public ACodeFPS_Character_Base
{
	GENERATED_BODY()

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Mesh)
		UBoxComponent* ShieldCollision;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Mesh)
		UBoxComponent* WeaponCollision;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AttackParameters)
		UAnimMontage* BlockMontage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AttackParameters)
		FAttackInfo AttackSwing;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AttackParameters)
		FAttackInfo AttackStab;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AttackParameters)
		FAttackInfo AttackUppercut;

	UAIDecisionParametersComponent* DecisionComponent;

	FAbilityInfo AbilityBlock;

	void OnAttackBegin() override;

	void OnAttackEnd() override;

	void OnAbilityBegin() override;

	void OnAbilityEnd() override;

	bool IsBlocking;

	UFUNCTION()
	void OnShieldHit(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void OnWeaponHit(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

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
};
