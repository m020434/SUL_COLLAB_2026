#include "BaseWildcard.h"

// Sets default values
ABaseWildcard::ABaseWildcard()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

void ABaseWildcard::BeginPlay()
{
	Super::BeginPlay();
}

void ABaseWildcard::RunWildcardTimer()
{
	FTimerHandle TimerHandle;
	GetWorld()->GetTimerManager().SetTimer(
		TimerHandle,
		this,
		&ABaseWildcard::OnWildcardEnd,
		Duration);
}

// Called every frame
void ABaseWildcard::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

