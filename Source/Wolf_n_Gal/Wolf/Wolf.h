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
    
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
    class UCameraComponent* Camera;
    
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
    class USpringArmComponent* SpringArm;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Stats")
    float MaxHealth;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Stats")
    float Health;

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
};
