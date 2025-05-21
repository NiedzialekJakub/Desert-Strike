#include "ShooterAICharacter.h"
#include "GameFramework/Actor.h"
#include "GameFramework/Controller.h"
#include "ShooterAIGun.h"
#include "TimerManager.h"
#include "ControllerPlayer.h"
#include "Misc/OutputDeviceNull.h"
#include "Heart.h"
#include "Kismet/GameplayStatics.h"
#include "PlayerCharacter.h"

void AShooterAICharacter::BeginPlay()
{
	Super::BeginPlay();

	OnTakeAnyDamage.AddDynamic(this, &AShooterAICharacter::DamageTaken);

	Health = MaxHealth;

	Gun = GetWorld()->SpawnActor<AShooterAIGun>(GunClass);
	GetMesh()->HideBoneByName(TEXT("weapon_r"), EPhysBodyOp::PBO_None);
	Gun->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("WeaponSocket"));
	Gun->SetOwner(this);

}

void AShooterAICharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if(IsDead() && !GetWorldTimerManager().IsTimerActive(TimerHandle)){
		APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
		APlayerCharacter* Player = Cast<APlayerCharacter>(PlayerPawn);
		Player->KillCount += 1;
		GetWorldTimerManager().SetTimer(TimerHandle, this, &AShooterAICharacter::DestroyHandler, Rate, false);
		Gun->Destroy();
	}
}

AShooterAICharacter::AShooterAICharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	HeartSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("HeartSpawnPoint"));
	HeartSpawnPoint->SetupAttachment((USceneComponent*)GetCapsuleComponent());
}

bool AShooterAICharacter::IsDead() const
{
    return Health <= 0;
}

void AShooterAICharacter::DamageTaken(AActor *DamagedAktor, float Damage, const UDamageType *DamageType, AController *DamageInstigator, AActor *DamageCauser)
{
	if (Damage <= 0) return;

	Health -= Damage;
}

void AShooterAICharacter::Shoot()
{
	Gun->PullTheTrigger();
}

void AShooterAICharacter::DestroyHandler()
{
	FVector Location = GetActorLocation();
	FRotator Rotation = GetActorRotation();
	AHeart* Heart = GetWorld()->SpawnActor<AHeart>(HeartClass, Location, Rotation);
	
	Destroy();
}
