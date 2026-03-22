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
	multTimeRemaining -= dt; 
	
	if(multTimeRemaining <= 0.0f)
	{
		MultTickDown();
	}
}

#pragma region I/O
	void UMultiplierManager::AddMult(float amount)
	{
		currentMultiplier += amount;
	}

	void UMultiplierManager::SetMult(float amount) //Probably usually shouldn't be used, but the option is there.
	{
		currentMultiplier = amount;
	}

	void UMultiplierManager::ResetMult()
	{
		currentMultiplier = 1;
		multTimeRemaining = multTickInterval;
	}

	float UMultiplierManager::GetMult()
	{
		return currentMultiplier;
	}
#pragma endregion

void UMultiplierManager::MultTickDown()
{
	//Lose 10%
	currentMultiplier = currentMultiplier * 0.9f;
	
	//Reset
	multTimeRemaining = multTickInterval;
}