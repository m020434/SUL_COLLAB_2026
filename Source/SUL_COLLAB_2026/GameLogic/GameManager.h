#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "GameManager.generated.h"

class UScoreManager;
class UMultiplierManager;
class ULevelTimeManager;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(F_OnLevelStart);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(F_OnLevelStop);

UCLASS()
class SUL_COLLAB_2026_API UGameManager : public UObject
{
	GENERATED_BODY()
	
public:
	UGameManager();
	
	UFUNCTION(BlueprintCallable)
	void LevelStart();
	UFUNCTION(BlueprintCallable)
	void LevelEnd();
	
	UPROPERTY(BlueprintAssignable)
	F_OnLevelStart onLevelStart;
	UPROPERTY(BlueprintAssignable)
	F_OnLevelStop onLevelStop;
	
	void UpdateManager(float dt);
	
	#pragma region I/O
		UFUNCTION(BlueprintPure)
		UScoreManager* GetScoreManager();
		UFUNCTION(BlueprintPure)
		UMultiplierManager* GetMultiplierManager();
		UFUNCTION(BlueprintPure)
		ULevelTimeManager* GetLevelTimeManager();

		UFUNCTION(BlueprintCallable)
		void AddScore(int score);
	#pragma endregion
	
	#pragma region Events
		UFUNCTION()
		void OnLevelTimerExpired();
		UFUNCTION()
		void OnPlayerDied(APawn* playerPawn);
	#pragma endregion
	
protected:
	#pragma region Manager Refs
		UPROPERTY()
		UScoreManager* scoreManager;
		UPROPERTY()
		UMultiplierManager* multiplierManager;
		UPROPERTY()
		ULevelTimeManager* levelTimeManager;
	#pragma endregion
	
	bool levelStarted;
};