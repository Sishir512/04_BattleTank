// Fill out your copyright notice in the Description page of Project Settings.
#include "Kismet/GameplayStatics.h"
#include "Projectile.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "TankAimingComponent.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UTankAimingComponent::BeginPlay() {
	Super::BeginPlay();
	LastFireTime = GetWorld()->GetTimeSeconds();
}

void UTankAimingComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) {
	//Set the logic for tank aiming component aiming or not aiming in TickComponent because we need to check it every frame
	if ((GetWorld()->GetTimeSeconds() - LastFireTime) < ReloadTimeInSeconds){
		FiringState = EFiringState::Reloading; //Red
	}
	else if (IsBarrelMoving()) {
		FiringState = EFiringState::Aiming; //Yellow
	}
	else {
		FiringState = EFiringState::Locked;  //Grren
	}

}
void UTankAimingComponent::Initialise(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet) {
	Barrel = BarrelToSet;
	Turret = TurretToSet;
}

bool UTankAimingComponent::IsBarrelMoving() {
	if (!ensure(Barrel)) { return false; }
	auto BarrelForward = Barrel->GetForwardVector();
	return !(BarrelForward.Equals(AimDirection , 0.01));  //0.01 is tolerance value

}



// Called when the game starts

void UTankAimingComponent::AimAt(FVector HitLocation) {
	/* auto OurTankName = GetOwner()->GetName();
	auto BarrelLocation = Barrel->GetComponentLocation().ToString();
	UE_LOG(LogTemp, Warning, TEXT("%s aiming at %s from %s"), *OurTankName, *(HitLocation.ToString()) , *BarrelLocation); */

	if (!ensure(Barrel && ProjectileBluePrint)) { return; }
	FVector OutLaunchVelocity;
	FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));

	//Calculate the OutLaunchVelocity
	bool bHaveAimSolution = UGameplayStatics::SuggestProjectileVelocity(
		this,
		OutLaunchVelocity,
		StartLocation,
		HitLocation,
		LaunchSpeed,
		false,
		0,
		0,
		ESuggestProjVelocityTraceOption::DoNotTrace

	);
	if(bHaveAimSolution){
		AimDirection = OutLaunchVelocity.GetSafeNormal(); //To get unit vector which determines direction to aim at
		auto TankName = GetOwner()->GetName();
		//UE_LOG(LogTemp, Warning, TEXT("%s Aiming at %s"),*TankName , *AimDirection.ToString());
		MoveBarrelTowards(AimDirection);
		auto Time = GetWorld()->GetTimeSeconds();
		//UE_LOG(LogTemp, Warning, TEXT("%f : Aim solution found "), Time);
	}
	else {
		auto Time = GetWorld()->GetTimeSeconds();
		//UE_LOG(LogTemp, Warning, TEXT("%f : No aiming component found"), Time);
	}
	
}

void UTankAimingComponent::MoveBarrelTowards(FVector AimingDirection) {
	if (!ensure(Barrel) || !ensure(Turret)) { return; }
	//Work out difference between current barrel rotation and AimDirection

	auto BarrelRotator = Barrel->GetForwardVector().Rotation();
	//auto BarrelRotator = Barrel->GetRelativeRotation(); we can use this as well
	auto AimAsRotator = AimingDirection.Rotation();
	auto DeltaRotator = AimAsRotator - BarrelRotator;
	//UE_LOG(LogTemp, Warning, TEXT("AimAsRotator : %s") , *AimAsRotator.ToString());

	Barrel->Elevate(DeltaRotator.Pitch);
	if (DeltaRotator.Yaw > 180){
		Turret->Rotate(-DeltaRotator.Yaw);
	}
	else {
		Turret->Rotate(DeltaRotator.Yaw);
	}
	

}

void UTankAimingComponent::Fire() {
	
	
	if (FiringState!=EFiringState::Reloading) {

		if (!ensure(Barrel && ProjectileBluePrint)) {
			UE_LOG(LogTemp, Warning, TEXT("ProjectileBluePrint or Barrel not found"));
			return;
		}

		//else spawn a projectile at the socket location on the barrel
		auto Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileBluePrint,
			Barrel->GetSocketLocation(FName("Projectile")),
			Barrel->GetSocketRotation(FName("Projectile"))
			);
		Projectile->LaunchProjectile(LaunchSpeed);
		LastFireTime = GetWorld()->GetTimeSeconds();
	}

}

EFiringState UTankAimingComponent::GetFiringState() const {
	return FiringState;
}



