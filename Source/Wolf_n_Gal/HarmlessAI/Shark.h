// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "../Interface/DialogInterface.h"
#include "Shark.generated.h"

UENUM(BlueprintType)
enum class EStoryStatus : uint8
{
    ESS_Untold              UMETA(DisplayName = "Untold"),
    ESS_Intro               UMETA(DisplayName = "Intro"),
    ESS_WaitingForMemories  UMETA(DisplayName = "WaitingForMemories"),
    ESS_GotFirstMemory      UMETA(DisplayName = "GotFirstMemory"),
    ESS_FinalWords          UMETA(DisplayName = "FinalWords"),
    
    ESS_MAX                 UMETA(DisplayName = "DefaultMax")
};

UCLASS()
class WOLF_N_GAL_API AShark : public ACharacter, public IDialogInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AShark();
    
    bool bFirstInteraction;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Interaction)
    bool bHasMoreToSay;
    
    UPROPERTY(EditAnywhere, meta = (MakeEditWidget = "true"))
    FVector GoldParticlesSpot;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Interaction)
    class UBoxComponent* InteractionBox;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Interaction)
    class UParticleSystem* GetGoldParticles;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Interaction)
    class UParticleSystem* DestroyParticles;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Interaction)
    int32 Price;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Dialog)
    class UDataTable* DialogLinesTable;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Dialog);
    int32 Id;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Dialog);
    bool Interactive;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Dialog);
    TArray<FString> DialogLinesArray;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Dialog);
    int32 DialogLineNum;
    
    bool bPaid;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Dialog);
    EStoryStatus StoryStatus;
    
    int32 CurrentConversation;
    
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
    
    void MakeDialogLineArray();
    
    UFUNCTION()
   void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult);
    
    UFUNCTION()
    void OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

    FORCEINLINE void SetStoryStatus(EStoryStatus Status) { StoryStatus = Status; }
};
