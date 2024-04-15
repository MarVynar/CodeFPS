// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "../Story/StoryManager.h"
#include "CodeFPS_GameMode.generated.h"

UCLASS()
class CODEFPS_API ACodeFPS_GameMode : public AGameMode
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	bool MagicAllowed;

	UPROPERTY(EditAnywhere)
	bool WeaponsAllowed;

public:
	ACodeFPS_GameMode();

	UPROPERTY(EditAnywhere)
	UStoryManager* StoryManager;

	UFUNCTION()
	bool IsMagicAllowed();
	UFUNCTION()
	bool IsWeaponsAllowed();
};
