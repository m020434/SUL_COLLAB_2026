// Fill out your copyright notice in the Description page of Project Settings.


#include "DefaultGameMode.h"
#include "GameManager.h"
#include "GameFramework/PlayerStart.h"
#include "Kismet/GameplayStatics.h"
#include "SUL_COLLAB_2026/DEBUG/DB.h"

ADefaultGameMode::ADefaultGameMode()
{
	//gameManager = NewObject<UGameManager>();
}

void ADefaultGameMode::BeginPlay()
{
	Super::BeginPlay();
	
	//Create manager
	gameManager = NewObject<UGameManager>();
}

void ADefaultGameMode::Tick(float dt)
{
	//Update managers
	gameManager->UpdateManager(dt);
}

AActor* ADefaultGameMode::FindPlayerStart_Implementation(AController* Player, const FString& IncomingName)
{
	if(currentPlayerStart == nullptr)
	{
		return Super::FindPlayerStart_Implementation(Player, "LevelStart");
	}
	
	
	return currentPlayerStart;
}