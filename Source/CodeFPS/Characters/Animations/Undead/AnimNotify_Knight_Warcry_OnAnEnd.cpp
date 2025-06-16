// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotify_Knight_Warcry_OnAnEnd.h"
#include "../../Undead/CodeFPS_SkeletonKnight_Base.h"
//#include "../CodeFPS_Character_Base.h"

void UAnimNotify_Knight_Warcry_OnAnEnd::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	ACodeFPS_SkeletonKnight_Base* Character = Cast<ACodeFPS_SkeletonKnight_Base>(MeshComp->GetOwner());
	if (Character != nullptr)
	{
		Character->EventOnWarcryAnimEnded.Broadcast();
	}
}

