#pragma once

#include "CoreMinimal.h"
#include "Shootable.h"
#include "GameFramework/Actor.h"
#include "ShootableTarget.generated.h"

//Forward Declaration
class UBoxComponent;

UCLASS()
class SUL_COLLAB_2026_API AShootableTarget : public AActor, public IShootable
{
	GENERATED_BODY()
	
public:	
	AShootableTarget();

protected:
	virtual void BeginPlay() override;

	// Components
	// (Using a box collider for now since there is no cylinder collider by default).
	UPROPERTY(EditAnywhere) UBoxComponent* Collider;
	UPROPERTY(EditAnywhere) UStaticMeshComponent* Mesh;

	// Parameters.
	float DistanceCutOff = 30.0f;

	// Functions
	void SetUpComponents();
	void CalculateAccuracyBonus(const FVector& HitLocation) const;

public:	
	virtual void Tick(float DeltaTime) override;
	virtual void RecieveHit(FHitResult OutHit) override;
};
