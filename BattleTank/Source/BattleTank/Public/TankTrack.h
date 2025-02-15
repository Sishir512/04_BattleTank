// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankTrack.generated.h"

/**
 *
 */

class ASprungWheel;
UCLASS(meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankTrack : public UStaticMeshComponent
{
	GENERATED_BODY()
public:
	UFUNCTION(BluePrintCallable, Category = Input)
		void SetThrottle(float Throttle);
	//Max force per track in newton
	UPROPERTY(EditDefaultsOnly)
		float TrackMaxDrivingForce = 1600000;

	UTankTrack();


	void ApplySideWaysForce();

private:
	
	void DriveTrack(float CurrentThrottle);

	TArray<ASprungWheel*> GetWheels();
};
