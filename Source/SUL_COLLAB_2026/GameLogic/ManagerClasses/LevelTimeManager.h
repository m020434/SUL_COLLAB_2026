#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "LevelTimeManager.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(F_OnLevelTimerExpire);

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
	
protected:
	float initialLevelTime; //How long the level is (to reset to)
	float levelTimeRemaining;
};
