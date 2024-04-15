// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "StoryEvent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FEventExecutedDelegate, UStoryEvent*, Event);

UCLASS()
class CODEFPS_API UStoryEvent : public UObject
{
	GENERATED_BODY()

	FText Name;
	bool IsActive;

public:
	FText GetName();

	void BeginPlay();

	FEventExecutedDelegate EventExecutedDelegate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray <UStoryEvent*> RequiredEvents;

	UFUNCTION(Server, Reliable)
		void Server_ExecuteEvent();

	UFUNCTION(BlueprintNativeEvent, Category = "Storyline")
		void ExecuteEvent();

	UFUNCTION()
		void SetActive(bool Active);

	UFUNCTION()
		bool GetActive();

	UFUNCTION()
		bool CheckRequirementsForEvent(UStoryEvent* Event);
};
