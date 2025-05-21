// Fill out your copyright notice in the Description page of Project Settings.


#include "ControllerPlayer.h"
#include "Blueprint/UserWidget.h"

void AControllerPlayer::BeginPlay()
{
	Super::BeginPlay();

    HUD = CreateWidget(this, HUDClass);
    if(HUD != nullptr){
        HUD->AddToViewport();
    }
}