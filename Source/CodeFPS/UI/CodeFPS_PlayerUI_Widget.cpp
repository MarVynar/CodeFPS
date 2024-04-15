// Fill out your copyright notice in the Description page of Project Settings.


#include "CodeFPS_PlayerUI_Widget.h"


void UCodeFPS_PlayerUI_Widget::SetHealth(int CurrentHealth, int MaxHealth)
{
	if (HealthBar != nullptr)
	{
		HealthBar->SetPercent((float)CurrentHealth / MaxHealth);
	}
}

void UCodeFPS_PlayerUI_Widget::SetMana(int CurrentMana, int MaxMana)
{
	if (ManaBar != nullptr)
	{
		if (MaxMana !=0)
			ManaBar->SetPercent((float)CurrentMana / MaxMana);
		else 
			ManaBar->SetPercent(0);
	}
}

void UCodeFPS_PlayerUI_Widget::SetShield(int CurrentShield, int MaxShield)
{
	if (ShieldBar != nullptr)
	{
		if (MaxShield != 0)
			ShieldBar->SetPercent((float)CurrentShield / MaxShield);
		else 
			ShieldBar->SetPercent(0);
	}
}

void UCodeFPS_PlayerUI_Widget::SetAmmo(int CurrentAmmo, int MaxAmmo)
{
	if (AmmoBar != nullptr)
	{
		if (MaxAmmo != 0)
			AmmoBar->SetPercent((float)CurrentAmmo / MaxAmmo);
		else 
			AmmoBar->SetPercent(0);
	}
}


