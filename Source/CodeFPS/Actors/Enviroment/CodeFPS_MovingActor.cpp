// Fill out your copyright notice in the Description page of Project Settings.


#include "CodeFPS_MovingActor.h"

// Sets default values
ACodeFPS_MovingActor::ACodeFPS_MovingActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ACodeFPS_MovingActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACodeFPS_MovingActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

