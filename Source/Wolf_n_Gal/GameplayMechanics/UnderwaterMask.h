// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item.h"
#include "UnderwaterMask.generated.h"

/**
 * 
 */
UCLASS()
class WOLF_N_GAL_API AUnderwaterMask : public AItem
{
	GENERATED_BODY()
	
public:
    
    void PutOn(class AWolf* Wolf);
    
    void PutOff(AWolf* Wolf);
    
    virtual void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult);
    
    virtual void OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
};
