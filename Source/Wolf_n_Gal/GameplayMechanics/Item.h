// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Item.generated.h"

UCLASS()
class WOLF_N_GAL_API AItem : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AItem();
    
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Colission)
    class UBoxComponent* CollisionBox;
    
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Mesh)
    class UStaticMeshComponent* Mesh;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Particles)
    class UParticleSystemComponent* ParticleSystemComponent;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Particles)
    class UParticleSystem* ParticleSystem;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Mesh)
    bool bRotate;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Mesh)
    float RotationRate;

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
