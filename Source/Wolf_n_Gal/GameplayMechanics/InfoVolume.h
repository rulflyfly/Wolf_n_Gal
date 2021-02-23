// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "../Interface/DialogInterface.h"
#include "InfoVolume.generated.h"

UCLASS()
class WOLF_N_GAL_API AInfoVolume : public AActor, public IDialogInterface
{
	GENERATED_BODY()
    
protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;
	
public:	
	// Sets default values for this actor's properties
	AInfoVolume();
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = InfoType)
    bool bWater;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = InfoType)
    bool bShark;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Dialog);
    FString DialogLine;
    
    //class AMainPlayerController* InfoPlayerController;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Overlap);
    class UBoxComponent* OverlappingBox;
    
    UFUNCTION()
    virtual void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult);
    
    UFUNCTION()
    virtual void OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

};
