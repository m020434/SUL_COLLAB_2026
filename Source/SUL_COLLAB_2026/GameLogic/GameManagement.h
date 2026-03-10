#pragma once

#include "CoreMinimal.h"
#include "GameManager.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "GameManagement.generated.h"

UCLASS()
class SUL_COLLAB_2026_API UGameManagement : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
/*
	#pragma region Blueprint Functions
		UFUNCTION(BlueprintCallable)
		static void StartLevel();
		
		#pragma region Getters
			UFUNCTION(BlueprintPure)
			static float GetLevelTime();
		#pragma endregion 
	#pragma endregion
*/
	//Was originally going to write getters for everything, but just giving designers the manager object is honestly probably better (and much faster for me to write in any case).
	UFUNCTION(BlueprintPure)
	static UGameManager* GetGameManager();

protected:
	static UGameManager* TryGetManager();
};
