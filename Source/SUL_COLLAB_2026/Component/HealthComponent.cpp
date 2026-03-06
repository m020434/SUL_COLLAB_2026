// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthComponent.h"
//#include "Interfaces/IPluginManager.h"


#pragma region Initialisation
	// Sets default values for this component's properties
	UHealthComponent::UHealthComponent()
	{
		MaxHealth = 3; //Default
	}

	// Called when the game starts
	void UHealthComponent::BeginPlay()
	{
		Super::BeginPlay();
		
		CurrentHealth = MaxHealth;
	}
#pragma endregion


void UHealthComponent::TakeDamage(int Damage)
{
	CurrentHealth -= Damage;

	if (CurrentHealth <= 0)
	{
		// Dead
		//TODO: A Multicast delegate here would be a good idea, we want other things to know when we die.
	}

	if (CurrentHealth >= MaxHealth)
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

