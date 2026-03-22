  #include "ScoreManager.h"


UScoreManager::UScoreManager()
{
	currentScore = 0;
}

#pragma region I/O
	void UScoreManager::AddScore(int add, float mult)
	{
		int oldScore = currentScore;
		currentScore += (add * mult);
		
		BroadcastScoreChange(oldScore);
	}

	void UScoreManager::SetScore(int newVal)
	{
		int oldScore = currentScore;
		currentScore = newVal;

		BroadcastScoreChange(oldScore);
	}

	void UScoreManager::ResetScore()
	{
		int oldScore = currentScore;
		currentScore = 0; //If designers ever need this to be different, this is where that logic would be defined.
		
		BroadcastScoreChange(oldScore);
	}
#pragma endregion

void UScoreManager::BroadcastScoreChange(int oldScore)
{
	if(OnScoreChanged.IsBound())
	{
		OnScoreChanged.Broadcast(currentScore, oldScore);
	}
}
