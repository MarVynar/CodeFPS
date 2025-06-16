// Fill out your copyright notice in the Description page of Project Settings.


//#include "Actors/Equipment/Weapons/Projectiles/CodeFPS_Proj_Base.h"
#include "CodeFPS_Proj_Base.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/ProjectileMovementComponent.h"

// Sets default values
ACodeFPS_Proj_Base::ACodeFPS_Proj_Base()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	//GEngine->AddOnScreenDebugMessage(3, 1.0f, FColor::Green, FString::Printf(TEXT("BaseConstructor")));
	PrimaryActorTick.bCanEverTick = true;

	CollisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	CollisionComp->InitSphereRadius(5.0f);
	CollisionComp->BodyInstance.SetCollisionProfileName("Projectile");
	CollisionComp->OnComponentHit.AddDynamic(this, &ACodeFPS_Proj_Base::OnHit);		// set up a notification for when this component hits something blocking

	// Players can't walk on it
	CollisionComp->SetWalkableSlopeOverride(FWalkableSlopeOverride(WalkableSlope_Unwalkable, 0.f));
	CollisionComp->CanCharacterStepUpOn = ECB_No;

	// Set as root component
	RootComponent = CollisionComp;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Head Mesh"));
	UStaticMesh* mesh = LoadObject<UStaticMesh>(nullptr, TEXT("/Game/StarterContent/Shapes/Shape_Sphere.Shape_Sphere"));
	Mesh->SetStaticMesh(mesh);
	Mesh->SetWorldScale3D(FVector(0.3f, 0.3f, 0.3f));
	Mesh->SetupAttachment(CollisionComp);

	// Use a ProjectileMovementComponent to govern this projectile's movement
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileComp"));
	ProjectileMovement->UpdatedComponent = CollisionComp;
	ProjectileMovement->InitialSpeed = 50000.f;
	ProjectileMovement->MaxSpeed = 50000.f;
	ProjectileMovement->bRotationFollowsVelocity = true;
	ProjectileMovement->bShouldBounce = true;

	// Die after 3 seconds by default
	InitialLifeSpan = 3.0f;
}

// Called when the game starts or when spawned
void ACodeFPS_Proj_Base::BeginPlay()
{
	Super::BeginPlay();
	GEngine->AddOnScreenDebugMessage(3, 1.0f, FColor::Green, FString::Printf(TEXT("Spawn")));
	
}

void ACodeFPS_Proj_Base::Server_OnHit_Implementation(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr) && (Shooter != nullptr) &&  (OtherActor!= Shooter))// && OtherComp->IsSimulatingPhysics())
	{
		OtherComp->AddImpulseAtLocation(GetVelocity() * 100.0f, GetActorLocation());
		DmgTypeClass = DmgTypeClass ? *DmgTypeClass : UDamageType::StaticClass();
		AController* EventInstigator = UGameplayStatics::GetPlayerController(GetWorld(), 0);
		OtherActor->TakeDamage(Damage, FDamageEvent(DmgTypeClass), EventInstigator, this);
		GEngine->AddOnScreenDebugMessage(4, 1.0f, FColor::Green, OtherActor->GetName());
		Destroy();
	}
}

// Called every frame
void ACodeFPS_Proj_Base::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACodeFPS_Proj_Base::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	//GEngine->AddOnScreenDebugMessage(4, 1.0f, FColor::Green, OtherActor->GetName());//++
	Server_OnHit(HitComp, OtherActor, OtherComp, NormalImpulse, Hit);
}

void ACodeFPS_Proj_Base::SetDamage(int IncomeDamage)
{
	this->Damage = IncomeDamage;
}

void ACodeFPS_Proj_Base::SetShooter(ACodeFPS_Character_Base* Attacker)
{
	Shooter = Attacker;
}
