#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "MultiplierManager.generated.h"


UCLASS()
class SUL_COLLAB_2026_API UMultiplierManager : public UObject
{
	GENERATED_BODY()
	
public:
	UMultiplierManager();
	//void Mng_Init(); //BeginPlay
	
	void UpdateManager(float dt); //Allows us to control when this object thinks, so it can be paused/slowed/sped up.
	
	#pragma region I/O
		UFUNCTION(BlueprintCallable)
		void AddMult(float amount); //Can be used to add/subtract mult
		UFUNCTION(BlueprintCallable)
		void SetMult(float amount);
		UFUNCTION(BlueprintCallable)
		void ResetMult();
		
		UFUNCTION(BlueprintPure)
		float GetMult();
	#pragma endregion
	
protected:
	float currentMultiplier;
	
	float multTickInterval; //How long in-between ticks?
	float multTimeRemaining; //Remaining mult time. Usually I'd use a timestamp, but I want it to be possible to freeze this. 
	
	void MultTickDown(); //Time ran out, reduce our multiplier.
};
