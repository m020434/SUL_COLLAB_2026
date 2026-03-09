// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class SUL_COLLAB_2026_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UHealthComponent();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	int MaxHealthPoint;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int CurrentHealthPoint;
	
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	
	
public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
	void TakeDamage(int Damage);
	UFUNCTION(BlueprintCallable)
	void SetHealth(int NewHealth);
};
