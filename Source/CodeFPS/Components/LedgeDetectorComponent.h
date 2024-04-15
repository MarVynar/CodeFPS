// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameFramework/Character.h"
#include "LedgeDetectorComponent.generated.h"

USTRUCT(BlueprintType)
struct FLedgeDescription
{
	GENERATED_BODY()

		UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "LedgeDescription")
		FVector Location;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "LedgeDescription")
		FRotator Rotation;

};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CODEFPS_API ULedgeDetectorComponent : public UActorComponent
{
	GENERATED_BODY()

		ACharacter* Owner;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;	

	//UPROPERTY(EditDefaultsOnly, BlueprintGetter, Category = "Detection Settings", meta = (UIMin = 0.0f, ClampMin = 0.0f))
		float MinLedgeHeight = 40.0f;

	//UPROPERTY(EditDefaultsOnly, BlueprintGetter, Category = "Detection Settings", meta = (UIMin = 0.0f, ClampMin = 0.0f))
		float MaxLedgeHeight = 200.0f;

public:

	bool DetectLedge(OUT FLedgeDescription& LedgeDescription);
};
