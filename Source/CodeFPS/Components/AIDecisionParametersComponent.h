// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "../Characters/CodeFPS_Character_Base.h"
#include "Components/BoxComponent.h"
#include "../Characters/AI/CodeFPS_Waypoint.h"
#include "AIDecisionParametersComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CODEFPS_API UAIDecisionParametersComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UAIDecisionParametersComponent();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Decisions)
		int DodgeChance;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Decisions)
		int BlockChance;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Decisions)
		int AttackChoice;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Parameters)
		int Aggression;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Parameters)
		float SensingRange;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Parameters)
		float CombatRange;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Parameters)
		float SafeRange;
	//float Morale;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Navigation)
		TArray<ACodeFPS_Waypoint*> Waypoints;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Navigation)
		bool LoopWaypoints;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Reaction)
		UBoxComponent* ReactionCollision;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	ACodeFPS_Character_Base* SelectedTargetCharacter;
		
};
