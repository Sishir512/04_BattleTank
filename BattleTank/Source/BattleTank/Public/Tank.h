// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

//Forward declaration


DECLARE_DYNAMIC_MULTICAST_DELEGATE(FTankDelegate);

UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

public:
	//Called when actor damage is done by Projectile through ApplyRadialDamage function
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;
		
	UFUNCTION(BlueprintPure , Category = "Setup")
	float GetHealthPercentage() const;

	FTankDelegate OnDeath;

private:
	
	// Sets default values for this pawn's properties
	ATank();
	UPROPERTY(EditDefaultsOnly)
	int32 StartingHealth = 100;
	UPROPERTY(VisibleAnywhere)
	int32 CurrentHealth;
	

	virtual void BeginPlay() override;

	

	

};
