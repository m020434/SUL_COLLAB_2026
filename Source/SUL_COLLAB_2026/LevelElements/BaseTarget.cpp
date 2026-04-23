#include "BaseTarget.h"
#include "Components/BoxComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"
#include "SUL_COLLAB_2026/DEBUG/DB.h"

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
	#pragma region up collider.
		Collider = CreateDefaultSubobject<UBoxComponent>(TEXT("Collider"));
		//if (Collider) Collider->SetupAttachment(RootComponent);
		SetRootComponent(Collider);

		//Set up default parameters.
		Collider->SetBoxExtent(FVector(100.0, 10.0, 100.0));
		Collider->SetCollisionResponseToAllChannels(ECR_Block); // Not sure if this is the ideal way to set collisions.
	#pragma endregion
	
	// Set up mesh component.
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	if (Mesh) Mesh->SetupAttachment(Collider);
}

void ABaseTarget::ReceiveShot(FVector HitLocation)
{
	float worldTime = UKismetSystemLibrary::GetGameTimeInSeconds(GetWorld());
	if(LastHit + 0.01f > worldTime) return; //Protection from double-collision
	
	//LastHit
	// Get distance from centre and hit position.
	float HitAccuracy = FVector::Dist(HitLocation, GetActorLocation());

	#pragma region Calculate Scale multiplier
		//There has to be some way to grab these values from the transform directly, but FTransform seems to be completely undocumented (Thanks Epic), so this is the *working* way I've found.
		FTransform transform = GetTransform();	
		FVector pos;
		FRotator ang;
		FVector scale;
		UKismetMathLibrary::BreakTransform(transform, pos, ang, scale);

		//If these values are different design-wise behaviour is essentially undefined, so the max works well enough.
		float fScale = UKismetMathLibrary::Max(UKismetMathLibrary::Max(scale.X, scale.Y), scale.Z);
	#pragma endregion

	// Call the event.
	OnTargetHit(HitAccuracy / fScale);
	
	LastHit = worldTime;
}

float ABaseTarget::CalculateAccuracyBonus(UCurveFloat* Curve, float HitAccuracy)
{
	if(Curve == nullptr) //This crashes the editor, and cost me a lot of time hunting for the issue - j
	{
		UE_LOG(LogTemp, Error, TEXT("CalculateAccuracyBonus called with no Curve"))
		return 0;
	}
	
	// Get accuracy bonus value from the curve that is passed in.
	float AccuracyBonus = Curve->GetFloatValue(HitAccuracy);

	return AccuracyBonus;
}


void ABaseTarget::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

