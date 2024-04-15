// Fill out your copyright notice in the Description page of Project Settings.


#include "EquipmentItem_Base.h"

AEquipmentItem_Base::AEquipmentItem_Base()
{
	PrimaryActorTick.bCanEverTick = true;

}

void AEquipmentItem_Base::BeginPlay()
{
	Super::BeginPlay();
	
}

void AEquipmentItem_Base::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

/*
void AEquipmentItem_Base::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	{
		//Player->AddWeapon(this);
		if (DestroyOnPick)
		{
			Destroy();
		} 
	}
}*/