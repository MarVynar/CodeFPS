// Fill out your copyright notice in the Description page of Project Settings.


#include "CodeFPS_GameMode.h"
#include "../UI/CodeFPS_HUD.h"
#include "../Characters/Humanoid/Players/CodeFPS_Char_Player.h"
#include "UObject/ConstructorHelpers.h"

ACodeFPS_GameMode::ACodeFPS_GameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/Characters/Player/CodeFPS_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = ACodeFPS_HUD::StaticClass();
}

bool ACodeFPS_GameMode::IsMagicAllowed()
{
	return MagicAllowed;
}

bool ACodeFPS_GameMode::IsWeaponsAllowed()
{
	return WeaponsAllowed;
}
