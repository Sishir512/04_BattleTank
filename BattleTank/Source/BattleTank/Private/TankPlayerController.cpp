// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
#include "Engine/World.h"
#include "TankPlayerController.h"

void ATankPlayerController::BeginPlay() {
	Super::BeginPlay();
	auto ControlledTank = GetControlledTank();
	if (!ControlledTank) {
		UE_LOG(LogTemp, Error, TEXT("No Tank possessed"));
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("Player Controller possessing %s"), *(ControlledTank->GetName()));
	}
}

void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//UE_LOG(LogTemp , Warning , TEXT("Ticking"));
	AimTowardsCrossHair();

}


ATank* ATankPlayerController::GetControlledTank() const {
	return Cast<ATank>(GetPawn());
}

void ATankPlayerController::AimTowardsCrossHair() {
	if (!GetControlledTank()) { return; }
	FVector HitLocation;
	//Get World location of linetrace through crosshair . If it hits the landscape tell controlled tank to aim at this point .
	if (GetSightRayHitLocation(HitLocation)) {          
		GetControlledTank()->AimAt(HitLocation);
	}
	

}
bool ATankPlayerController::GetSightRayHitLocation(FVector& HitLocation) const {
	//GetWorld()->LineTraceMultiByChannel()
	//Find the Crosshair Position .
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX , ViewportSizeY);
	auto ScreenLocation = FVector2D(ViewportSizeX * CrossHairXLocation , ViewportSizeY * CrossHairYLocation); //To find the screen location of small dot i.e target of the screen
	//UE_LOG(LogTemp, Warning, TEXT("Screen Location : %s"), *(ScreenLocation.ToString()));
	//De project the screen projection of the crosshair to the world direction.
	FVector CameraWorldLocation;
	FVector WorldDirection;
	if (GetLookDirection(ScreenLocation, WorldDirection)) {
		//Line trace along that look direction and see what we hit (upto max range)
		GetLookVectorHitDirection(WorldDirection, HitLocation);
		return true;
	}
	else {
		return false;
	}
	
	 
	
}

bool ATankPlayerController::GetLookVectorHitDirection(FVector LookDirection , FVector& HitLocation) const {
	FHitResult HitResult;
	auto StartLocation = PlayerCameraManager->GetCameraLocation();
	auto EndLocation = StartLocation + (LookDirection * LineTraceRange);
	if (GetWorld()->LineTraceSingleByChannel(HitResult ,
		StartLocation ,
		EndLocation ,
		ECollisionChannel::ECC_Visibility
		)) {
		HitLocation = HitResult.Location;
		return true;
	}
	HitLocation = FVector(0.0);
	return false;
}


bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const {
	FVector CameraWorldLocation;    //Discard but nececessary
	return DeprojectScreenPositionToWorld(ScreenLocation.X, ScreenLocation.Y, CameraWorldLocation, LookDirection); //Because it returns true if direction is found
}