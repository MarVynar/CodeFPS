// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CodeFPS_PlayerUI_Widget.generated.h"

/**
 * 
 */
UCLASS()
class CODEFPS_API UCodeFPS_PlayerUI_Widget : public UUserWidget
{
	GENERATED_BODY()
	
public: 
	UPROPERTY(EditAnywhere, meta = (BindWidget))
		class UProgressBar* HealthBar;
	UPROPERTY(EditAnywhere, meta = (BindWidget))
		class UProgressBar* ManaBar;
	UPROPERTY(EditAnywhere, meta = (BindWidget))
		class UProgressBar* ShieldBar;
	UPROPERTY(EditAnywhere, meta = (BindWidget))
		class UProgressBar* AmmoBar;


	void SetHealth(int CurrentHealth, int MaxHealth);
	void SetMana(int CurrentMana, int MaxMana);
	void SetShield(int CurrentShield, int MaxShield);
	void SetAmmo(int CurrentAmmo, int MaxAmmo);
};
