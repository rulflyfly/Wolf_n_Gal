// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SpawnVolume.generated.h"

UCLASS()
class WOLF_N_GAL_API ASpawnVolume : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASpawnVolume();
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Portal)
    FVector PortalLocation;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Extent)
    class UBoxComponent* ExtentBox;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Extent)
    UBoxComponent* SecondQuarterBox;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Extent)
    UBoxComponent* ThirdQuarterBox;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Extent)
    UBoxComponent* FourthQuarterBox;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Extent)
    UBoxComponent* FirstQuarterBox;
    
    TArray<UBoxComponent*> BoxArray;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Extent)
    TSubclassOf<class ACoin> Coin;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Extent)
    TSubclassOf<class APlayerMemory> MemoryRecorder;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Extent)
    TSubclassOf<class APotion> Potion;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Extent)
    TSubclassOf<class APortal> Portal;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
    
    FVector GetSpawnPoint(UBoxComponent* TargetBox);
    
    void SpawnCoinsAfterFirstEncounter();
    
    void SpawnMemoryRecorder();
    
    void SpawnPotion();

    void SpawnPortal();
};
