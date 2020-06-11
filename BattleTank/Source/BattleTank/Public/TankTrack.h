// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankTrack.generated.h"

/**
 * 
 */
UCLASS(meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankTrack : public UStaticMeshComponent
{
	GENERATED_BODY()
public:
	UFUNCTION(BluePrintCallable , Category = Input)
	void SetThrottle(float Throttle);
	//Max force per track in newton
	UPROPERTY(EditDefaultsOnly)
	float TrackMaxDrivingForce = 1000000;
	
	UTankTrack();
	

	void ApplySideWaysForce();

private:
	virtual void BeginPlay() override;
	
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);
	
	float CurrentThrottle = 0.0;
	void DriveTrack();
};
