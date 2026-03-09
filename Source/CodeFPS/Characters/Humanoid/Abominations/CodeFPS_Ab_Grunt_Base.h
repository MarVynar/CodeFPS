// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../CodeFPS_Char_Humanoid_Base.h"
#include "../../../../CodeFPS/Components/AIDecisionParametersComponent.h"
#include "../../../../CodeFPS/Components/AbominationComponent.h"
#include "CodeFPS_Ab_Grunt_Base.generated.h"

/**
 * 
 */
UCLASS()
class CODEFPS_API ACodeFPS_Ab_Grunt_Base : public ACodeFPS_Char_Humanoid_Base
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Mesh)
		UBoxComponent* LeftHandCollision;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Mesh)
		UBoxComponent* RightHandCollision;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AttackParameters)
	//	UAnimMontage* ShoutMontage;

	TArray<AActor*> HitTargetsRight;
	TArray<AActor*> HitTargetsLeft;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AttackParameters)
		FAttackInfo AttackRSwordSwing;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AttackParameters)
		FAttackInfo AttackRSwordWhirl;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AttackParameters)
		FAttackInfo AttackKick;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AttackParameters)
		FAttackInfo AttackLBlunt;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AttackParameters)
		FAttackInfo AttackLShoot;

	UAIDecisionParametersComponent* DecisionComponent;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Abilities)
	//	FAbilityInfo AbilityShout;
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Abilities)
	//	bool IsEating;

	void OnAttackBegin() override;

	void OnAttackEnd() override;

	//void OnAbilityBegin() override;

	//void OnAbilityEnd() override;

	//bool IsBlocking;

	UFUNCTION()
		void OnRightHandHit(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
		void OnLeftHandHit(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
		void OnRightHandEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	UFUNCTION()
		void OnLeftHandEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UFUNCTION(Server, Reliable)
		void Server_OnRightHandHit(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION(Server, Reliable)
		void Server_OnLeftHandHit(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Equipment)
		UAbominationComponent* AbominationComponent;

public:
	ACodeFPS_Ab_Grunt_Base();

	//	UFUNCTION(BlueprintCallable)
	/*/		void Eat();
	UFUNCTION(BlueprintCallable)
		void EatStart();
	UFUNCTION(BlueprintCallable)
		void EatEnd();
	UFUNCTION(BlueprintCallable)
		void Shout();
		/*/
	//	UPROPERTY(BlueprintAssignable)
	//		FEventOnWarcryAnimEnded EventOnWarcryAnimEnded;
};
