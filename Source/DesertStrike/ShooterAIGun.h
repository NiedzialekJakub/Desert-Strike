// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Gun.h"
#include "ShooterAIGun.generated.h"

/**
 * 
 */
UCLASS()
class DESERTSTRIKE_API AShooterAIGun : public AGun
{
	GENERATED_BODY()
	
private:
	UPROPERTY(EditAnywhere)
	UParticleSystem* MuzzleEffect;

	UStaticMeshComponent* Mesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	USceneComponent* ProjectileSpawnPoint;

	UPROPERTY(EditDefaultsOnly, Category = "Combat")
	TSubclassOf<class AProjectile> ProjectileClass;

	UPROPERTY(EditAnywhere, Category = "Combat")
	class USoundBase* ShootSound;

public:
	AShooterAIGun();
	void PullTheTrigger();
};
