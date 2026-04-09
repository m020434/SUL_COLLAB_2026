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
	
	void ReceiveShot(FVector HitLocation);
protected:
	virtual void BeginPlay() override;
	void SetUpComponents();

	// Components
	UPROPERTY(EditAnywhere, BlueprintReadOnly) UBoxComponent* Collider;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) UStaticMeshComponent* Mesh;

	//void ReceiveHit(UPrimitiveComponent* MyComp, AActor* Other, UPrimitiveComponent* OtherComp, bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit);
	
	UFUNCTION(BlueprintImplementableEvent) void OnTargetHit(float HitAccuracy);
	UFUNCTION(BlueprintCallable) float CalculateAccuracyBonus(UCurveFloat* Curve, float HitAccuracy);

public:	
	virtual void Tick(float DeltaTime) override;
};
