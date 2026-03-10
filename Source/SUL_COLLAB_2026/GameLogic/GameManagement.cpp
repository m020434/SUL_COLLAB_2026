#include "GameManagement.h"

#include "DefaultGameMode.h"
#include "GameManager.h"
#include "Kismet/GameplayStatics.h"

UGameManager* UGameManagement::GetGameManager()
{
	return TryGetManager(); //This doesn't need to be 2 methods, that's just leftover from my old code, which I haven't cleaned up yet.
}

#pragma region Internal

	UGameManager* UGameManagement::TryGetManager()
	{
		#if WITH_EDITOR
			if(ADefaultGameMode* gm = Cast<ADefaultGameMode>(UGameplayStatics::GetGameMode(GWorld )) )
			{
				return gm->gameManager;
			}
		#else
			if(ADefaultGameMode* gm = Cast<ADefaultGameMode>(UGameplayStatics::GetGameMode(GEngine->GetWorldContexts()[0].World())) )
			{
				return gm->gameManager;
			}
		#endif
		
		UE_LOG(LogTemp, Error, TEXT("Tried to use a function that requires UGameManager, but the current GameMode isn't based on DefaultGameMode.cpp, so it doesn't exist."))
		return nullptr;
	}
#pragma endregion