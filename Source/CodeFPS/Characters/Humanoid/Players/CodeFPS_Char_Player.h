// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../CodeFPS_Char_Humanoid_Base.h"
#include "../../../UI/CodeFPS_PlayerUI_Widget.h"
#include "CodeFPS_Char_Player.generated.h"

class UInputComponent;
class USkeletalMeshComponent;
class USceneComponent;
class UCameraComponent;
class UMotionControllerComponent;
class UAnimMontage;
class USoundBase;

UCLASS(config = Game)
class CODEFPS_API ACodeFPS_Char_Player : public ACodeFPS_Char_Humanoid_Base
{
	GENERATED_BODY()
	
		UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
		USkeletalMeshComponent* Mesh1P;

	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
		USceneComponent* FP_MuzzleLocation;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		UCameraComponent* FirstPersonCameraComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		UMotionControllerComponent* R_MotionController;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		UMotionControllerComponent* L_MotionController;

protected:
	virtual void BeginPlay();

	void MoveForward(float Val) override;

	void MoveRight(float Val) override;

	void Interact() override;

	void TurnAtRate(float Rate);

	void LookUpAtRate(float Rate);

public:
		ACodeFPS_Char_Player();

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
			FVector GunOffset;

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AnimationFP)
			UAnimMontage* OnFireMontageFP;
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AnimationFP)
			UAnimMontage* OnReloadMontageFP;
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AnimationFP)
			UAnimMontage* OnSprintMontageFP;

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
			uint8 bUsingMotionControllers : 1;

		UPROPERTY(EditAnywhere)
			TSubclassOf<class UCodeFPS_PlayerUI_Widget> PlayerHUDClass;

		UPROPERTY(EditAnywhere)
			class UCodeFPS_PlayerUI_Widget* PlayerHUD;

		UFUNCTION()
			void AddArmor(int AddArmor);

		void OnFire() override;

		UFUNCTION(Server, Reliable)
			void Server_OnFire();

	USkeletalMeshComponent* GetMesh1P() const { return Mesh1P; }

	UCameraComponent* GetFirstPersonCameraComponent() const { return FirstPersonCameraComponent; }

		void Sprint() override;

		void SprintStart() override;

		void SprintEnd() override;

		//virtual void OnStartCrouch(float HalfHeightAdjust,float ScaledHalfHeightAdjust) override; //IsNeeded?
		//virtual void OnEndCrouch(float HalfHeightAdjust, float ScaledHalfHeightAdjust) override; //

		virtual bool CanJumpInternal_Implementation() const override;
		virtual void OnJumped_Implementation() override;

		void Die_Implementation(bool FatalDamage) override;

		float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;
		void ReloadEnd() override;
		void ReloadStart() override;

	//UFUNCTION(BlueprintCallable)
	//	void Dash() override;

	UFUNCTION(BlueprintCallable)
		void Scope();

	//UFUNCTION(BlueprintCallable)
	//	void AddWeapon(ACodeFPSWeaponBase* Weapon);

	//UFUNCTION(BlueprintCallable)
		//void Crouch();

	void Crouch();
	void UnCrouch();
	UFUNCTION()
		void ToggleCrouch(bool ToCrouch);
};
