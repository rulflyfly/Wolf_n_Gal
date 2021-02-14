// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FloatingPlatform.generated.h"

UCLASS()
class WOLF_N_GAL_API AFloatingPlatform : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFloatingPlatform();
    
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Platform)
    class UStaticMeshComponent* Mesh;
    
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Platform)
    class UBoxComponent* Box;
    
    UPROPERTY(EditAnywhere)
    FVector StartPoint;
    
    UPROPERTY(EditAnywhere, meta = (MakeEditWidget = "true"))
    FVector EndPoint;
    
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Platform)
    float InterpSpeed;
    
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Platform)
    float InterpTime;
    
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Platform)
    bool bInterping;
    
    float Distance;
    
    FTimerHandle InterpTimer;
    
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Platform)
    bool bPressed;
    
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Platform)
    int32 ColorNum;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
    
    void ToggleInterping();
    
    void SwapVectors(FVector& VectorOne, FVector& VectorTwo);
    
    UFUNCTION()
    void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult);
    
    UFUNCTION()
    void OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

};
