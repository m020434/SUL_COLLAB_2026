#include "BaseTarget.h"
#include "Components/BoxComponent.h"

// Sets default values
ABaseTarget::ABaseTarget()
{
	PrimaryActorTick.bCanEverTick = true;
	SetUpComponents();
}

void ABaseTarget::BeginPlay()
{
	Super::BeginPlay();
}

void ABaseTarget::SetUpComponents()
{
	// Set up collider.
	Collider = CreateDefaultSubobject<UBoxComponent>(TEXT("Collider"));
	if (Collider) Collider->SetupAttachment(RootComponent);

	//Set up default parameters.
	Collider->SetBoxExtent(FVector(100.0, 10.0, 100.0));
	Collider->SetCollisionResponseToAllChannels(ECR_Block); // Not sure if this is the ideal way to set collisions.
	
	// Set up mesh component.
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	if (Mesh) Mesh->SetupAttachment(RootComponent);
}

void ABaseTarget::RecieveHit(FVector HitLocation)
{
	// Get distance from centre and hit position.
	float HitAccuracy = FVector::Dist(HitLocation, GetActorLocation());

	// Call the event.
	OnTargetHit(HitAccuracy);
}


float ABaseTarget::CalculateAccuracyBonus(UCurveFloat* Curve, float HitAccuracy)
{
	// Get accuracy bonus value from the curve that is passed in.
	float AccuracyBonus = Curve->GetFloatValue(HitAccuracy);

	return AccuracyBonus;
}


void ABaseTarget::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

