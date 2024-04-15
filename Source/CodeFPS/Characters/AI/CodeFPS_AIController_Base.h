// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "CodeFPS_AIController_Base.generated.h"

UCLASS()
class CODEFPS_API ACodeFPS_AIController_Base : public AAIController
{
	GENERATED_BODY()

public:
	const float GetPatrolRadius() const { return PatrolRadius; }
	const FName& GetLocationKey() const { return LocationKey; }
	const FName& GetDetectedEnemyKey() const { return DetectedEnemyKey; }

protected:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		float PatrolRadius;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		FName LocationKey;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		FName DetectedEnemyKey;
};
