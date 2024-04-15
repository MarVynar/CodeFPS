// Fill out your copyright notice in the Description page of Project Settings.


//#include "Components/SpellCastingComponent.h"
#include "SpellCastingComponent.h"

void USpellCastingComponent::SelectSpell()
{
}

// Sets default values for this component's properties
USpellCastingComponent::USpellCastingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void USpellCastingComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

void USpellCastingComponent::CastSpell()
{
}


