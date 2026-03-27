// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE(F_OnDead);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class SUL_COLLAB_2026_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UHealthComponent();

	UFUNCTION(BlueprintCallable)
	void SetHealth(int NewHealth);	

	UPROPERTY(BlueprintAssignable)
	F_OnDead OnDead;
protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	
	UFUNCTION()
	void TakeDamage(AActor* damagedActor, float damageAmount, const UDamageType* damageType, AController* eventInstigator, AActor* damageCauser);
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	int MaxHealth;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int CurrentHealth;
};
