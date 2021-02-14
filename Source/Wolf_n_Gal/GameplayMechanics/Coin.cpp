// Fill out your copyright notice in the Description page of Project Settings.


#include "Coin.h"
#include "../Wolf/Wolf.h"
#include "Particles/ParticleSystem.h"
#include "Kismet/GameplayStatics.h"

ACoin::ACoin()
{
    Worth = 1;
}

void ACoin::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult)
{
    if (OtherActor)
    {
        AWolf* Wolf = Cast<AWolf>(OtherActor);
        
        if (Wolf)
        {
            Wolf->AddCoins(Worth);
            
            if (ParticleSystem)
            {
                UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ParticleSystem, GetActorLocation(), FRotator(0.f), true);
            }
            
            Destroy();
        }
        
    }
}
