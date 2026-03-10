#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "ScoreManager.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(F_OnScoreChanged, int, newScore, int, oldScore);

UCLASS()
class SUL_COLLAB_2026_API UScoreManager : public UObject
{
	GENERATED_BODY()

public:
	UScoreManager();
	
	#pragma region I/O
		UFUNCTION(BlueprintCallable)
		void AddScore(int add, float mult); //Input is signed so this can be used to subtract too.
		UFUNCTION(BlueprintCallable)
		void SetScore(int newVal);
		UFUNCTION(BlueprintCallable)
		void ResetScore();
	#pragma endregion
	
	UPROPERTY(BlueprintAssignable)
	F_OnScoreChanged OnScoreChanged;
	
protected:
	int currentScore;
private:
	void BroadcastScoreChange(int oldScore);
};
