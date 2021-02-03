// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MainPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class WOLF_N_GAL_API AMainPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
    /** Reference to the UMG asset in editor */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Widgets)
    TSubclassOf<class UUserWidget> HealthBarAsset;
    
    /** Variable to hold the widget after creating it */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Widgets)
    UUserWidget* HealthBar;
    
protected:
    virtual void BeginPlay() override;
};
