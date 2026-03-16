// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Projectile.h"
#include "GameFramework/Actor.h"
#include "Weapon.generated.h"

class UStaticMeshComponent;
class UArrowComponent;

UCLASS()
class SUL_COLLAB_2026_API AWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWeapon();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<AProjectile> ProjectilePrefab;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float FireRate;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int MagSize;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	UStaticMeshComponent* MeshComp;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	UArrowComponent* FirePoint;

	UPROPERTY(VisibleDefaultsOnly, BlueprntReadOnly)
	FTimerHandle CooldownTimer;
	UPROPERTY(VisibleDefaultsOnly, BlueprntReadOnly)
	FTimerHandle ReloadTimer;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	int CurrentMag;

	bool CanShoot = true;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void Shoot();
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void Reload();
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void ResetShootCooldown();
};
