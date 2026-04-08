#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "DefaultGameMode.generated.h"

class UGameManager;

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
	
	UPROPERTY(BlueprintReadWrite)
	APlayerStart* currentPlayerStart;
protected:
	virtual AActor* FindPlayerStart_Implementation(AController* Player, const FString& IncomingName) override;
};
