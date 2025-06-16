// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_SetSpeed.h"
#include "../../CodeFPS_AIController_Base.h"
#include "../../../CodeFPS_Character_Base.h"
#include "NavigationSystem.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTask_SetSpeed::UBTTask_SetSpeed(const FObjectInitializer& ObjectInitializer)
{
	NodeName = "Set Speed";

	AIState.AddObjectFilter(this, GET_MEMBER_NAME_CHECKED(UBTTask_SetSpeed, AIState), AActor::StaticClass());
	AIState.AddVectorFilter(this, GET_MEMBER_NAME_CHECKED(UBTTask_SetSpeed, AIState));
}

EBTNodeResult::Type UBTTask_SetSpeed::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	ACodeFPS_AIController_Base* Controller = Cast<ACodeFPS_AIController_Base>(OwnerComp.GetOwner());
	if (Controller == nullptr)
	{
		EBTNodeResult::Failed;
	}

	ACodeFPS_Character_Base* Character = Cast<ACodeFPS_Character_Base>(Controller->GetPawn());
	if (Character == nullptr)
	{
		EBTNodeResult::Failed;
	}
	/*
	float PatrolRadius = Controller->GetPatrolRadius();

	if (PatrolRadius > 0.f)
	{
		FNavLocation ResultLocation;

		if (UNavigationSystemV1::GetNavigationSystem(&OwnerComp)->GetRandomReachablePointInRadius(Controller->GetNavAgentLocation(), PatrolRadius, ResultLocation))
		{
			//FVector  Destination = GetRandomReachablePointInRadius(UObject * WorldContextObject, const FVector & Origin, float Radius, ANavigationData * NavData, TSubclassOf < UNavigationQueryFilter>);
			Controller->GetBlackboardComponent()->SetValueAsVector(Controller->GetLocationKey(), ResultLocation.Location);

			return EBTNodeResult::Succeeded;
		}
	}
	return EBTNodeResult::Failed;*/
	return EBTNodeResult::Succeeded;
}
