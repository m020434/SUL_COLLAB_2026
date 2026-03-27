// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthComponent.h"

#pragma region Initialisation
	// Sets default values for this component's properties
	UHealthComponent::UHealthComponent()
	{
		MaxHealth = 3; //Default
		CurrentHealth = MaxHealth;
	}

	// Called when the game starts
	void UHealthComponent::BeginPlay()
	{
		Super::BeginPlay();
		CurrentHealth = MaxHealth;
		
		GetOwner()->OnTakeAnyDamage.AddDynamic(this, &UHealthComponent::TakeDamage);
	}
#pragma endregion


void UHealthComponent::TakeDamage(AActor* damagedActor, float damageAmount, const UDamageType* damageType, AController* eventInstigator, AActor* damageCauser)
{
	CurrentHealth -= damageAmount;

	if(CurrentHealth <= 0)
	{
		if(OnDead.IsBound())
		{
			OnDead.Broadcast();
		}
	}

	if(CurrentHealth >= MaxHealth)
	{
		CurrentHealth = MaxHealth;
	}
}

void UHealthComponent::SetHealth(int NewHealth)
{
	CurrentHealth = NewHealth;

	if (CurrentHealth >= MaxHealth)
	{
		CurrentHealth = MaxHealth;
	}
}

