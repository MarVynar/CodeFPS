// Fill out your copyright notice in the Description page of Project Settings.


#include "StoryEvent.h"
#include "Kismet/GameplayStatics.h"
#include "../Core/CodeFPS_GameMode.h"

void UStoryEvent::BeginPlay()
{
   // if (RequiredEvents.Num() == 0) // RequiredEvents.IsEmpty()
   // {
        ACodeFPS_GameMode* Mode = Cast<ACodeFPS_GameMode>(UGameplayStatics::GetGameMode(GetWorld()));
        Mode->StoryManager->AddEvent(this);
   // }
}

FText UStoryEvent::GetName()
{
    return Name;
}

void UStoryEvent::SetActive(bool Active)
{
    IsActive = Active;
}

bool UStoryEvent::GetActive()
{
    return IsActive;
}

bool UStoryEvent::CheckRequirementsForEvent(UStoryEvent* Event)
{
    if (RequiredEvents.Contains(Event))
    {
        RequiredEvents.Remove(Event);
        if (RequiredEvents.Num() == 0)
        {
            IsActive = true;
        }

        return true;
    }
    return false;
}

void UStoryEvent::Server_ExecuteEvent_Implementation()
{
    //if (IsActive)
        ExecuteEvent();
        //EventExecutedDelegate.Broadcast();//???
        EventExecutedDelegate.Broadcast(this);
        IsActive = false;
}

void UStoryEvent::ExecuteEvent_Implementation()
{
    //Server_ExecuteEvent //???
   // EventExecutedDelegate.Broadcast();
   // IsActive = false;

}
