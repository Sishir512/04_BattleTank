// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"


UENUM()
enum class EFiringState : uint8 {
	Reloading , 
	Aiming , 
	Locked , 
	OutOfAmmo
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
	virtual void BeginPlay() override;

	UTankAimingComponent();
	UFUNCTION(BlueprintCallable , Category = "Setup")
	void Initialise(UTankBarrel* BarrelToSet , UTankTurret* TurretToSet );

	void AimAt(FVector HitLocation );
	UFUNCTION(BlueprintCallable)
	void Fire();

	EFiringState GetFiringState() const;
	
	UFUNCTION(BlueprintCallable)
		int GetRoundsLeft() const;

protected: 
	UPROPERTY(BlueprintReadOnly)
	EFiringState FiringState = EFiringState::Reloading;

	

private:

	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UTankBarrel* Barrel = nullptr;
	UTankTurret* Turret = nullptr;
	void MoveBarrelTowards(FVector AimingDirection);
	UPROPERTY(EditAnywhere, Category = Firing)
	float LaunchSpeed = 10000.f;
	
	FVector AimDirection;

	UPROPERTY(EditAnywhere, Category = Setup)
	TSubclassOf<AProjectile> ProjectileBluePrint;
	float ReloadTimeInSeconds = 3;
	float LastFireTime = 0;
	
	bool IsBarrelMoving();

	int RoundsLeft = 3;


};
