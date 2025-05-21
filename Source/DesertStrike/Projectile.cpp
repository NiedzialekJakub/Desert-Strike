// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/DamageType.h"
#include "GameFramework/Controller.h"

// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(Root);

	CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));

    // Collision settings
    CollisionComponent->InitSphereRadius(5.0f);
    CollisionComponent->SetCollisionProfileName(TEXT("BlockAll"));
    CollisionComponent->SetNotifyRigidBodyCollision(true); 
    CollisionComponent->BodyInstance.bUseCCD = true; 

    RootComponent = CollisionComponent;

	CollisionComponent->SetSimulatePhysics(true);
	CollisionComponent->SetNotifyRigidBodyCollision(true);


	//Projectile Movement 
	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Movement Component"));
	ProjectileMovementComponent->MaxSpeed = 30000.f;
	ProjectileMovementComponent->InitialSpeed = 30000.f;
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();

	SetLifeSpan(3.0f);

	CollisionComponent->OnComponentHit.AddDynamic(this, &AProjectile::OnHit);

}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	UGameplayStatics::SpawnEmitterAtLocation(
		GetWorld(),
		ProjectileParticle,
		GetActorLocation(),
		GetActorRotation(),
		FVector(0.2f)
	);
	

}

void AProjectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpuls, const FHitResult& Hit)
{
	auto MyOwner = GetOwner();
	if(MyOwner == nullptr) return;
	auto MyOwnerInstygator = MyOwner->GetInstigatorController();
	auto DamageTypeClass = UDamageType::StaticClass();
	if (OtherActor && OtherActor != this && OtherComp)
	{
		UGameplayStatics::ApplyDamage(
			OtherActor,
			Damage,                             
			MyOwnerInstygator, 
			this,                             
			DamageTypeClass        
		);

		Destroy();
	}
}
