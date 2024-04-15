// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "CodeFPS_DoubleDoor.generated.h"

UCLASS()
class CODEFPS_API ACodeFPS_DoubleDoor : public AActor
{
	GENERATED_BODY()
	
public:	
	ACodeFPS_DoubleDoor();

protected:
	virtual void BeginPlay() override;

	TArray<ACodeFPS_Char_Humanoid_Base*> CharsInRange;

	UFUNCTION(Server, Reliable)
	void AddToCharsList(ACodeFPS_Char_Humanoid_Base* Char);

public:	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Mesh)
	UStaticMeshComponent* RootMesh;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Mesh)
	UStaticMeshComponent* Mesh1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Mesh)
	UStaticMeshComponent* Mesh2;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Mesh)
	UBoxComponent* Collision;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USoundBase* OpenSound;

	UFUNCTION(BlueprintNativeEvent, Category = "Movement")
	void PlayMovement(bool Forward);
	UFUNCTION(NetMulticast, Reliable, BlueprintCallable, Category = "Movement")
	void Open();
	UFUNCTION(NetMulticast, Reliable, BlueprintCallable, Category = "Movement")
	void Close();
	UFUNCTION(Server, Reliable, BlueprintCallable, Category = "Movement")
	void Server_Open();
	UFUNCTION(Server, Reliable, BlueprintCallable, Category = "Movement")
	void Server_Close();

	UFUNCTION()
	void OnCollisionOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void OnCollisionEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);


	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool IsOpen;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool CanBeOpened;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FTransform OffsetToAdd;
};
