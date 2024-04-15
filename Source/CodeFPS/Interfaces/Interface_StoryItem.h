// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Interface_StoryItem.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UInterface_StoryItem : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class CODEFPS_API IInterface_StoryItem
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintNativeEvent, Category = "Storyline")
		void ExecuteEvent();
};
