// Fill out your copyright notice in the Description page of Project Settings.


#include "TankTrack.h"

void UTankTrack::SetThrottle(float Throttle) {
	auto Name = GetName();
	UE_LOG(LogTemp, Warning, TEXT("%s Throttle") , *Name );

	auto ForceApplied = GetForwardVector() * TrackMaxDrivingForce * Throttle; //Throttle is the force by which key is pressed
	auto ForceLocation = GetComponentLocation();
	auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());  //because staticmeshcomponent's parent class is primitivecomponent and force can only be applied to primitivecomponent
	TankRoot->AddForceAtLocation(ForceApplied , ForceLocation);



}