// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon.h"

#include "Components/ArrowComponent.h"

// Sets default values
AWeapon::AWeapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	MeshComp->SetupAttachment(GetRootComponent());
	MeshComp->SetRelativeLocation(FVector(0, 0, 0));

	FirePoint = CreateDefaultSubobject<UArrowComponent>(TEXT("FirePoint"));
	FirePoint->SetupAttachment(GetRootComponent());
	FirePoint->SetRelativeLocation(FVector(0, 0, 0));
}

// Called when the game starts or when spawned
void AWeapon::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AWeapon::ResetShootCooldown_Implementation()
{
	
}

void AWeapon::Reload_Implementation()
{
	
}

void AWeapon::Shoot_Implementation()
{
	
}

