// Fill out your copyright notice in the Description page of Project Settings.


#include "MainPlayerController.h"
#include "Blueprint/UserWidget.h"



void AMainPlayerController::BeginPlay()
{
    Super::BeginPlay();
    
    if (HealthBarAsset)
    {
        HealthBar = CreateWidget<UUserWidget>(this, HealthBarAsset);
        HealthBar->AddToViewport();
        HealthBar->SetVisibility(ESlateVisibility::Visible);
    }
    
    if (DialogBoxAsset)
    {
        DialogBox = CreateWidget<UUserWidget>(this, DialogBoxAsset);
        DialogBox->AddToViewport();
        DialogBox->SetVisibility(ESlateVisibility::Hidden);
    }
    
}

void AMainPlayerController::ShowDialogBox_Implementation(const FString& Text)
{
    if (DialogBox)
    {
        DialogBox->SetVisibility(ESlateVisibility::Visible);
    }
}

void AMainPlayerController::HideDialogBox()
{
    if (DialogBox)
    {
        DialogBox->SetVisibility(ESlateVisibility::Hidden);
    }
}
