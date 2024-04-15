// Fill out your copyright notice in the Description page of Project Settings.


#include "LedgeDetectorComponent.h"
#include "Components/CapsuleComponent.h"

// Called when the game starts
void ULedgeDetectorComponent::BeginPlay()
{
	Super::BeginPlay();

	checkf(GetOwner()->IsA<ACharacter>(), TEXT("ULedgeDetectorComponent: Only Character can be anowner"));
	Owner = StaticCast<ACharacter*> (GetOwner());	
}

bool ULedgeDetectorComponent::DetectLedge(OUT FLedgeDescription& LedgeDescription)
{
	UCapsuleComponent* CapsuleComponent = Owner->GetCapsuleComponent();
	float BottomZOffset = 2.0f;
	FVector Bottom = Owner->GetActorLocation() - (CapsuleComponent->GetScaledCapsuleHalfHeight()) *FVector::UpVector;

	float ForwardCheckCapsuleRadius = CapsuleComponent->GetScaledCapsuleRadius();
	float ForwardCheckCapsuleHalfHeight = (MaxLedgeHeight - MinLedgeHeight) / 2;

	return false;
}
