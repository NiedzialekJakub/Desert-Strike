#include "PlayerCharacter.h"
#include "PlayerGun.h"
#include "ControllerPlayer.h"
#include "TimerManager.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/UserWidget.h"

APlayerCharacter::APlayerCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
}

void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	Health = MaxHealth;
	OnTakeAnyDamage.AddDynamic(this, &APlayerCharacter::DamageTaken);

	Gun = GetWorld()->SpawnActor<APlayerGun>(PlayerGunClass);
	GetMesh()->HideBoneByName(TEXT("weapon_r"), EPhysBodyOp::PBO_None);
	Gun->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("Weapon_Socket"));
	Gun->SetOwner(this);

	StartDelay = false;

	PlayerController = Cast<AControllerPlayer>(GetController());
	if (PlayerController)
	{
		DisableInput(PlayerController);
		GetWorld()->GetTimerManager().SetTimer(
			TimerHandle,
			this,
			&APlayerCharacter::EnablePlayerInput,
			3.0f,
			false
		);
	}

	if (APlayerController* PC = Cast<APlayerController>(GetController())){
    	RestartWidget = CreateWidget<UUserWidget>(PC, RestartClass);
	}
}

void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &APlayerCharacter::MoveForward);
	PlayerInputComponent->BindAxis(TEXT("MoveRight"), this, &APlayerCharacter::MoveRight);
	PlayerInputComponent->BindAxis(TEXT("LookUp"), this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis(TEXT("LookRight"), this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAction(TEXT("Jump"), EInputEvent::IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction(TEXT("Shoot"), EInputEvent::IE_Pressed, this, &APlayerCharacter::Shoot);
}

void APlayerCharacter::MoveForward(float Value)
{
	AddMovementInput(GetActorForwardVector() * Value);
}

void APlayerCharacter::MoveRight(float Value)
{
	AddMovementInput(GetActorRightVector() * Value);
}

void APlayerCharacter::Shoot()
{
	Gun->PullTheTrigger();
}

bool APlayerCharacter::IsDead() const
{
    return Health <= 0;
}


float APlayerCharacter::GetHealth() const
{
	return Health / MaxHealth;
}

void APlayerCharacter::DamageTaken(AActor* DamagedAktor, float Damage, const UDamageType* DamageType, AController* DamageInstigator, AActor* DamageCauser)
{
    if (Damage <= 0 || bHasDied) return;

    Health -= Damage;
    UE_LOG(LogTemp, Warning, TEXT("Zycie: %f"), Health);
	UGameplayStatics::PlaySoundAtLocation(this, HitSound, GetActorLocation());

    if (IsDead())
    {
        bHasDied = true;
		RestartWidget->AddToViewport();
        GetWorldTimerManager().SetTimer(RestartTimerHandle, this, &APlayerCharacter::RestartLevel, RestartTime, false);
    }
}


void APlayerCharacter::EnablePlayerInput()
{
	if (PlayerController)
	{
		EnableInput(PlayerController);
		StartDelay = true;
	}
}

void APlayerCharacter::RestartLevel()
{
	UGameplayStatics::OpenLevel(this, FName(*GetWorld()->GetName()), false);
}

int APlayerCharacter::GetKills() const
{
	return KillCount;
}

int APlayerCharacter::GetGold() const
{
	return Gold;
}