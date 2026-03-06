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

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	int MaxHealth;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int CurrentHealth;

public:
	UFUNCTION(BlueprintCallable)
	void TakeDamage(int Damage);
	UFUNCTION(BlueprintCallable)
	void SetHealth(int NewHealth);
};
