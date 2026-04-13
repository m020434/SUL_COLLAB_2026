#include "MultiplierManager.h"

#pragma region Initialisation 
	UMultiplierManager::UMultiplierManager()
	{
		currentMultiplier = 1.0f;
		multTickInterval = 3.0f;
		multTimeRemaining = multTickInterval;
	}
#pragma endregion

void UMultiplierManager::UpdateManager(float dt)
{
	if(currentMultiplier <= 1) return;
	
	multTimeRemaining -= dt; 
	
	if(multTimeRemaining <= 0.0f)
	{
		MultTickDown();
	}
}

#pragma region I/O
	void UMultiplierManager::AddMult(float amount)
	{
		float oldMult = currentMultiplier;
		currentMultiplier += amount;
		
		if(onMultChanged.IsBound()) onMultChanged.Broadcast(currentMultiplier, oldMult);
	}

	void UMultiplierManager::SetMult(float amount) //Probably usually shouldn't be used, but the option is there.
	{
		float oldMult = currentMultiplier;
		currentMultiplier = amount;
		
		if(onMultChanged.IsBound()) onMultChanged.Broadcast(currentMultiplier, oldMult);
	}

	void UMultiplierManager::ResetMult()
	{
		float oldMult = currentMultiplier;
		currentMultiplier = 1;
		multTimeRemaining = multTickInterval;
		
		if(onMultChanged.IsBound()) onMultChanged.Broadcast(currentMultiplier, oldMult);
	}

	float UMultiplierManager::GetMult()
	{
		return currentMultiplier;
	}
#pragma endregion

void UMultiplierManager::MultTickDown()
{
	float oldMult = currentMultiplier;
	
	//Lose 10%, minimum of 1x
	currentMultiplier = FGenericPlatformMath::Max(currentMultiplier * 0.9f, 1);
	
	//Reset
	multTimeRemaining = multTickInterval;
	
	if(onMultChanged.IsBound()) onMultChanged.Broadcast(currentMultiplier, oldMult);
}