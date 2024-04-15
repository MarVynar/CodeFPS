// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "EquipmentItem_Base.generated.h"

UCLASS(Abstract, NotBlueprintable)
class CODEFPS_API AEquipmentItem_Base : public AActor
{
	GENERATED_BODY()
	
public:	
	AEquipmentItem_Base();

protected:
	virtual void BeginPlay() override;

	//UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Mesh)
	//	USkeletalMeshComponent* MeshComponent; //Skeletal or Static?
	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Collision)
	//	UBoxComponent* CollisionComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		bool DestroyOnPick;


public:	
	virtual void Tick(float DeltaTime) override;

	//UFUNCTION()
	//	void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
};
