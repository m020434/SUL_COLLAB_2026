// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthComponent.h"

#include "Interfaces/IPluginManager.h"


// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	
}


// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                     FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UHealthComponent::TakeDamage(int Damage)
{
	CurrentHealthPoint -= Damage;

	if (CurrentHealthPoint <= 0)
	{
		// Dead
	}

	if (CurrentHealthPoint >= MaxHealthPoint)
	{
		CurrentHealthPoint = MaxHealthPoint;
	}
}

void UHealthComponent::SetHealth(int NewHealth)
{
	CurrentHealthPoint = NewHealth;

	if (CurrentHealthPoint >= MaxHealthPoint)
	{
		CurrentHealthPoint = MaxHealthPoint;
	}
}


