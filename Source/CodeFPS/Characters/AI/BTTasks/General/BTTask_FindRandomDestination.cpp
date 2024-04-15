// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_FindRandomDestination.h"
#include "../../CodeFPS_AIController_Base.h"
#include "../../../CodeFPS_Character_Base.h"
#include "NavigationSystem.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTask_FindRandomDestination::UBTTask_FindRandomDestination(const FObjectInitializer& ObjectInitializer)
{
	NodeName = "Get Random Destination";

	DestinationKey.AddObjectFilter(this, GET_MEMBER_NAME_CHECKED(UBTTask_FindRandomDestination, DestinationKey), AActor::StaticClass());
	DestinationKey.AddVectorFilter(this, GET_MEMBER_NAME_CHECKED(UBTTask_FindRandomDestination, DestinationKey));
}

EBTNodeResult::Type UBTTask_FindRandomDestination::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	ACodeFPS_AIController_Base* Controller = Cast<ACodeFPS_AIController_Base>(OwnerComp.GetOwner());
	if (Controller == nullptr)
	{
		EBTNodeResult::Failed;
	}

	float PatrolRadius = Controller->GetPatrolRadius();

	if (PatrolRadius > 0.f)
	{
		FNavLocation ResultLocation;

		if (UNavigationSystemV1::GetNavigationSystem(&OwnerComp)->GetRandomReachablePointInRadius(Controller->GetNavAgentLocation(), PatrolRadius, ResultLocation))
		{
			ACodeFPS_Character_Base* Character = Cast<ACodeFPS_Character_Base>(Controller->GetPawn());
			if (Character == nullptr)
			{
				EBTNodeResult::Failed;
			}

			//FVector  Destination = GetRandomReachablePointInRadius(UObject * WorldContextObject, const FVector & Origin, float Radius, ANavigationData * NavData, TSubclassOf < UNavigationQueryFilter>);
			Controller->GetBlackboardComponent()->SetValueAsVector(Controller->GetLocationKey(), ResultLocation.Location);

			return EBTNodeResult::Succeeded;
		}
	}
	return EBTNodeResult::Failed;
}
