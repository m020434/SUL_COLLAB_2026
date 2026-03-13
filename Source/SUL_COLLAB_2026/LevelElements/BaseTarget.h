#pragma once

#include "Math/UnrealMathUtility.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SUL_COLLAB_2026/Shootable.h"
#include "BaseTarget.generated.h"

// Forward Declaration
class UBoxComponent;

UCLASS()
class SUL_COLLAB_2026_API ABaseTarget : public AActor, public IShootable
{
	GENERATED_BODY()
	
public:	
	ABaseTarget();

protected:
	virtual void BeginPlay() override;

	// Components
	UPROPERTY(EditAnywhere) UBoxComponent* Collider;
	UPROPERTY(EditAnywhere) UStaticMeshComponent* Mesh;

	void SetUpComponents();
	virtual void RecieveHit(FVector HitLocation) override;
	
	UFUNCTION(BlueprintImplementableEvent) void OnTargetHit(float HitAccuracy);
	UFUNCTION(BlueprintCallable) float CalculateAccuracyBonus(UCurveFloat* Curve, float HitAccuracy);

public:	
	virtual void Tick(float DeltaTime) override;

};
