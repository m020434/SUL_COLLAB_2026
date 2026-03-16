// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile.h"

#include "Components/SphereComponent.h"

#include "Components/StaticMeshComponent.h"

#include "GameFramework/ProjectileMovementComponent.h"

// Sets default values
AProjectile::AProjectile()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	
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
	OnHit(OtherActor);
}

void AProjectile::OnHit_Implementation(AActor* OtherActor)
{
	
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

