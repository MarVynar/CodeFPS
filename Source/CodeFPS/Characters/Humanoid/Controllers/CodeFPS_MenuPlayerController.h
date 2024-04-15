// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "../../../UI/CodeFPS_MainMenu.h"
#include "CodeFPS_MenuPlayerController.generated.h"

UCLASS()
class CODEFPS_API ACodeFPS_MenuPlayerController : public APlayerController
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
		TSubclassOf<class UCodeFPS_MainMenu> MainMenuClass;

	UPROPERTY(EditAnywhere)
		class UCodeFPS_MainMenu* MainMenu;
};
