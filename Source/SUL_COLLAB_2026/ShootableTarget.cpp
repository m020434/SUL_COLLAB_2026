#include "ShootableTarget.h"
#include "Math/UnrealMathUtility.h"
#include "Components/BoxComponent.h"



// Sets default values
AShootableTarget::AShootableTarget()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SetUpComponents();
}

// Called when the game starts or when spawned
void AShootableTarget::BeginPlay()
{
	Super::BeginPlay();
}

void AShootableTarget::SetUpComponents()
{
	// Set up collider.
	Collider = CreateDefaultSubobject<UBoxComponent>(TEXT("Collider"));
	if (Collider) Collider->SetupAttachment(RootComponent);

	// Set up mesh component.
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	if (Mesh) Mesh->SetupAttachment(RootComponent);
}

// Called every frame
void AShootableTarget::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AShootableTarget::RecieveHit(FHitResult OutHit)
{
	CalculateAccuracyBonus(OutHit.ImpactPoint);
}

void AShootableTarget::CalculateAccuracyBonus(const FVector& HitLocation) const
{
	// Check the distance between the target's origin and the bullet's hit location.
	float DistanceFromOrigin = FVector::Dist(HitLocation, GetActorLocation());

	// Don't do anything if the distance is too far.
	if (DistanceFromOrigin > DistanceCutOff) return;

	// Calculate bonus as percentage.
	float AccuracyBonus = FMath::GetRangePct(0.0f, DistanceCutOff, DistanceFromOrigin);

	// Return the value.
	// (Nothing is using this currently, so it's printed out as a log.)
	UE_LOG(LogTemp, Log, TEXT("Accuracy Bonus: %f"), AccuracyBonus); 
}

