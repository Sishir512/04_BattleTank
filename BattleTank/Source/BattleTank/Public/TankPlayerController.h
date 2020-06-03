// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Tank.h"
#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

/**
 *
 */
UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
private:
	ATank* GetControlledTank() const;
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
};
