// Fill out your copyright notice in the Description page of Project Settings.
#include "TankTurret.h"
#include "TankBarrel.h"
#include "Projectile.h"
#include "TankAimingComponent.h"
#include "Tank.h"
#include <Runtime\Engine\Classes\Kismet\GameplayStatics.h>

// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	TankAimingComponent = CreateDefaultSubobject<UTankAimingComponent>(FName("Aiming Component"));

}

void ATank::SetBarrelReference(UTankBarrel* BarrelToSet) {
	TankAimingComponent->SetBarrelReference(BarrelToSet);
	Barrel = BarrelToSet;
}

void ATank::SetTurretReference(UTankTurret* TurretToSet) {
	TankAimingComponent->SetTurretReference(TurretToSet);
}


// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame

void ATank::AimAt(FVector HitLocation) {
	TankAimingComponent->AimAt(HitLocation , LaunchSpeed);
	
}

void ATank::Fire() {
	auto Time = GetWorld()->GetTimeSeconds();
	UE_LOG(LogTemp, Display, TEXT("%f Tank fires") , Time);

	if (!Barrel) {
		UE_LOG(LogTemp, Display, TEXT("No local barrel found"));
		return;
	}
	//else spawn a projectile at the socket location on the barrel
	GetWorld()->SpawnActor<AProjectile>(ProjectileBluePrint,
		Barrel->GetSocketLocation(FName("Projectile")),
		Barrel->GetSocketRotation(FName("Projectile"))
		);



}

// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

