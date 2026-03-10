// Fill out your copyright notice in the Description page of Project Settings.


#include "DefaultGameMode.h"
#include "GameManager.h"

ADefaultGameMode::ADefaultGameMode()
{
	//gameManager = NewObject<UGameManager>();
}

void ADefaultGameMode::BeginPlay()
{
	Super::BeginPlay();
	gameManager = NewObject<UGameManager>();
}

void ADefaultGameMode::Tick(float dt)
{
	Super::Tick(dt);
	
	gameManager->UpdateManager(dt);
}

