// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MainCharakter.h"
#include "SniperAICharakter.generated.h"

class AShooterAIGun;

UCLASS()
class DESERTSTRIKE_API ASniperAICharakter : public AMainCharakter
{
	GENERATED_BODY()

private:

	UPROPERTY(EditAnywhere)
	float MaxHealth = 100.f;

	float Health = 0.f;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AShooterAIGun> GunClass;

	UPROPERTY()
	AShooterAIGun* Gun;

	FTimerHandle TimerHandleDeath;
	float DeathRate = 0.6f;
	void DestroyHandler();


protected:
	virtual void BeginPlay() override;

public:
	UFUNCTION(BlueprintPure)
	bool IsDead() const;

	UFUNCTION()
	void DamageTaken(AActor* DamagedAktor, float Damage, const UDamageType* DamageType, class AController* DamageInstigator, AActor* DamageCauser);

	void Shoot();

	FTimerHandle TimerHandle;
	float Rate = 2.f;
	void CheckIfCanShoot();

	virtual void Tick(float DeltaTime) override;
};
