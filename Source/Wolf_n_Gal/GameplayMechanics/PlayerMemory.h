// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "../Interface/DialogInterface.h"
#include "PlayerMemory.generated.h"

UCLASS()
class WOLF_N_GAL_API APlayerMemory : public AActor, public IDialogInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APlayerMemory();
    
    class AWolf* Player;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Sound)
    class USoundCue* GetSound;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Mesh)
    class UStaticMeshComponent* Mesh;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Mesh)
    class UBoxComponent* OverlapBox;
    
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Particles)
    class UParticleSystemComponent* IdleParticles;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Particles)
    class UParticleSystem* DestroyParticles;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Interaction)
    FString Info;
    
    void PlayDeathEffect();

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
