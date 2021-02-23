// Fill out your copyright notice in the Description page of Project Settings.


#include "InfoVolume.h"
#include "GameFramework/PlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "../Wolf/Wolf.h"
#include "../PlayerController/MainPlayerController.h"
#include "Components/BoxComponent.h"
#include "SpawnVolume.h"

// Sets default values
AInfoVolume::AInfoVolume()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
    
    OverlappingBox = CreateDefaultSubobject<UBoxComponent>(TEXT("OverlappingBox"));
    OverlappingBox->SetupAttachment(GetRootComponent());
    
    DialogLine = "I am an info volume";
    
    bWater = false;
    
    bShark = false;
}

void AInfoVolume::BeginPlay()
{
    Super::BeginPlay();
    
    OverlappingBox->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
    OverlappingBox->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);
    
    OverlappingBox->OnComponentBeginOverlap.AddDynamic(this, &AInfoVolume::OnOverlapBegin);
    OverlappingBox->OnComponentEndOverlap.AddDynamic(this, &AInfoVolume::OnOverlapEnd);
    
}

void AInfoVolume::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult)
{
    if (OtherActor)
    {
        AWolf* Wolf = Cast<AWolf>(OtherActor);
        
        if (Wolf)
        {
            if (bWater && Wolf->bMaskOn)
            {
                Destroy();
                return;
            }
            
            Wolf->SetOverlappingInfoVolume(this);
            Interact(Wolf, DialogLine);

        }
    }
}

void AInfoVolume::OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
    if (OtherActor && InfoPlayerController)
    {
        AWolf* Wolf = Cast<AWolf>(OtherActor);
        
        if (Wolf && bShark)
        {
            Wolf->SpawnVolume->SpawnCoinsAfterFirstEncounter();
            Destroy();
        }
            
        if (Wolf && InfoPlayerController)
        {
            Wolf->SetOverlappingInfoVolume(nullptr);
            StopInteracting(Wolf);
        }
    }
}
