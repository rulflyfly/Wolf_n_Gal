// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "WolfAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class WOLF_N_GAL_API UWolfAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:
    
    /** Is similar to BeginPlay() of an Actor */
    virtual void NativeInitializeAnimation() override;
    
    UFUNCTION(BlueprintCallable, Category = AnimationProperties)
    void UpdateAnimationProperties();
    
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Movement)
    float MovementSpeed;
    
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Movement)
    bool bIsInAir;
    
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Movement)
    class APawn* Pawn;
    
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Movement)
    class AWolf* Wolf;
};
