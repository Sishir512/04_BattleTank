// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

//Forward declaration
class UTankBarrel;
class UTankTurret;
class UTankAimingComponent;
class AProjectile;
class UTankMovementComponent;

UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

public:
	
	

	void AimAt(FVector HitLocation);

	UFUNCTION(BluePrintCallable)
	void Fire();
	
protected:
	UPROPERTY(BlueprintReadOnly)
	UTankAimingComponent* TankAimingComponent = nullptr;
	


private:
	
	// Sets default values for this pawn's properties
	ATank();


	

	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = Firing)
	float LaunchSpeed = 4000.f;

	UPROPERTY(EditAnywhere , Category = Setup)
	TSubclassOf<AProjectile> ProjectileBluePrint;

	//Local barrel reference for spawning projectile
	UTankBarrel* Barrel = nullptr;
	float ReloadTimeInSeconds = 3;
	float LastFireTime = 0;

};
