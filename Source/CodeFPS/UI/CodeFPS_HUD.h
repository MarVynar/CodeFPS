// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "Components/ProgressBar.h"
#include "CodeFPS_HUD.generated.h"

/**
 * 
 */
UCLASS()
class CODEFPS_API ACodeFPS_HUD : public AHUD
{
	GENERATED_BODY()

public:
	ACodeFPS_HUD();

	/** Primary draw call for the HUD */
	virtual void DrawHUD() override;

private:
	/** Crosshair asset pointer */
	class UTexture2D* CrosshairTex;
};
