#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "DefaultGameMode.generated.h"

class UGameManager;
class APlayerStart; 

DECLARE_DYNAMIC_MULTICAST_DELEGATE(F_OnGameModeReady);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(F_OnPlayerRespawn);

UCLASS()
class SUL_COLLAB_2026_API ADefaultGameMode : public AGameMode
{
	GENERATED_BODY()
	ADefaultGameMode();
	virtual void BeginPlay() override;
	virtual void Tick(float dt) override;
	
public:
	UPROPERTY(BlueprintReadOnly)
	UGameManager* gameManager;
	
	UPROPERTY(BlueprintAssignable)
	F_OnPlayerRespawn OnPlayerRespawn;
	
	UPROPERTY(BlueprintReadWrite)
	APlayerStart* currentPlayerStart;
	
	UFUNCTION(BlueprintCallable)
	void InvokeBinding();
protected:
	virtual AActor* FindPlayerStart_Implementation(AController* Player, const FString& IncomingName) override;

	
};
