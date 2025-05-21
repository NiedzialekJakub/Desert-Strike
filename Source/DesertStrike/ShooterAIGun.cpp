// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterAIGun.h"
#include "Kismet/GameplayStatics.h"
#include "Projectile.h"
#include "PlayerCharacter.h"

AShooterAIGun::AShooterAIGun()
{
    Mesh = FindComponentByClass<UStaticMeshComponent>();

    ProjectileSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("Spawn Point"));
	ProjectileSpawnPoint->SetupAttachment(Mesh);
}

void AShooterAIGun::PullTheTrigger()
{
    FVector Shift(80, 0, -30);
	FRotator RotationParticle(-90, 0, 0);

	UGameplayStatics::SpawnEmitterAttached(
	MuzzleEffect,
	Mesh,
	TEXT("Fire_Socket"),
	Shift,
	RotationParticle,
	EAttachLocation::SnapToTarget,
	true // AutoDestroy
	);
	
	//prepare spawn projectile with rotation to player
	APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	FVector PlayerLocation = PlayerPawn->GetActorLocation();
	FVector SpawnPoint = ProjectileSpawnPoint->GetComponentLocation();
	FRotator LookAtRotation = (PlayerLocation - SpawnPoint).Rotation();

	AProjectile* SpawnedProjectile = GetWorld()->SpawnActor<AProjectile>(ProjectileClass, SpawnPoint, LookAtRotation);
	if(SpawnedProjectile){
		SpawnedProjectile->SetOwner(this);
	}

	UGameplayStatics::PlaySoundAtLocation(this, ShootSound, GetActorLocation(), 0.2f);
}