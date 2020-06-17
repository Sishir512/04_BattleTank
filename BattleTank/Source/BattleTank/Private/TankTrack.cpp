// Fill out your copyright notice in the Description page of Project Settings.


#include "TankTrack.h"
#include "SprungWheel.h"
#include "SpawnPoint.h"


UTankTrack::UTankTrack() {
	PrimaryComponentTick.bCanEverTick = false;
}


/*void UTankTrack::BeginPlay() {
	Super::BeginPlay();
	OnComponentHit.AddDynamic(this, &UTankTrack::OnHit);

}
*/


//This function gets called every frame even though its not inside TickComponent .
/*void UTankTrack::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit) {
	//UE_LOG(LogTemp, Warning, TEXT("Hit"));
	DriveTrack();
	ApplySideWaysForce();
	CurrentThrottle = 0.0f;
} */


/*void UTankTrack::ApplySideWaysForce()
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
*/



void UTankTrack::SetThrottle(float Throttle) {

	float CurrentThrottle = FMath::Clamp<float>(Throttle, -1.8, 1.8);
	//UE_LOG(LogTemp, Warning, TEXT("Throttle = %f"), CurrentThrottle);
	DriveTrack(CurrentThrottle);
	
}

void UTankTrack::DriveTrack(float CurrentThrottle) {
	

	auto ForceApplied = TrackMaxDrivingForce * CurrentThrottle;
	auto Wheels = GetWheels();
	auto ForcePerWheel = ForceApplied / Wheels.Num();
	for (ASprungWheel* Wheel : Wheels) {
		Wheel->AddDrivingForce(ForcePerWheel);
	}
}

TArray<ASprungWheel*> UTankTrack::GetWheels() {
	TArray<ASprungWheel*> ResultArray;
	TArray<USceneComponent*> Children;
	GetChildrenComponents(true, Children);
	for (USceneComponent* Child : Children)
	{
		auto SpawnPointChild = Cast<USpawnPoint>(Child);
		if (!SpawnPointChild) continue;

		AActor* SpawnedChild = SpawnPointChild->GetSpawnedActor();
		auto SprungWheel = Cast<ASprungWheel>(SpawnedChild);
		if (!SprungWheel) continue;

		ResultArray.Add(SprungWheel);
	}
	return ResultArray;
}
