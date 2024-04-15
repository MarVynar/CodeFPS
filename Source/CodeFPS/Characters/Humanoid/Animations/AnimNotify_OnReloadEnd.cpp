// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotify_OnReloadEnd.h"
#include "../CodeFPS_Char_Humanoid_Base.h"

void UAnimNotify_OnReloadEnd::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	ACodeFPS_Char_Humanoid_Base* Humanoid = Cast<ACodeFPS_Char_Humanoid_Base>(MeshComp->GetOwner());
	if (Humanoid != nullptr)
	{
		Humanoid->ReloadEnd();
	}
}


