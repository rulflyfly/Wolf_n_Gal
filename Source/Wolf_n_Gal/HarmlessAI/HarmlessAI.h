// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "../Interface/DialogInterface.h"
#include "HarmlessAI.generated.h"

UCLASS()
class WOLF_N_GAL_API AHarmlessAI : public ACharacter, public IDialogInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AHarmlessAI();
    
    class AWolf* Player;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Interaction)
    bool bHasMoreToSay;
    
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Interaction)
    class UBoxComponent* InteractionBox;
    
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = AI)
    class AAIController* AIController;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AI)
    bool Moving;
    
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

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
    
    UFUNCTION(BlueprintCallable)
    void Move(FVector Location);

    UFUNCTION()
    virtual void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult);
    
    UFUNCTION()
    virtual void OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
};
