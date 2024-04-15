// Fill out your copyright notice in the Description page of Project Settings.


#include "CodeFPS_Char_Player.h"
#include "Animation/AnimInstance.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/Character.h" //
#include "GameFramework/CharacterMovementComponent.h" //
#include "GameFramework/InputSettings.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "MotionControllerComponent.h"
#include "XRMotionControllerBase.h" // for FXRMotionControllerBase::RightHandSourceId

DEFINE_LOG_CATEGORY_STATIC(LogFPChar, Warning, All);

ACodeFPS_Char_Player::ACodeFPS_Char_Player()
{
	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);

	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->SetupAttachment(GetMesh(), HumanoidHeadSocket);
	//FirstPersonCameraComponent->SetRelativeLocation(FVector(-39.56f, 1.75f, 64.f)); // Position the camera // -7 , -5, -147
	FirstPersonCameraComponent->bUsePawnControlRotation = true;

	//GetMesh()->SetOwnerNoSee(true);
	GetMesh()->bCastHiddenShadow = true;

	Mesh1P = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CharacterMesh1P"));
	Mesh1P->SetOnlyOwnerSee(true);
	//Mesh1P->SetOwnerNoSee(true);
	Mesh1P->SetupAttachment(FirstPersonCameraComponent);
	Mesh1P->bCastDynamicShadow = false;
	Mesh1P->CastShadow = false;
	Mesh1P->SetRelativeRotation(FRotator(1.9f, -19.19f, 5.2f));
	Mesh1P->SetRelativeLocation(FVector(-0.5f, -4.4f, -155.7f));

	GunOffset = FVector(100.0f, 0.0f, 10.0f);

}

float ACodeFPS_Char_Player::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	GEngine->AddOnScreenDebugMessage(7, 10.0f, FColor::Red, FString::Printf(TEXT("income Damage %f"), HealthPoints));
	float result = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	if (PlayerHUD != nullptr)
	{
		GEngine->AddOnScreenDebugMessage(8, 10.0f, FColor::Red, FString::Printf(TEXT("Got Damage: %f"), HealthPoints));
		PlayerHUD->SetHealth(HealthPoints, HealthMaxPoints);
		PlayerHUD->SetShield(ShieldPoints, ShieldMaxPoints);
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(9, 10.0f, FColor::Red, FString::Printf(TEXT("no HUD")));
	}
	return result;
}

void ACodeFPS_Char_Player::ReloadEnd()
{
	Super::ReloadEnd();
	if (PlayerHUD != nullptr)
	{
		PlayerHUD->SetAmmo(EquipmentComponent->GetAmmoInClipCurrent(), EquipmentComponent->GetAmmoInClipMax());
	}
}

void ACodeFPS_Char_Player::ReloadStart()
{
	Super::ReloadStart();

	if (OnReloadMontageFP != nullptr)
		{
			UAnimInstance* AnimInstance = Mesh1P->GetAnimInstance();
			if (AnimInstance != nullptr)
			{
				AnimInstance->Montage_Play(OnReloadMontageFP, 1.f);
			}
		}
}

void ACodeFPS_Char_Player::BeginPlay()
{ 
	Super::BeginPlay();

	if (bUsingMotionControllers)
	{
		Mesh1P->SetHiddenInGame(true, true);
	}
	else
	{
		Mesh1P->SetHiddenInGame(false, true); // Here(false, true);
	} 

	if (PlayerHUDClass)
	{
		APlayerController* controller = GetController<APlayerController>();

		if (controller != nullptr)
		{
			PlayerHUD = CreateWidget<UCodeFPS_PlayerUI_Widget>(controller, PlayerHUDClass);
			if (PlayerHUD != nullptr)
			{
				PlayerHUD->AddToViewport();
				PlayerHUD->SetHealth(HealthPoints, HealthMaxPoints);
				PlayerHUD->SetMana(ManaPoints, ManaMaxPoints);
				PlayerHUD->SetShield(ShieldPoints, ShieldMaxPoints);
				PlayerHUD->SetAmmo(EquipmentComponent->GetAmmoInClipCurrent(), EquipmentComponent->GetAmmoInClipMax());
			}
		}
	}
	//GEngine->AddOnScreenDebugMessage(7, 10.0f, FColor::Magenta, FString::Printf(TEXT("BegPlay %f"), HealthPoints));
}

