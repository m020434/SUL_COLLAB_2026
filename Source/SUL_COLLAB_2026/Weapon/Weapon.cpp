// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon.h"

#include "Components/ArrowComponent.h"

// Sets default values
AWeapon::AWeapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultSceneRoot"));
	SetRootComponent(SceneComponent);
	
	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	MeshComp->SetupAttachment(GetRootComponent());

	FirePoint = CreateDefaultSubobject<UArrowComponent>(TEXT("FirePoint"));
	FirePoint->SetupAttachment(GetRootComponent());
	FirePoint->SetRelativeLocation(FVector(0, 0, 0));
}

// Called when the game starts or when spawned
void AWeapon::BeginPlay()
{
	CurrentMag = MagSize;
	Super::BeginPlay();
}

// Called every frame
void AWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AWeapon::ShootingAnimation_Implementation()
{
	
}

void AWeapon::ReloadAnimation_Implementation()
{
	
}

void AWeapon::SetBullet_Implementation(int NumberOfBullet)
{
	CurrentMag = NumberOfBullet;
}

void AWeapon::Reloading_Implementation()
{
	ReloadAnimation();
	GetWorldTimerManager().SetTimer(ReloadTimer, this, &AWeapon::Reload, ReloadCooldown);
}

void AWeapon::ResetShootCooldown_Implementation()
{
	CanShoot = true;
}

void AWeapon::Reload_Implementation()
{
	CurrentMag = MagSize;
	ResetShootCooldown();
}

void AWeapon::Shoot_Implementation()
{
	if (CanShoot)
	{
		CanShoot = false;

		FVector Location = FirePoint->GetComponentLocation();
		FRotator Rotation = FirePoint->GetComponentRotation();
		GetWorld()->SpawnActor(ProjectilePrefab, &Location, &Rotation);

		CurrentMag--;

		ShootingAnimation();
		
		if (CurrentMag <= 0)
		{
			Reloading();
		}

		else
		{
			GetWorldTimerManager().SetTimer(CooldownTimer, this, &AWeapon::ResetShootCooldown, FireRate);
		}
	}
}

