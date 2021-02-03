// Fill out your copyright notice in the Description page of Project Settings.


#include "MainPlayerController.h"
#include "Blueprint/UserWidget.h"



void AMainPlayerController::BeginPlay()
{
    Super::BeginPlay();
    
    if (HealthBarAsset)
    {
        HealthBar = CreateWidget<UUserWidget>(this, HealthBarAsset);
    }
    
    HealthBar->AddToViewport();
    HealthBar->SetVisibility(ESlateVisibility::Visible);
}
