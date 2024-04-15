// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "StoryEvent.h"
#include "StoryManager.generated.h"

UCLASS()
class CODEFPS_API UStoryManager : public UObject
{
	GENERATED_BODY()
	
		TArray <UStoryEvent*> Events;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool StoryCompleted { false };

public:
	UFUNCTION()
		void ExecuteEvent(UStoryEvent* Event);
	UFUNCTION()
		void AddEvent(UStoryEvent* Event);
	UFUNCTION(BlueprintNativeEvent, Category = "Storyline")
		void CompleteStoryline();
};
