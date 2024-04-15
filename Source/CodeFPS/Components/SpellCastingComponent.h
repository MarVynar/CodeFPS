// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "../Characters/CodeFPS_Character_Base.h"
#include "SpellCastingComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CODEFPS_API USpellCastingComponent : public UActorComponent
{
	GENERATED_BODY()

	//ACodeFPS_Item_Weapon_Base* CurrentWeapon;
	ACodeFPS_Character_Base* OwnerCharacter;

	void SelectSpell();

public:	
	// Sets default values for this component's properties
	USpellCastingComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spells")
		TSubclassOf<class ACodeFPS_Item_Weapon_Base> SelectedSpellClass;

public:	
	
	UFUNCTION()
		void CastSpell();
		
};
