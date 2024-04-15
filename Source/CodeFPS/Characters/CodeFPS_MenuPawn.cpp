// Fill out your copyright notice in the Description page of Project Settings.


#include "CodeFPS_MenuPawn.h"

// Sets default values
ACodeFPS_MenuPawn::ACodeFPS_MenuPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ACodeFPS_MenuPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACodeFPS_MenuPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ACodeFPS_MenuPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

