#pragma once

#include "CoreMinimal.h"
#include "MainCharakter.h"
#include "ShooterAICharacter.generated.h"

class AShooterAIGun;

UCLASS()
class DESERTSTRIKE_API AShooterAICharacter : public AMainCharakter
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

	FTimerHandle TimerHandle;
	float Rate = 0.6f;
	void DestroyHandler();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	USceneComponent* HeartSpawnPoint;

	UPROPERTY(EditDefaultsOnly, Category = "Combat")
	TSubclassOf<class AHeart> HeartClass;

protected:
	virtual void BeginPlay() override;

public:
	AShooterAICharacter();

	UFUNCTION(BlueprintPure)
	bool IsDead() const;

	UFUNCTION()
	void DamageTaken(AActor* DamagedAktor, float Damage, const UDamageType* DamageType, class AController* DamageInstigator, AActor* DamageCauser);

	void Shoot();

	virtual void Tick(float DeltaTime) override;
};
