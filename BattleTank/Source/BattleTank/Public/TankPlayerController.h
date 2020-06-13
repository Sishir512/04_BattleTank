// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

/**
 *Responsible for helping the player aim

 */
class ATank;
class UTankAimingComponent;
UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
protected:
	

	UFUNCTION(BlueprintImplementableEvent, Category = "Setup")
	void FoundAimingComponent(UTankAimingComponent* AimingCompRef);
private:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	//Start the tank moving towards barrel so that a shot would hit where the crosshair intersects the world 
	void AimTowardsCrossHair();
	//Return an out parameter . true if hit landscape

	bool GetSightRayHitLocation(FVector& OutHitLocation) const;
	UPROPERTY(EditAnywhere)
	float CrossHairXLocation = 0.5;
	UPROPERTY(EditAnywhere)
	float CrossHairYLocation = 0.3333;
	UPROPERTY(EditAnywhere)
	float LineTraceRange = 1000000.f;
	bool GetLookDirection(FVector2D ScreenLocation, FVector& WorldDirection) const;
	bool GetLookVectorHitDirection(FVector LookDirection, FVector& HitLocation) const;

	UFUNCTION()
	void OnTankDeath();
};