void ACodeFPS_Char_Player::OnFire()
{
	Super:: OnFire();
	if (MovementType != EMovementType::Sprint)
	{
		UWorld* const World = GetWorld();
		if (World != nullptr)
		{
			const FRotator SpawnRotation = GetControlRotation();

			const FVector SpawnLocation = ((FP_MuzzleLocation != nullptr) ? FP_MuzzleLocation->GetComponentLocation() : GetActorLocation()) + SpawnRotation.RotateVector(GunOffset);

			FActorSpawnParameters ActorSpawnParams;
			ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;

			// spawn the projectile at the muzzle
			//World->SpawnActor<ACodeFPSProjectile>(ProjectileClass, SpawnLocation, SpawnRotation, ActorSpawnParams);
			
		}


		if (OnFireMontageFP != nullptr)
		{
			UAnimInstance* AnimInstance = Mesh1P->GetAnimInstance();
			if (AnimInstance != nullptr)
			{
				AnimInstance->Montage_Play(OnFireMontageFP, 1.f);
			}
		}
		Server_OnFire();
		PlayerHUD->SetAmmo(EquipmentComponent->GetAmmoInClipCurrent(), EquipmentComponent->GetAmmoInClipMax());
	}
}

void ACodeFPS_Char_Player::Server_OnFire_Implementation()
{
	/*
	if (OnFireMontageFP != nullptr)
	{
		// Get the animation object for the arms mesh
		UAnimInstance* AnimInstance = Mesh1P->GetAnimInstance();
		if (AnimInstance != nullptr)
		{
			AnimInstance->Montage_Play(OnFireMontageFP, 1.f);
		}
	}*/ //3person
	EquipmentComponent->FireCurrentWeapon();
}

void ACodeFPS_Char_Player::MoveForward(float Value)
{
	if (Value != 0.0f)
	{
		if (Value < 0 && MovementType == EMovementType::Sprint) SprintEnd();
		AddMovementInput(GetActorForwardVector(), Value);
	}
}

void ACodeFPS_Char_Player::MoveRight(float Value)
{
	if (Value != 0.0f)
	{
		if (MovementType == EMovementType::Sprint) SprintEnd();
		AddMovementInput(GetActorRightVector(), Value);
	}
}

void ACodeFPS_Char_Player::Interact()
{
	FHitResult Hit;

	FCollisionQueryParams CollisionQueryParams;
	CollisionQueryParams.AddIgnoredActor(this);
	CollisionQueryParams.bTraceComplex = false;

	FCollisionResponseParams CollisionResponseParams;

	GetWorld()->LineTraceSingleByChannel(
		Hit,
		GetActorLocation(),
		GetActorLocation() + FirstPersonCameraComponent->GetComponentRotation().Vector() * 500.0f,
		ECollisionChannel::ECC_Visibility,
		CollisionQueryParams,
		CollisionResponseParams
	);

	if (GEngine)
	{
		if (Hit.bBlockingHit)
		{
			GEngine->AddOnScreenDebugMessage(2, 1.0f, FColor::Blue, FString::Printf(TEXT("LineTrace Hit with %s"), *Hit.Actor.Get()->GetName()));
		}
		else
		{
			GEngine->AddOnScreenDebugMessage(2, 1.0f, FColor::Blue, TEXT("LineTrace no Hit"));
		}
	}

	//Implements interface ?/In Parent
	if (Hit.GetActor()->GetClass()->ImplementsInterface(UInterface_Interactive::StaticClass()))
	{
		Cast<IInterface_Interactive>(Hit.GetActor())->Interact();
		IInterface_Interactive::Execute_Interact(Hit.GetActor()); //for Blueprint Implementation
	}
}

