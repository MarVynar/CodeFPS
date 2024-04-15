// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/TargetPoint.h"
#include "CodeFPS_Waypoint.generated.h"

/**
 * 
 */
UCLASS()
class CODEFPS_API ACodeFPS_Waypoint : public ATargetPoint
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		int Number;
};
