// Fill out your copyright notice in the Description page of Project Settings.


#include "UnderwaterMask.h"
#include "../Wolf/Wolf.h"
#include "Engine/SkeletalMeshSocket.h"

void AUnderwaterMask::PutOn(AWolf* Wolf)
{
    if (Wolf)
    {
        Mesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_Camera, ECollisionResponse::ECR_Ignore);
        Mesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Ignore);
        Mesh->SetSimulatePhysics(false);
        
        const USkeletalMeshSocket* MaskSocket = Wolf->GetMesh()->GetSocketByName("MaskSocket");
        
        if (MaskSocket)
        {
            MaskSocket->AttachActor(this, Wolf->GetMesh());
        }
    }
}

void AUnderwaterMask::PutOff(AWolf* Wolf)
{
    UE_LOG(LogTemp, Warning, TEXT("Mask Put Off"));
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
