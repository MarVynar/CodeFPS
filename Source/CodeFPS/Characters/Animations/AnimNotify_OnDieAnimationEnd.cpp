// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotify_OnDieAnimationEnd.h"
#include "../CodeFPS_Character_Base.h"

void UAnimNotify_OnDieAnimationEnd::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	ACodeFPS_Character_Base* Character = Cast<ACodeFPS_Character_Base>(MeshComp->GetOwner());
	if (Character != nullptr)
	{
		Character->Server_OnDeathAnimEnded();
	}
}