// Fill out your copyright notice in the Description page of Project Settings.


#include "StrikerGameMode.h"
#include "Blueprint/UserWidget.h"
#include "TimerManager.h"
#include "Kismet/GameplayStatics.h"


void AStrikerGameMode::BeginPlay()
{
	Super::BeginPlay();

    StartGame();
}

void AStrikerGameMode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}