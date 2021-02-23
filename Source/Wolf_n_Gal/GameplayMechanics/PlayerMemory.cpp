// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerMemory.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Particles/ParticleSystem.h"
#include "../Wolf/Wolf.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundCue.h"

// Sets default values
APlayerMemory::APlayerMemory()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    OverlapBox = CreateDefaultSubobject<UBoxComponent>(TEXT("OverlapBox"));
    RootComponent = OverlapBox;
    
    Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
    Mesh->SetupAttachment(GetRootComponent());
    
    IdleParticles = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("ParticleSystemComponent"));
    IdleParticles->SetupAttachment(GetRootComponent());
    
    Info = TEXT("Press M to see what's there");
}

// Called when the game starts or when spawned
void APlayerMemory::BeginPlay()
{
	Super::BeginPlay();
	
    OverlapBox->OnComponentBeginOverlap.AddDynamic(this, &APlayerMemory::OnOverlapBegin);
    OverlapBox->OnComponentEndOverlap.AddDynamic(this, &APlayerMemory::OnOverlapEnd);
    
    APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
    
    AWolf* WolfToSet = Cast<AWolf>(PlayerPawn);
    
    if (WolfToSet)
    {
        Player = WolfToSet;
    }
}

// Called every frame
void APlayerMemory::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
    
    if (Player->bGoingToPortal) Destroy();
}

void APlayerMemory::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult)
{
    if (OtherActor)
    {
        AWolf* Wolf = Cast<AWolf>(OtherActor);
        
        if (Wolf)
        {
            Wolf->SetMemoryRecorder(this);
            Interact(Wolf, Info);
        }
    }
}

void APlayerMemory::OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
    if (OtherActor)
    {
        AWolf* Wolf = Cast<AWolf>(OtherActor);
        
        if (Wolf)
        {
            Wolf->SetMemoryRecorder(nullptr);
            StopInteracting(Wolf);
        }
    }
}

void APlayerMemory::PlayDeathEffect()
{
    if (DestroyParticles)
    {
        UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), DestroyParticles, GetActorLocation(), FRotator(0.f), true);
    }
    
    if (GetSound)
    {
        UGameplayStatics::PlaySound2D(this, GetSound);
    }
}
