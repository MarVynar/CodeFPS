// Fill out your copyright notice in the Description page of Project Settings.


#include "CodeFPS_DoubleDoor.h"
#include "../../Characters/Humanoid/CodeFPS_Char_Humanoid_Base.h"

ACodeFPS_DoubleDoor::ACodeFPS_DoubleDoor()
{
	RootMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Root Mesh"));
	RootMesh->SetupAttachment(RootComponent);
	Mesh1= CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Door Mesh1"));
	Mesh1->SetupAttachment(RootMesh);
	Mesh2 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Door Mesh2"));
	Mesh2->SetupAttachment(RootMesh);

	Collision = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision"));
	Collision->SetBoxExtent(FVector(15.0f, 15.0f, 15.0f));
	Collision->OnComponentBeginOverlap.AddDynamic(this, &ACodeFPS_DoubleDoor::OnCollisionOverlap);		
	Collision->OnComponentEndOverlap.AddDynamic(this, &ACodeFPS_DoubleDoor::OnCollisionEndOverlap);
	Collision->SetupAttachment(RootMesh);

	CanBeOpened = true;
}

void ACodeFPS_DoubleDoor::BeginPlay()
{
	Super::BeginPlay();
	
}

void ACodeFPS_DoubleDoor::AddToCharsList_Implementation(ACodeFPS_Char_Humanoid_Base* Char)
{
	CharsInRange.AddUnique(Char);
}

void ACodeFPS_DoubleDoor::Open_Implementation()
{
	PlayMovement(true);
	GEngine->AddOnScreenDebugMessage(1, 1.0f, FColor::Green, FString::Printf(TEXT("MultiOpen")));
}

void ACodeFPS_DoubleDoor::Close_Implementation()
{
	PlayMovement(false);
}

void ACodeFPS_DoubleDoor::Server_Open_Implementation()
{
	Open();
	IsOpen = true;
	GEngine->AddOnScreenDebugMessage(0, 1.0f, FColor::Red, FString::Printf(TEXT("ServOpen")));
}

void ACodeFPS_DoubleDoor::Server_Close_Implementation()
{
	Close();
	IsOpen = false;
}

void ACodeFPS_DoubleDoor::OnCollisionOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (CanBeOpened&& !IsOpen && OtherActor->IsA(ACodeFPS_Char_Humanoid_Base::StaticClass()))
	{
		Server_Open();
	}
}

void ACodeFPS_DoubleDoor::OnCollisionEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
}

void ACodeFPS_DoubleDoor::PlayMovement_Implementation(bool Forward)
{
}


