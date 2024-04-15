// Fill out your copyright notice in the Description page of Project Settings.


#include "CodeFPS_MenuPlayerController.h"

void ACodeFPS_MenuPlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (MainMenuClass)
	{
			MainMenu = CreateWidget<UCodeFPS_MainMenu>(this, MainMenuClass);
			if (MainMenu != nullptr)
			{
				MainMenu->AddToViewport();
			}
	}
}
