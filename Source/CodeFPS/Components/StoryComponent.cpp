// Fill out your copyright notice in the Description page of Project Settings.


#include "StoryComponent.h"

// Sets default values for this component's properties
UStoryComponent::UStoryComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UStoryComponent::BeginPlay()
{
	Super::BeginPlay();

	AttachedEvent->BeginPlay();
}

void UStoryComponent::ExecuteEvent()
{
	AttachedEvent->Server_ExecuteEvent();
}


/*/ Called every frame
void UStoryComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}*/

