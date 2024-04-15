// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/TriggerVolume.h"
#include "../Interfaces/Interface_StoryItem.h"
//#include "StoryEvent.h"
#include "StoryManager.h"
#include "StoryTriggerVolume.generated.h"


UCLASS()
class CODEFPS_API AStoryTriggerVolume : public ATriggerVolume
{
	GENERATED_BODY()

protected:
		UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray <FText> Events;
		//TArray <UStoryEvent*> Events;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray <UClass*> ActivationActors;
protected:
//	UFUNCTION(BlueprintCallable)
	void OnOverlapBegin(UPrimitiveComponent* overlappedComponent, AActor* otherActor, UPrimitiveComponent* otherComp, int otherBodyIndex, bool fromSweep, const FHitResult& sweepResult);
};
