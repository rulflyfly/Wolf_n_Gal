// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "../Interface/DialogInterface.h"
#include "DamagingSubstance.generated.h"

UCLASS()
class WOLF_N_GAL_API ADamagingSubstance : public AActor, public IDialogInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
    ADamagingSubstance();
    
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Collision)
    class UBoxComponent* DamageVolume;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Dialog)
    FString Message;
    
    bool bDamaging;
    
    class AWolf* Wolf;
    
    float DamagePerSec;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
    
    UFUNCTION()
    void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult);
    
    UFUNCTION()
    void OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

};
