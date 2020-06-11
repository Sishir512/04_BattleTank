// Fill out your copyright notice in the Description page of Project Settings.


#include "TankTrack.h"

UTankTrack::UTankTrack() {
	PrimaryComponentTick.bCanEverTick = false;
}

void UTankTrack::BeginPlay() {
	Super::BeginPlay();
	OnComponentHit.AddDynamic(this, &UTankTrack::OnHit);

}

	



//This function gets called every frame even though its not inside TickComponent .
void UTankTrack::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit) {
	//UE_LOG(LogTemp, Warning, TEXT("Hit"));
	DriveTrack();
	ApplySideWaysForce();
	CurrentThrottle = 0.0F;
}


void UTankTrack::ApplySideWaysForce()
{
	//The function is used to reduce the slippage of the tank

	// Work-out the required acceleration this frame to correct
	auto DeltaTime = GetWorld()->DeltaTimeSeconds;
	auto SlippageSpeed = FVector::DotProduct(GetComponentVelocity(), GetRightVector());
	auto CorrectionAcceleration = -SlippageSpeed / DeltaTime * GetRightVector(); //Because we need to apply the force in opposite direction. (-SlippageSpeed /DeltaTime) because a = v/t;
																				 // Calculate and apply sideways (F = m a)
	auto TankRoot = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());  // Because GetRootComponent returns a USceneComponent which is a parent class of UStaticMeshComponent

	auto CorrectionForce = (TankRoot->GetMass() * CorrectionAcceleration) / 2; //Because there are two tracks
	TankRoot->AddForce(CorrectionForce);
}

void UTankTrack::SetThrottle(float Throttle) {

	CurrentThrottle = FMath::Clamp<float>(CurrentThrottle + Throttle, -1.8, 1.8);


}

void UTankTrack::DriveTrack() {
	auto ForceApplied = GetForwardVector() * TrackMaxDrivingForce * CurrentThrottle; //Throttle is the force by which key is pressed
	auto ForceLocation = GetComponentLocation();
	auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());  //because staticmeshcomponent's parent class is primitivecomponent and force can only be applied to primitivecomponent
	TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);
	UE_LOG(LogTemp, Error, TEXT("Track Driving"));
}
