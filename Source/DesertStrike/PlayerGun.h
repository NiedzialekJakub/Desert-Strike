// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Gun.h"
#include "PlayerGun.generated.h"

/**
 * 
 */
UCLASS()
class DESERTSTRIKE_API APlayerGun : public AGun
{
	GENERATED_BODY()

private:

	UPROPERTY(EditAnywhere)
	UParticleSystem* MuzzleEffect;

	UStaticMeshComponent* MeshComp;

	UPROPERTY(EditDefaultsOnly, Category = "Combat")
	TSubclassOf<class AProjectile> ProjectileClass;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	USceneComponent* ProjectileSpawnPoint;

	UPROPERTY(EditAnywhere, Category = "Combat")
	class USoundBase* ShootSound;

public:
	void PullTheTrigger();
	APlayerGun();
	
};
