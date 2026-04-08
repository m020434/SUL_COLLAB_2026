#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseWildcard.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(F_WildcardFinished);

UCLASS()
class SUL_COLLAB_2026_API ABaseWildcard : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseWildcard();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Properties
	UPROPERTY(EditAnywhere) FName Name;
	UPROPERTY(EditAnywhere) unsigned int Cost;
	UPROPERTY(EditAnywhere) float Duration;
	UPROPERTY(EditAnywhere) UTexture2D* CardTexture;
	
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	// Blueprint Events
	UFUNCTION(BlueprintImplementableEvent) void OnWildcardActivate();
	UFUNCTION(BlueprintImplementableEvent) void OnWildcardEnd();

	// Functions
	UFUNCTION(BlueprintCallable) void RunWildcardTimer();
	UFUNCTION(BlueprintCallable) void ActivateWildcard(); // Call this function to activate the wildcard.
	
	// Event Dispatcher
	UPROPERTY(BlueprintCallable) F_WildcardFinished WildcardFinished;
};
