// Fill out your copyright notice in the Description page of Project Settings.


#include "CodeFPS_MainMenu.h"
#include "Kismet/GameplayStatics.h"

void UCodeFPS_MainMenu::NativeConstruct()
{
	if (ExitButton != nullptr)
	{
		ExitButton->OnClicked.AddDynamic(this, &UCodeFPS_MainMenu::OnExit);
	}

	if (PlayButton != nullptr)
	{
		PlayButton->OnClicked.AddDynamic(this, &UCodeFPS_MainMenu::OnPlay);
	}
}

void UCodeFPS_MainMenu::OnExit()
{
	//FSlateColor Color = FSlateColor(FLinearColor::MakeRandomColor());
	//BackgroundImage->SetBrushTintColor(Color);
	TEnumAsByte<EQuitPreference::Type> QuitPreference = EQuitPreference::Quit; UKismetSystemLibrary::QuitGame(GetWorld(), UGameplayStatics::GetPlayerController(GetWorld(), 0), QuitPreference, true);
}

void UCodeFPS_MainMenu::OnPlay()
{
	UGameplayStatics::OpenLevel(GetWorld(), LevelToLoad);
}

