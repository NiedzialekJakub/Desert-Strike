// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "PlayerCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "StrikerGameMode.generated.h"

/**
 * 
 */
UCLASS()
class DESERTSTRIKE_API AStrikerGameMode : public AGameModeBase
{
	GENERATED_BODY()

protected:
	UFUNCTION(BlueprintImplementableEvent)
	void StartGame();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
public:
	virtual void Tick(float DeltaTime) override;
};
