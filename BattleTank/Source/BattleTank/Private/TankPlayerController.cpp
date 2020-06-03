// Fill out your copyright notice in the Description page of Project Settings.

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
	FVector OutHitLocation;
	if (GetSightRayHitLocation(OutHitLocation)) {                                          //Has side effect , is going to line trace .
		//UE_LOG(LogTemp, Warning, TEXT("Look direction : %s") , *(OutHitLocation.ToString()));
	}
	//Get World location of linetrace through crosshair . If it hits the landscape tell controlled tank to aim at this point .

}
bool ATankPlayerController::GetSightRayHitLocation(FVector& OutHitLocation) const {
	//GetWorld()->LineTraceMultiByChannel()
	//Find the Crosshair Position .
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX , ViewportSizeY);
	auto ScreenLocation = FVector2D(ViewportSizeX * CrossHairXLocation , ViewportSizeY * CrossHairYLocation); //To find the screen location of small dot i.e target of the screen
	UE_LOG(LogTemp, Warning, TEXT("Screen Location : %s"), *(ScreenLocation.ToString()));
	//De project the screen projection of the crosshair to the world direction.
	//Line trace along that look direction and see what we hit (upto max range) 
	return true;
}