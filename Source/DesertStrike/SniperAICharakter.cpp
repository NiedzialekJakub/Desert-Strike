// Fill out your copyright notice in the Description page of Project Settings.


#include "SniperAICharakter.h"
#include "ShooterAIGun.h"
#include "TimerManager.h"
#include "Kismet/GameplayStatics.h"
#include "PlayerCharacter.h"

void ASniperAICharakter::BeginPlay()
{
	Super::BeginPlay();

	Health = MaxHealth;

    OnTakeAnyDamage.AddDynamic(this, &ASniperAICharakter::DamageTaken);

		Gun = GetWorld()->SpawnActor<AShooterAIGun>(GunClass);
		GetMesh()->HideBoneByName(TEXT("weapon_r"), EPhysBodyOp::PBO_None);
		Gun->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("Weapon"));
		Gun->SetOwner(this);

		GetWorldTimerManager().SetTimer(TimerHandle, this, &ASniperAICharakter::CheckIfCanShoot, Rate, true);
}

void ASniperAICharakter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if(IsDead() && !GetWorldTimerManager().IsTimerActive(TimerHandleDeath)){
		APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
		APlayerCharacter* Player = Cast<APlayerCharacter>(PlayerPawn);
		Player->KillCount += 1;
		GetWorldTimerManager().SetTimer(TimerHandleDeath, this, &ASniperAICharakter::DestroyHandler, DeathRate, false);
		Gun->Destroy();
	}
}

bool ASniperAICharakter::IsDead() const
{
    return Health <= 0;
}

void ASniperAICharakter::DamageTaken(AActor *DamagedAktor, float Damage, const UDamageType *DamageType, AController *DamageInstigator, AActor *DamageCauser)
{
	if (Damage <= 0) return;

	Health -= Damage;
}

void ASniperAICharakter::Shoot()
{
	Gun->PullTheTrigger();
}

void ASniperAICharakter::CheckIfCanShoot()
{
	APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
    if (!PlayerPawn)
    {
        return;
    }

    FVector PlayerLocation = PlayerPawn->GetActorLocation();
	FVector AILocation = GetActorLocation();

    float Distance = FVector::Dist(PlayerLocation, AILocation);
    if (Distance <  FMath::Square(100.0f))
    {
		Shoot();
	}
}

void ASniperAICharakter::DestroyHandler()
{
	Destroy();
}