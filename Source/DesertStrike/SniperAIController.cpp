// Fill out your copyright notice in the Description page of Project Settings.
#include "SniperAIController.h"
#include "Kismet/GameplayStatics.h"
#include "Math/Vector.h"
#include "CoreMinimal.h"


void ASniperAIController::BeginPlay()
{
	Super::BeginPlay();
}

void ASniperAIController::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);

    APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
    if (!PlayerPawn)
    {
        return;
    }

    FVector PlayerLocation = PlayerPawn->GetActorLocation();
    FVector AILocation = GetPawn()->GetActorLocation();

    float Distance = FVector::Dist(PlayerLocation, AILocation);
    if (Distance <  FMath::Square(500.0f))
    {
        SetFocus(PlayerPawn);
    }
}
