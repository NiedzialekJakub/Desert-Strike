// Fill out your copyright notice in the Description page of Project Settings.


#include "Gold.h"
#include "PlayerCharacter.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AGold::AGold()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Basic Mesh"));
	Mesh->SetupAttachment(Root);

	BasicMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	BasicMesh->SetupAttachment(Root);
}

// Called when the game starts or when spawned
void AGold::BeginPlay()
{
	Super::BeginPlay();
	
	BasicMesh->OnComponentBeginOverlap.AddDynamic(this, &AGold::OnOverlapBegin);
}

// Called every frame
void AGold::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

/*void AGold::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
    if (OtherActor->ActorHasTag("Player"))
    {
		APlayerCharacter* Player = Cast<APlayerCharacter>(OtherActor);
		if(Player){
			//UGameplayStatics::PlaySoundAtLocation(this, TakeSound, GetActorLocation());
			Player->Gold += 1;
        	Destroy();
		}
    }
}*/

void AGold::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
                           UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
                           bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && OtherActor->ActorHasTag("Player"))
	{
		APlayerCharacter* Player = Cast<APlayerCharacter>(OtherActor);
		if (Player)
		{
			UGameplayStatics::PlaySoundAtLocation(this, TakeSound, GetActorLocation());
			Player->Gold += 1;
			Destroy();
		}
	}
}
