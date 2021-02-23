// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Wolf.generated.h"

UCLASS()
class WOLF_N_GAL_API AWolf : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AWolf();
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Sound)
    bool bInWater;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Sound)
    class USoundCue* InWaterSound;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Sound)
    class USoundCue* OutWaterSound;
    
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Controller)
    class AMainPlayerController* MainPlayerController;
    
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
    class UCameraComponent* Camera;
    
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
    class USpringArmComponent* SpringArm;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Stats")
    float MaxHealth;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Stats")
    float Health;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Stats")
    int32 Coins;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interaction")
    class ACharacter* AIToInteract;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UnderWater")
    class AUnderwaterMask* MaskToPutOn;
    
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Anims)
    class UAnimMontage* DeathMontage;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Memories")
    TArray<FString> Memories;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Memories")
    bool bRecordingMemory;
    
    class AInfoVolume* OverlappingInfoVolume;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UnderWater")
    bool bMaskOn;
    
    bool bIsDead;
    
    bool bBeingDamaged;
    
    class ASaveSpot* SaveSpotThatWasLeft;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Recording Memories")
    class APlayerMemory* MemoryRecorder;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Spawning)
    class ASpawnVolume* SpawnVolume;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Recording Memories")
    int32 MemoryRecordersAmountToSpawn;
    
    TSubclassOf<ASpawnVolume> SpawnVolumeClass;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Merories)
    int32 MemoryCount;
    
    bool bRepeat;
    
    bool bMadeStoryIntroArray;
    
    bool bMadeToMemoryResponseArray;
    
    bool bFinalChoice;
    
    bool bPotionSpawned;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = EndGame)
    bool bGoingToPortal;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

    /** Movement */
    void Turn(float Value);
    void LookUp(float Value);
    void MoveForward(float Value);
    void MoveRight(float Value);
	
    /** Damage */
    
    void DecrementHealth(float Amount);
    void IncrementHealth(float Amount);
    
    /** Coins  */
    
    void AddCoins(int32 Amount);
    
    void Interact();
    
    void WearMask();
    
    void HideInfo();
    
    void TogglePause();
    
    bool GamePaused();
    
    void Die();
    
    void RecordMemory();
    
    void EndGame();
    
    UFUNCTION(BlueprintCallable)
    void SaveMemory(FString Memory);
    
    UFUNCTION(BlueprintCallable)
    void DeathEnd();
    
    UFUNCTION(BlueprintCallable)
    void FinishStory();
    
    UFUNCTION(BlueprintCallable)
    void ContinuePlaying();
    
    virtual void Jump() override;
    
    FORCEINLINE void SetAIToInteract(ACharacter* AI) { AIToInteract = AI; }
    FORCEINLINE void SetMaskToPutOn(AUnderwaterMask* Mask) { MaskToPutOn = Mask; }
    FORCEINLINE void SetOverlappingInfoVolume(AInfoVolume* InfoVolume) { OverlappingInfoVolume = InfoVolume; }
    FORCEINLINE void SetSaveSpotThatWasLeft(ASaveSpot* Spot) { SaveSpotThatWasLeft = Spot; }
    FORCEINLINE void SetMemoryRecorder(APlayerMemory* Recorder) { MemoryRecorder = Recorder; }
};
