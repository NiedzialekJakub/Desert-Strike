// Fill out your copyright notice in the Description page of Project Settings.


#include "Heart.h"
#include "Components/SkeletalMeshComponent.h"
#include "PlayerCharacter.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AHeart::AHeart()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Skeletal Mesh"));
	RootComponent = SkeletalMesh;

}

// Called when the game starts or when spawned
void AHeart::BeginPlay()
{
	Super::BeginPlay();
	
	StartLocation = GetActorLocation();

	SkeletalMesh->OnComponentHit.AddDynamic(this, &AHeart::OnHit);
}

// Called every frame
void AHeart::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AddActorLocalRotation(FRotator(0, 1, 0));

	FVector CurrentLocation = GetActorLocation();
	float Distance = FVector::Dist(CurrentLocation, StartLocation);

	if (Distance >= MoveRange)
	{
		bGoingUp = !bGoingUp;
	}

	float Direction = bGoingUp ? 1.0f : -1.0f;
	FVector Offset = FVector(0, 0, Direction * MoveSpeed * DeltaTime);

	SetActorLocation(CurrentLocation + Offset);
}

void AHeart::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
    if (OtherActor->ActorHasTag("Player"))
    {
		APlayerCharacter* Player = Cast<APlayerCharacter>(OtherActor);
		if(Player){
			UGameplayStatics::PlaySoundAtLocation(this, TakeSound, GetActorLocation());
			Player->Health += 50;
        	Destroy();
		}
    }
}