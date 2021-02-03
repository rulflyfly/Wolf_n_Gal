// Fill out your copyright notice in the Description page of Project Settings.


#include "DamagingSubstance.h"
#include "Components/BoxComponent.h"
#include "../Wolf/Wolf.h"

// Sets default values
ADamagingSubstance::ADamagingSubstance()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    DamageVolume = CreateDefaultSubobject<UBoxComponent>(TEXT("DamageVolume"));
    
    DamagePerSec = 10.f;

}

// Called when the game starts or when spawned
void ADamagingSubstance::BeginPlay()
{
	Super::BeginPlay();
    
    DamageVolume->OnComponentBeginOverlap.AddDynamic(this, &ADamagingSubstance::OnOverlapBegin);
    DamageVolume->OnComponentEndOverlap.AddDynamic(this, &ADamagingSubstance::OnOverlapEnd);
	
    DamageVolume->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
    DamageVolume->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);
    
}

// Called every frame
void ADamagingSubstance::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
    
    if (Wolf && bDamaging)
    {
        Wolf->DecrementHealth(DamagePerSec*DeltaTime);
    }

}

void ADamagingSubstance::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult)
{
    if (OtherActor)
    {
        Wolf = Cast<AWolf>(OtherActor);
        
        if (Wolf)
        {
            bDamaging = true;
        }
    }
}

void ADamagingSubstance::OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
    if (OtherActor)
    {
        AWolf* LeavingWolf = Cast<AWolf>(OtherActor);
        
        if (LeavingWolf)
        {
            Wolf = nullptr;
            bDamaging = false;
        }
    }
}
