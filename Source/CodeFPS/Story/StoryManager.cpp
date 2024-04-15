// Fill out your copyright notice in the Description page of Project Settings.


#include "StoryManager.h"

void UStoryManager::ExecuteEvent(UStoryEvent* Event)
{
	for (auto Iter : Events)
	{
		Iter->CheckRequirementsForEvent(Event);
	}
	Events.Remove(Event);
	if (Events.Num() == 0)
	{
		StoryCompleted = true;
	}
}

void UStoryManager::AddEvent(UStoryEvent* Event)
{
	Events.AddUnique(Event);
	Event->EventExecutedDelegate.AddDynamic(this, &UStoryManager::ExecuteEvent);
}

void UStoryManager::CompleteStoryline_Implementation()
{
	GEngine->AddOnScreenDebugMessage(0, 1.0f, FColor::Green, FString::Printf(TEXT("StoryCompleted")));
	//Level exit
}
