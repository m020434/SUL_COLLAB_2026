#include "GameManager.h"

#include "DefaultGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "ManagerClasses/LevelTimeManager.h"
#include "ManagerClasses/MultiplierManager.h"
#include "ManagerClasses/ScoreManager.h"


#pragma region Initialisation/Deinitialisation
	UGameManager::UGameManager()
	{	
		//Supposedly this is garbage collected
		scoreManager = NewObject<UScoreManager>();
		multiplierManager = NewObject<UMultiplierManager>();
		levelTimeManager = NewObject<ULevelTimeManager>();
		
		levelTimeManager->onLevelTimerExpire.AddDynamic(this, &UGameManager::OnLevelTimerExpired);
		
		levelStarted = false;
	}

	void UGameManager::LevelStart()
	{
		if(levelStarted)
		{
			UE_LOG(LogTemp, Error, TEXT("Tried to start the level when it was already running!"))
			return;
		}
		
		levelStarted = true;
		
		multiplierManager->ResetMult();
		levelTimeManager->ResetLevelTime();
		scoreManager->ResetScore();
		
		if(onLevelStart.IsBound())
		{
			onLevelStart.Broadcast();
		}
	}
	
	void UGameManager::LevelEnd()
	{
		levelStarted = false;
		if(onLevelStop.IsBound())
		{
			onLevelStop.Broadcast();
		}
	}
#pragma endregion

#pragma region Events
	void UGameManager::OnLevelTimerExpired()
	{
		LevelEnd();
	}
	
	void UGameManager::OnPlayerDied(APawn* playerPawn)
	{
		AController* controller = playerPawn->GetController();
		APlayerController* playerController = Cast<APlayerController>(controller);
		
		playerPawn->Destroy();
		
		if(playerController != nullptr)
		{
			if(ADefaultGameMode* gm = Cast<ADefaultGameMode>(UGameplayStatics::GetGameMode(GWorld )) )
			{
				gm->RestartPlayer(playerController);
			}
		}
	}
#pragma endregion

void UGameManager::UpdateManager(float dt) //TODO: For now this runs on-tick, but would be better if it was on a timer / only started after lvl start.
{
	if(levelStarted)
	{
		multiplierManager->UpdateManager(dt);
		levelTimeManager->UpdateManager(dt);
	}
}

#pragma region I/O
	UScoreManager* UGameManager::GetScoreManager()
	{
		return this->scoreManager;
	}
	
	UMultiplierManager* UGameManager::GetMultiplierManager()
	{
		return this->multiplierManager;
	}
	
	ULevelTimeManager* UGameManager::GetLevelTimeManager()
	{
		return this->levelTimeManager;
	}

	void UGameManager::AddScore(int score)
	{
		scoreManager->AddScore(score, multiplierManager->GetMult());
	}
#pragma endregion
