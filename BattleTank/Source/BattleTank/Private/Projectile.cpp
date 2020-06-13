// Fill out your copyright notice in the Description page of Project Settings.

#include "GameFramework/ProjectileMovementComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "PhysicsEngine/RadialForceComponent.h"
#include "Projectile.h"

// Sets default values
AProjectile::AProjectile()
{
	

	PrimaryActorTick.bCanEverTick = false;
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	CollisionMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("Collision Mesh"));
	SetRootComponent(CollisionMesh);
	CollisionMesh->SetNotifyRigidBodyCollision(true);  //Ticks the generate simulate hit events
	CollisionMesh->SetVisibility(true);

	LaunchBlast = CreateDefaultSubobject<UParticleSystemComponent>(FName("Launch Blast"));
	LaunchBlast->AttachToComponent(RootComponent , FAttachmentTransformRules::KeepRelativeTransform); //It is always a best idea to use AttachToComponent

	ImpactBlast = CreateDefaultSubobject<UParticleSystemComponent>(FName("Impact Blast"));
	ImpactBlast->AttachToComponent(RootComponent  , FAttachmentTransformRules::KeepRelativeTransform);
	ImpactBlast->bAutoActivate = false;

	
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(FName("Projectile Movement"));
	ProjectileMovement->bAutoActivate = false;

	ExplosionForce = CreateDefaultSubobject<URadialForceComponent>(FName("Explosion Force"));
	ExplosionForce->AttachToComponent(RootComponent , FAttachmentTransformRules::KeepRelativeTransform);
}

void AProjectile::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit) {
	LaunchBlast->Deactivate();
	ImpactBlast->Activate();
	CollisionMesh->SetVisibility(false);
	ExplosionForce->FireImpulse();

}


// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	CollisionMesh->OnComponentHit.AddDynamic(this, &AProjectile::OnHit);
	
}




void AProjectile::LaunchProjectile(float Speed)
{
	auto Time = GetWorld()->GetTimeSeconds();
	//UE_LOG(LogTemp, Warning, TEXT("%f: Projectile fires at %f"), Time, Speed);
	ProjectileMovement->SetVelocityInLocalSpace(FVector::ForwardVector * Speed);  //FVector::Forward is used to get the forward diretion of the projectile(sphere).
	//UE_LOG(LogTemp, Error, TEXT("%s"), *FVector::ForwardVector.ToString());
	ProjectileMovement->Activate();
}