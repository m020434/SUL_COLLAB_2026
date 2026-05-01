// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Weapon.generated.h"

class UStaticMeshComponent;
class UArrowComponent;
class USceneComponent;

UCLASS()
class SUL_COLLAB_2026_API AWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWeapon();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<AActor> ProjectilePrefab;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float FireRate;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float ReloadCooldown;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int MagSize;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	USceneComponent* SceneComponent;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	UStaticMeshComponent* MeshComp;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	UArrowComponent* FirePoint;

	UPROPERTY(VisibleDefaultsOnly)
	FTimerHandle CooldownTimer;
	UPROPERTY(VisibleDefaultsOnly)
	FTimerHandle ReloadTimer;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int CurrentMag;

	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	bool CanShoot = true;
	bool InReload = false;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void Shoot();
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void Reload();
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void Reloading();
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void ResetShootCooldown();
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void SetBullet(int NumberOfBullet);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void ReloadAnimation();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void ShootingAnimation();
};
