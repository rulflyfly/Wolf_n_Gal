// Fill out your copyright notice in the Description page of Project Settings.


#include "SaveSpot.h"
#include "Components/BoxComponent.h"
#include "../Wolf/Wolf.h"

// Sets default values
ASaveSpot::ASaveSpot()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
    
    SaveVolume = CreateDefaultSubobject<UBoxComponent>(TEXT("SaveVolume"));
    SaveVolume->SetupAttachment(GetRootComponent());

    Message = TEXT("Lands without grass are deadly!");
    DamageIfLeft = 10.f;
}

// Called when the game starts or when spawned
void ASaveSpot::BeginPlay()
{
	Super::BeginPlay();
    
    SaveVolume->OnComponentBeginOverlap.AddDynamic(this, &ASaveSpot::OnOverlapBegin);
    SaveVolume->OnComponentEndOverlap.AddDynamic(this, &ASaveSpot::OnOverlapEnd);
	
}

// Called every frame
void ASaveSpot::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASaveSpot::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult)
{
    if (OtherActor)
    {
        AWolf* Wolf = Cast<AWolf>(OtherActor);
        
        if (Wolf)
        {
            Wolf->bBeingDamaged = false;
            Wolf->SetSaveSpotThatWasLeft(nullptr);
            StopInteracting(Wolf);
        }
    }
}

void ASaveSpot::OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
    if (OtherActor)
    {
        AWolf* Wolf = Cast<AWolf>(OtherActor);
        
        if (Wolf && !Wolf->bGoingToPortal)
        {
            Wolf->bBeingDamaged = true;
            Wolf->SetSaveSpotThatWasLeft(this);
            Interact(Wolf, Message);
        }
    }
}
