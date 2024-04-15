// Fill out your copyright notice in the Description page of Project Settings.

#include "StoryTriggerVolume.h"

//*
void AStoryTriggerVolume::OnOverlapBegin(UPrimitiveComponent* overlappedComponent, AActor* otherActor, UPrimitiveComponent* otherComp, int otherBodyIndex, bool fromSweep, const FHitResult& sweepResult)
{
	//for (int i = 0; i< ActivationActors.Num(); i++ )
	for (auto& ClassIter : ActivationActors)
		if (otherActor->IsA(ClassIter))	//if (otherActor->IsA(ActivationActors[i]::StaticClass()))
	{
		// The other Actor is not of type AFPSCharacter
			// if Events[i] = currentEvent
			//for (auto& EventIter : Events)
	}
}//*/
