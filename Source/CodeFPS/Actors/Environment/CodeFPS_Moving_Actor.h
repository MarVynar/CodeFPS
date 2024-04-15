// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CodeFPS_Moving_Actor.generated.h"

USTRUCT(BlueprintType)
struct FMovementInfo
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Mesh)
	UStaticMeshComponent* Mesh;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USoundBase* FireSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray <FTransform> MovementPoints;
};

UCLASS()
class CODEFPS_API ACodeFPS_Moving_Actor : public AActor
{
	GENERATED_BODY()
	
public:	
	ACodeFPS_Moving_Actor();

protected:
	virtual void BeginPlay() override;

public:	
	UFUNCTION(BlueprintNativeEvent, Category = "Movement")
	void PlayMovement();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray <FMovementInfo> MovementInfoPoints;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool IsLooping;
};
