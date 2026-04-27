#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "LevelTimeManager.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(F_OnLevelTimerExpire);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(F_OnLevelTimerTick);

UCLASS()
class SUL_COLLAB_2026_API ULevelTimeManager : public UObject
{
	GENERATED_BODY()
	
public:
	ULevelTimeManager();
	
	void UpdateManager(float dt);

	#pragma region I/O
		UFUNCTION(BlueprintCallable)
		void SetLevelTime( float time );
		UFUNCTION(BlueprintCallable)
		void ResetLevelTime();
		UFUNCTION(BlueprintCallable)
		void AddLevelTime( float amount ); //Also allows subtraction
		
		UFUNCTION(BlueprintPure)
		float GetLevelTime();
	#pragma endregion
	
	UPROPERTY(BlueprintAssignable)
	F_OnLevelTimerExpire onLevelTimerExpire;
	UPROPERTY(BlueprintAssignable) //Only runs while the timer is running
	F_OnLevelTimerTick onLevelTimerUpdate;
protected:
	UPROPERTY(BlueprintReadWrite)
	float initialLevelTime; //How long the level is (to reset to)
	float levelTimeRemaining;
	
	UPROPERTY(BlueprintReadWrite)
	float timeForgiveStart;
	UPROPERTY(BlueprintReadWrite)
	float timeForgiveRatio;
};
