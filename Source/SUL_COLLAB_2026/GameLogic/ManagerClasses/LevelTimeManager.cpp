#include "LevelTimeManager.h"


#pragma region Initialisation
	ULevelTimeManager::ULevelTimeManager()
	{
		initialLevelTime = 60.0f*2.5f; //2.5 min
		levelTimeRemaining = initialLevelTime;
	}
#pragma endregion

void ULevelTimeManager::UpdateManager(float dt)
{
	levelTimeRemaining -= dt;
	
	if(levelTimeRemaining <= 0)
	{
		levelTimeRemaining = 0; //We may still need to use this and we don't really want negative values.
		
		if(onLevelTimerExpire.IsBound()) //Let everyone know we're out of time.
		{
			onLevelTimerExpire.Broadcast();
		}
	}
}

#pragma region I/O
	void ULevelTimeManager::SetLevelTime(float time) //Probably shouldn't be used, but the option is there.
	{
		levelTimeRemaining = time;
	}

	void ULevelTimeManager::ResetLevelTime()
	{
		levelTimeRemaining = initialLevelTime;
	}

	void ULevelTimeManager::AddLevelTime(float amount)
	{
		levelTimeRemaining += amount;
	}

	float ULevelTimeManager::GetLevelTime()
	{
		return levelTimeRemaining;
	}
#pragma endregion
