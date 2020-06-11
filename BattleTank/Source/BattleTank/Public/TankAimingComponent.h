// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"


UENUM()
enum class EFiringState : uint8 {
	Reloading , 
	Aiming , 
	Locked
};

class UTankBarrel; //Forward Declaration
class UTankTurret;
class AProjectile;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTankAimingComponent();
	UFUNCTION(BlueprintCallable , Category = "Setup")
	void Initialise(UTankBarrel* BarrelToSet , UTankTurret* TurretToSet );

	void AimAt(FVector HitLocation );
	UFUNCTION(BluePrintCallable)
	void Fire();

protected: 
	UPROPERTY(BlueprintReadOnly)
	EFiringState FiringState = EFiringState::Aiming;
private:
	UTankBarrel* Barrel = nullptr;
	UTankTurret* Turret = nullptr;
	void MoveBarrelTowards(FVector AimDirection);
	UPROPERTY(EditAnywhere, Category = Firing)
	float LaunchSpeed = 4000.f;
	

	UPROPERTY(EditAnywhere, Category = Setup)
	TSubclassOf<AProjectile> ProjectileBluePrint;
	float ReloadTimeInSeconds = 3;
	float LastFireTime = 0;
	


};
