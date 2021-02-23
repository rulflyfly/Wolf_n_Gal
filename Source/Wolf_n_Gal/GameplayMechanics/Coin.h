// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item.h"
#include "Coin.generated.h"


/**
 * 
 */
UCLASS()
class WOLF_N_GAL_API ACoin : public AItem
{
	GENERATED_BODY()
    
    ACoin();
	
public:
    
    class AWolf* Player;
    
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;
    
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Coins")
    int32 Worth;
    
    // Called every frame
    virtual void Tick(float DeltaTime) override;
    
    virtual void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult) override;
};
