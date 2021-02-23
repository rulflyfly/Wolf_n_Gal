// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "../Interface/DialogInterface.h"
#include "SaveSpot.generated.h"

UCLASS()
class WOLF_N_GAL_API ASaveSpot : public AActor, public IDialogInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASaveSpot();
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Message)
    FString Message;
    
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Collision)
    class UBoxComponent* SaveVolume;
    
    float DamageIfLeft;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

    UFUNCTION()
    virtual void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult);
    
    UFUNCTION()
    virtual void OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

};

