// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../CodeFPS_Character_Base.h"
#include "../../Components/EquipmentComponent.h"
#include "CodeFPS_Char_Humanoid_Base.generated.h"

UCLASS()
class CODEFPS_API ACodeFPS_Char_Humanoid_Base : public ACodeFPS_Character_Base
{
	GENERATED_BODY()
	
protected:

	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Health)
		float LArmHealthPointsMax;
	float LArmHealthPointsCurrent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Health)
		float RArmHealthPointsMax;
	float RArmHealthPointsCurrent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Health)
		float LLegHealthPointsMax;
	float LLegHealthPointsCurrent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Health)
		float RLegHealthPointsMax;
	float RLegHealthPointsCurrent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Equipment) /////////////
		UEquipmentComponent* EquipmentComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animations)
		class UAnimMontage* OnReloadMontage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animations)
		class UAnimMontage* OnFireMontage;

	UPROPERTY(Replicated, VisibleAnywhere, BlueprintReadOnly)
	bool IsReloading = false;
	// 
	//CalculateArmor() override

public:
	ACodeFPS_Char_Humanoid_Base();
	/*
	virtual	void ReceivePointDamage(float Damage, const  UDamageType* DamageType,
		FVector HitLocation,
		FVector HitNormal,
		UPrimitiveComponent* HitComponent,
		FName BoneName,
		FVector ShotFromDirection,
		AController* InstigatedBy,
		AActor* DamageCauser,
		const FHitResult& HitInfo
	) override; //non virtual*/

	//virtual void ReceivePointDamage(float Damage, const class UDamageType* DamageType, FVector HitLocation, FVector HitNormal, class UPrimitiveComponent* HitComponent, FName BoneName, FVector ShotFromDirection, class AController* InstigatedBy, AActor* DamageCauser, const FHitResult& HitInfo) override;

	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UFUNCTION(BlueprintNativeEvent)
		void LeanLeft();

	UFUNCTION(BlueprintNativeEvent)
		void LeanRight();

	virtual void Crouch();

	virtual	void UnCrouch();

	void Die_Implementation(bool FatalDamage) override;

	//UFUNCTION(Server, Reliable)
	virtual void ReloadStart();
	virtual void ReloadEnd();

	void OnFire() override;
};
