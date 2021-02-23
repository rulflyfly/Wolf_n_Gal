// Fill out your copyright notice in the Description page of Project Settings.


#include "UnderwaterMask.h"
#include "../Wolf/Wolf.h"
#include "Engine/SkeletalMeshSocket.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystem.h"

void AUnderwaterMask::BeginPlay()
{
    Super::BeginPlay();
    Mesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_Camera, ECollisionResponse::ECR_Ignore);
    
    APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
    
    AWolf* WolfToSet = Cast<AWolf>(PlayerPawn);
    
    if (WolfToSet)
    {
        WolfUnderMask = WolfToSet;
    }
}

void AUnderwaterMask::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    if (WolfUnderMask->bGoingToPortal)
    {
        if (DestroyParticles) UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), DestroyParticles, GetActorLocation(), FRotator(0.f), true);
        Destroy();
    }
}

void AUnderwaterMask::PutOn(AWolf* Wolf)
{
    if (Wolf)
    {
        Mesh->SetSimulatePhysics(false);
        Mesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_Camera, ECollisionResponse::ECR_Ignore);
        Mesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Ignore);
 
        const USkeletalMeshSocket* MaskSocket = Wolf->GetMesh()->GetSocketByName("MaskSocket");
        
        if (MaskSocket)
        {
            MaskSocket->AttachActor(this, Wolf->GetMesh());
            Wolf->bMaskOn = true;
        }
    }
}

void AUnderwaterMask::PutOff(AWolf* Wolf)
{
    if (Wolf)
    {
        Mesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);
        FDetachmentTransformRules DetachmentRules(EDetachmentRule::KeepWorld,
                                                  false);
        DetachFromActor(DetachmentRules);
        Wolf->SetMaskToPutOn(this);
        Wolf->bMaskOn = false;
    }
}

void AUnderwaterMask::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult)
{
    if (OtherActor)
    {
        AWolf* Wolf = Cast<AWolf>(OtherActor);
        
        if (Wolf)
        {
            Wolf->SetMaskToPutOn(this);
        }
    }
}

void AUnderwaterMask::OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
    if (OtherActor)
    {
        AWolf* Wolf = Cast<AWolf>(OtherActor);
        
        if (Wolf)
        {
            Wolf->SetMaskToPutOn(nullptr);
        }
    }
}
