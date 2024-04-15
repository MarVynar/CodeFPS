// Fill out your copyright notice in the Description page of Project Settings.


#include "CodeFPS_Char_Humanoid_Base.h"
#include "Net/UnrealNetwork.h"


void ACodeFPS_Char_Humanoid_Base::BeginPlay()
{
	Super::BeginPlay();

	LArmHealthPointsCurrent = LArmHealthPointsMax;
	RArmHealthPointsCurrent = RArmHealthPointsMax;
	LLegHealthPointsCurrent = LLegHealthPointsMax;
	RLegHealthPointsCurrent = RLegHealthPointsMax;


}


void ACodeFPS_Char_Humanoid_Base::LeanLeft_Implementation()
{

}

void ACodeFPS_Char_Humanoid_Base::LeanRight_Implementation()
{

}

void ACodeFPS_Char_Humanoid_Base::Crouch()
{
	MovementType = EMovementType::Crouch;
	Super::Crouch();
}

void ACodeFPS_Char_Humanoid_Base::UnCrouch()
{
	MovementType = EMovementType::Walk;
	Super::UnCrouch();
}

ACodeFPS_Char_Humanoid_Base::ACodeFPS_Char_Humanoid_Base() :Super()
{
	EquipmentComponent = CreateDefaultSubobject<UEquipmentComponent>(TEXT("EquipmentComponent"));
}

void ACodeFPS_Char_Humanoid_Base::Die_Implementation(bool FatalDamage)
{
	Super:: Die_Implementation(FatalDamage);
	if (EquipmentComponent != nullptr)
	{
		EquipmentComponent->Server_UserDies();
	}
}

void ACodeFPS_Char_Humanoid_Base::ReloadStart()
{
	if ((EquipmentComponent != nullptr))// && !IsReloading)
	{
		IsReloading = true;
		if (OnReloadMontage != nullptr)
		{
			//GEngine->AddOnScreenDebugMessage(1, 9.0f, FColor::Orange, TEXT("OnReloadMontage"));
			Server_PlayAnimation(OnReloadMontage);
		}
		EquipmentComponent->Server_ReloadStart();
	}
}

void ACodeFPS_Char_Humanoid_Base::ReloadEnd()
{
	if (EquipmentComponent != nullptr)
	{
		EquipmentComponent->Server_ReloadEnd();
	}
	IsReloading = false;
}

void ACodeFPS_Char_Humanoid_Base::OnFire()
{
	Super:: OnFire();
	if (OnFireMontage != nullptr)
	{
		Server_PlayAnimation(OnFireMontage);
	}
}


void ACodeFPS_Char_Humanoid_Base::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ACodeFPS_Char_Humanoid_Base, IsReloading);
}