// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerGun.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystem.h"
#include "Projectile.h"
#include "Engine/DamageEvents.h"


APlayerGun::APlayerGun()
{
	MeshComp = FindComponentByClass<UStaticMeshComponent>();

	ProjectileSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("Spawn Point"));
	ProjectileSpawnPoint->SetupAttachment(MeshComp);
}

void APlayerGun::PullTheTrigger()
{
	FVector Shift(80, 0, -30);
	FRotator RotationParticle(-90, 0, 0);

	UGameplayStatics::SpawnEmitterAttached(
	MuzzleEffect,
	MeshComp,
	TEXT("Fire_Socket"),
	Shift,
	RotationParticle,
	EAttachLocation::SnapToTarget,
	true // AutoDestroy
	);

	FVector SpawnPoint = ProjectileSpawnPoint->GetComponentLocation();
	FRotator Rotation = ProjectileSpawnPoint->GetComponentRotation();
	AProjectile* SpawnedProjectile = GetWorld()->SpawnActor<AProjectile>(ProjectileClass, SpawnPoint, Rotation);
	if(SpawnedProjectile){
		SpawnedProjectile->SetOwner(this);
	}

	UGameplayStatics::PlaySoundAtLocation(this, ShootSound, GetActorLocation());
}
