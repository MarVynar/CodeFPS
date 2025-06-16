// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameFramework/Character.h"
//#include "../Actors/Abilities/CodeFPS_Ability_Base.h
#include "AbilityComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CODEFPS_API UAbilityComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UAbilityComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		ACharacter* OwnerChar;

	UFUNCTION(BlueprintCallable)
		void SetOwnerCharacter(); //ACharacter* OwnerCharacter

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AbilityParameters)
	//	TArray<ACodeFPS_Ability_Base> Abilities;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
