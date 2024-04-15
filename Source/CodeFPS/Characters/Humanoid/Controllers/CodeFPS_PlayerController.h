// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "../Players/CodeFPS_Char_Player.h"
#include "CodeFPS_PlayerController.generated.h"

/**
 * 
 */
UCLASS()
class CODEFPS_API ACodeFPS_PlayerController : public APlayerController
{
	GENERATED_BODY()

	TSoftObjectPtr<class ACodeFPS_Character_Base> CachedCharacter;

	void Jump();
	void StopJumping();
	void MoveForward(float Val);
	void MoveRight(float Val);

	void AddControllerYawInput(float Val);
	void TurnAtRate(float Rate);
	void AddControllerPitchInput(float Val);
	void LookUpAtRate(float Rate);

	void SprintStart();
	void SprintEnd();
	void Dash();
	void OnFire();
	void Crouch();
	void Uncrouch();

	void ReloadStart();
		
protected:
	virtual void SetupInputComponent() override;

public:
	virtual void SetPawn(APawn* InPawn) override;
};
