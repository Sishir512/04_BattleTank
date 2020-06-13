// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"


// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	//TankAimingComponent = CreateDefaultSubobject<UTankAimingComponent>(FName("Aiming Component"));
	
	

}

void ATank::BeginPlay() {  // This function is not necessary since we have changed teh architecture of the program .
	Super::BeginPlay();
	CurrentHealth = StartingHealth;
}

float ATank::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) {
	auto DamagePoint = FPlatformMath::RoundToInt(DamageAmount);
	auto DamageToApply = FMath::Clamp<int32>(DamagePoint , 0 , CurrentHealth);
	CurrentHealth -= DamageToApply;
	if (CurrentHealth <= 0) {
		UE_LOG(LogTemp, Error, TEXT("Tank dead ."));
		OnDeath.Broadcast();
	}
	
	UE_LOG(LogTemp, Error, TEXT("Health Remaining %d") , CurrentHealth);

	return DamageToApply;
}


float ATank::GetHealthPercentage() const {
	return (float)CurrentHealth / (float) StartingHealth;
}





