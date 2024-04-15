// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTask_FindRandomDestination.generated.h"

/**
 * 
 */
UCLASS()
class CODEFPS_API UBTTask_FindRandomDestination : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
	
	UBTTask_FindRandomDestination(const FObjectInitializer& ObjectInitializer);

	UPROPERTY(EditInstanceOnly, Category = Default)
		FBlackboardKeySelector DestinationKey;

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