void ACodeFPS_Char_Player::TurnAtRate(float Rate)
{
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void ACodeFPS_Char_Player::LookUpAtRate(float Rate)
{
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

void ACodeFPS_Char_Player::Sprint()
{
	if (MovementType != EMovementType::Sprint) {

		SprintStart();
	}
	else {
		SprintEnd();

	}
}

void ACodeFPS_Char_Player::SprintStart()
{
	Super::SprintStart();
	/*
	IsSprinting = true;
	GetCharacterMovement()->MaxWalkSpeed = SprintSpeed;
	if (bIsCrouched) 
	{
		UnCrouch();
	}*/
}

void ACodeFPS_Char_Player::SprintEnd()
{
	Super::SprintEnd();
}

bool ACodeFPS_Char_Player::CanJumpInternal_Implementation() const
{
	return bIsCrouched || Super::CanJumpInternal_Implementation();
}
void ACodeFPS_Char_Player::OnJumped_Implementation()
{
	if (bIsCrouched) 
	{
		UnCrouch();
	}
}
void ACodeFPS_Char_Player::Die_Implementation(bool FatalDamage)
{
	Super::Die_Implementation(FatalDamage);
	DisableInput(GetWorld()->GetFirstPlayerController());
}
/*
void ACodeFPS_Char_Player::Dash()
{
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Dash"));
	//AddMovementInput(GetActorForwardVector(), ForwardValue*DashDistance);
	//AddMovementInput(GetActorRightVector(), RightValue*DashDistance);

	//

	//float DirectionLength = 100.0f;
	//FVector ForwardDirection = GetActorForwardVector();
	AddActorWorldOffset(GetActorForwardVector() * ForwardValue * DashDistance * GetWorld()->GetDeltaSeconds(), true);
	//FVector RightDirection = GetActorRightVector() * DashDistance;

	AddActorWorldOffset(GetActorRightVector() * DashDistance * RightValue * GetWorld()->GetDeltaSeconds(), true);
	//

}*/

void ACodeFPS_Char_Player::Scope()
{
}
/*
void ACodeFPS_Char_Player::AddWeapon(ACodeFPSWeaponBase* Weapon)
{
	//GEngine->AddOnScreenDebugMessage(2, 1.0f, FColor::Yellow, FString::Printf(TEXT("ACube Overs with %s"), *OtherActor->GetName()), true, FVector2D(1.0f));

	AmmoMap.Add(Weapon->GetAmmoType(), Weapon->GetAmmoInClipMax());
}*/

void ACodeFPS_Char_Player::ToggleCrouch(bool ToCrouch)
{
	if(ToCrouch)
	{
		Crouch();
		//FirstPersonCameraComponent->SetRelativeLocation(FVector(-39.56f, 1.75f, 40.f)); //40 //-28
		if (MovementType == EMovementType::Sprint)
		{
			SprintEnd();
		}
	}
	else
	{
		UnCrouch();
		//FirstPersonCameraComponent->SetRelativeLocation(FVector(-39.56f, 1.75f, 64.f));
	}
}

//*
void ACodeFPS_Char_Player::Crouch()
{
	Super::Crouch();
	//FirstPersonCameraComponent->SetRelativeLocation(FVector(-39.56f, 1.75f, 10.f));
	if (MovementType == EMovementType::Sprint)
	{
		SprintEnd(); // Slide?
	}

}

void ACodeFPS_Char_Player::UnCrouch()
{
	Super::UnCrouch();
	//FirstPersonCameraComponent->SetRelativeLocation(FVector(-39.56f, 1.75f, 64.f));
}

void ACodeFPS_Char_Player::AddArmor(int AddArmor)
{
	ArmorPoints += ArmorPoints;
	if (ArmorPoints > ArmorMaxPoints) ArmorPoints = ArmorMaxPoints;
}


