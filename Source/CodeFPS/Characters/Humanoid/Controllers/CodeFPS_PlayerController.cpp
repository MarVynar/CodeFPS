// Fill out your copyright notice in the Description page of Project Settings.


#include "CodeFPS_PlayerController.h"

void ACodeFPS_PlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	// Bind fire event
	InputComponent->BindAction("Fire", IE_Pressed, this, &ACodeFPS_PlayerController::OnFire);
	//PlayerInputComponent->BindAction("SelectPistol", IE_Pressed, this, &ACodeFPS_PlayerController::SelectPistol);
	//PlayerInputComponent->BindAction("SelectShotgun", IE_Pressed, this, &ACodeFPS_PlayerController::SelectShotgun);
	//PlayerInputComponent->BindAction("SelectRifle", IE_Pressed, this, &ACodeFPS_PlayerController::SelectRifle);

	InputComponent->BindAction("Dash", IE_Pressed, this, &ACodeFPS_PlayerController::Dash);

	// Enable touchscreen input
	//EnableTouchscreenMovement(InputComponent);

	//PlayerInputComponent->BindAction("ResetVR", IE_Pressed, this, &ACodeFPS_PlayerController::OnResetVR);

	// Bind movement events
	InputComponent->BindAxis("MoveForward", this, &ACodeFPS_PlayerController::MoveForward);
	InputComponent->BindAxis("MoveRight", this, &ACodeFPS_PlayerController::MoveRight);

	InputComponent->BindAxis("Turn", this, &ACodeFPS_PlayerController::AddControllerYawInput);
	InputComponent->BindAxis("TurnRate", this, &ACodeFPS_PlayerController::TurnAtRate);
	InputComponent->BindAxis("LookUp", this, &ACodeFPS_PlayerController::AddControllerPitchInput);
	InputComponent->BindAxis("LookUpRate", this, &ACodeFPS_PlayerController::LookUpAtRate);

	InputComponent->BindAction("Jump", IE_Pressed, this, &ACodeFPS_PlayerController::Jump);
	InputComponent->BindAction("Jump", IE_Released, this, &ACodeFPS_PlayerController::StopJumping);

	InputComponent->BindAction("Sprint", IE_Pressed, this, &ACodeFPS_PlayerController::SprintStart);
	InputComponent->BindAction("Sprint", IE_Released, this, &ACodeFPS_PlayerController::SprintEnd);

	InputComponent->BindAction("Crouch", IE_Pressed, this, &ACodeFPS_PlayerController::Crouch);
	InputComponent->BindAction("Crouch", IE_Released, this, &ACodeFPS_PlayerController::Uncrouch);

	InputComponent->BindAction("Reload", IE_Pressed, this, &ACodeFPS_PlayerController::ReloadStart);
}

void ACodeFPS_PlayerController::SetPawn(APawn* InPawn)
{
	Super::SetPawn(InPawn);
	CachedCharacter = Cast<ACodeFPS_Char_Player>(InPawn);
}


void ACodeFPS_PlayerController::Jump()
{
	if (CachedCharacter!= nullptr) //
	{
		CachedCharacter->Jump();
	}
}

void ACodeFPS_PlayerController::StopJumping()
{
	if (CachedCharacter != nullptr) //
	{
		CachedCharacter->StopJumping();
	}
}

void ACodeFPS_PlayerController::MoveForward(float Val)
{
	if (CachedCharacter != nullptr)
	{
		CachedCharacter->MoveForward(Val);
	}
}

void ACodeFPS_PlayerController::MoveRight(float Val) 
{
	if (CachedCharacter != nullptr)
	{
		CachedCharacter->MoveRight(Val);
	}
}

void ACodeFPS_PlayerController::AddControllerYawInput(float Val)
{
	if (CachedCharacter != nullptr)
	{
		CachedCharacter->AddControllerYawInput(Val);
	}
}

void ACodeFPS_PlayerController::TurnAtRate(float Rate)
{
	if (CachedCharacter != nullptr)
	{
		CachedCharacter->TurnAtRate(Rate);
	}
}

void ACodeFPS_PlayerController::AddControllerPitchInput(float Val)
{
	if (CachedCharacter != nullptr)
	{
		CachedCharacter->AddControllerPitchInput(Val);
	}
}

void ACodeFPS_PlayerController::LookUpAtRate(float Rate) 
{
	if (CachedCharacter != nullptr)
	{
		CachedCharacter->LookUpAtRate(Rate);
	}
}

void ACodeFPS_PlayerController::SprintStart()
{
	if (CachedCharacter != nullptr)
	{
		CachedCharacter->SprintStart();
	}
}

void ACodeFPS_PlayerController::SprintEnd()
{
	if (CachedCharacter != nullptr)
	{
		CachedCharacter->SprintEnd();
	}
}

void ACodeFPS_PlayerController::Dash()
{
	if (CachedCharacter != nullptr)
	{
		CachedCharacter->Dash();
	}
}

void ACodeFPS_PlayerController::OnFire()
{
	if (CachedCharacter != nullptr)
	{
		CachedCharacter->OnFire();
	}
}

void ACodeFPS_PlayerController::Crouch()
{
	if (CachedCharacter != nullptr)
	{
		Cast<ACodeFPS_Char_Player>(CachedCharacter.Get())->ToggleCrouch(true);
	}
}

void ACodeFPS_PlayerController::Uncrouch()
{
	if (CachedCharacter != nullptr) //ACodeFPS_Char_Humanoid_Base
	{
		Cast<ACodeFPS_Char_Player>(CachedCharacter.Get())->ToggleCrouch(false);
	}
}

void ACodeFPS_PlayerController::ReloadStart()
{
	if (CachedCharacter != nullptr)
	{
		Cast<ACodeFPS_Char_Player>(CachedCharacter.Get())->ReloadStart();
	}
}


