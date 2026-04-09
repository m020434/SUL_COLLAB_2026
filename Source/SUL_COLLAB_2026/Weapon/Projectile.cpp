// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile.h"

#include "Components/SphereComponent.h"

#include "Components/StaticMeshComponent.h"

#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "SUL_COLLAB_2026/Shootable.h"
#include "SUL_COLLAB_2026/DEBUG/DB.h"

// Sets default values
AProjectile::AProjectile()
{
	// Create Component Object
	SphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("Collider"));
	SetRootComponent(SphereComp);

	SphereComp->SetCollisionProfileName(TEXT("BlockAllDynamic"));
	SphereComp->SetRelativeScale3D(FVector(0.5f));

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	MeshComp->SetupAttachment(GetRootComponent());
	MeshComp->SetCollisionEnabled(ECollisionEnabled::Type::NoCollision);
	MeshComp->SetRelativeScale3D(FVector(0.75f));

	ProjectileMovementComp = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile Movement"));
	ProjectileMovementComp->InitialSpeed = 1000.0f;
	ProjectileMovementComp->MaxSpeed = 1000.0f;
	ProjectileMovementComp->ProjectileGravityScale = 0.0f;
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();

	SphereComp->OnComponentHit.AddDynamic(this, &AProjectile::ProjectileHit);
}

void AProjectile::ProjectileHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	FVector NormalImpulse, const FHitResult& Hit)
{
	if (IShootable* shootable = Cast<IShootable>(OtherActor))
	{
		shootable->ReceiveShot(Hit.ImpactPoint);
	}
	
	OnHit(OtherActor, Hit);
}

void AProjectile::OnHit_Implementation(AActor* OtherActor, FHitResult HitResult)
{
	this->Destroy();
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}




