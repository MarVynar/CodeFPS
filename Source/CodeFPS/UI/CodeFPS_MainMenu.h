// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "CodeFPS_MainMenu.generated.h"

/**
 * 
 */
UCLASS()
class CODEFPS_API UCodeFPS_MainMenu : public UUserWidget
{
	GENERATED_BODY()
	
	virtual void NativeConstruct() override;

	UFUNCTION(BlueprintCallable)
		void OnExit();

	UFUNCTION(BlueprintCallable)
		void OnPlay();

	UPROPERTY(EditAnywhere, meta = (BindWidget))
		class UButton* ExitButton;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
		class UButton* PlayButton;

	//UPROPERTY(EditAnywhere, meta = (BindWidget))
	//	class UImage* BackgroundImage;

protected:
	UPROPERTY(EditAnywhere, meta = (LevelInfo))
		FName LevelToLoad;
};
