#pragma once

#include "CoreMinimal.h"
#include "MainCharakter.h"
#include "PlayerCharacter.generated.h"

class APlayerGun;
class AControllerPlayer;

UCLASS()
class DESERTSTRIKE_API APlayerCharacter : public AMainCharakter
{
	GENERATED_BODY()

public:
	APlayerCharacter();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintPure)
	bool IsDead() const;

	UFUNCTION(BlueprintPure)
	float GetHealth() const;

	UFUNCTION()
	void DamageTaken(AActor* DamagedAktor, float Damage, const UDamageType* DamageType, class AController* DamageInstigator, AActor* DamageCauser);

	UPROPERTY(BlueprintReadWrite)
	bool StartDelay;

	UPROPERTY(EditAnywhere)
	float MaxHealth = 1300.f;
	float Health = 0.f;

	int KillCount = 0;
	UFUNCTION(BlueprintPure)
	int GetKills() const;

	int Gold = 0;
	UFUNCTION(BlueprintPure)
	int GetGold() const;

private:
	void MoveForward(float Value);
	void MoveRight(float Value);
	void Shoot();
	void EnablePlayerInput();

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<APlayerGun> PlayerGunClass;

	UPROPERTY()
	APlayerGun* Gun;


	UPROPERTY()
	AControllerPlayer* PlayerController;

	FTimerHandle TimerHandle;

	//Restart, Loose Game
	void RestartLevel();
	bool bHasDied = false;
	float RestartTime = 3.0f;
	FTimerHandle RestartTimerHandle;
	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> RestartClass;
	UUserWidget* RestartWidget;
	//UPROPERTY(EditAnywhere)
	//TSubclassOf<UUserWidget> WinClass;
	//UUserWidget* WinWidget;


	UPROPERTY(EditAnywhere, Category = "Combat")
	class USoundBase* HitSound;

};