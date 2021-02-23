// Fill out your copyright notice in the Description page of Project Settings.


#include "MainPlayerController.h"
#include "Blueprint/UserWidget.h"
#include "../Wolf/Wolf.h"

AMainPlayerController::AMainPlayerController()
{
    bGamePaused = false;
}

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
    
    if (PauseMenuAsset)
    {
        PauseMenu = CreateWidget<UUserWidget>(this, PauseMenuAsset);
        PauseMenu->AddToViewport();
        PauseMenu->SetVisibility(ESlateVisibility::Hidden);
    }
    
    if (GameOverMenuAsset)
    {
        GameOverMenu = CreateWidget<UUserWidget>(this, GameOverMenuAsset);
        GameOverMenu->AddToViewport();
        GameOverMenu->SetVisibility(ESlateVisibility::Hidden);
    }
    
    if (MemoryInputAsset)
    {
        MemoryInput = CreateWidget<UUserWidget>(this, MemoryInputAsset);
        MemoryInput->AddToViewport();
        MemoryInput->SetVisibility(ESlateVisibility::Hidden);
    }
    
    if (FinalChoiceAsset)
    {
        FinalChoice = CreateWidget<UUserWidget>(this, FinalChoiceAsset);
        FinalChoice->AddToViewport();
        FinalChoice->SetVisibility(ESlateVisibility::Hidden);
    }
    
    if (FinishGameAsset)
    {
        FinishGame = CreateWidget<UUserWidget>(this, FinishGameAsset);
        FinishGame->AddToViewport();
        FinishGame->SetVisibility(ESlateVisibility::Hidden);
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

void AMainPlayerController::ShowPauseMenu()
{
    if (PauseMenu)
    {
        bGamePaused = true;
        FInputModeGameAndUI InputModeGameAndUI;
        SetInputMode(InputModeGameAndUI);
        bShowMouseCursor = true;
        PauseMenu->SetVisibility(ESlateVisibility::Visible);
    }
}

void AMainPlayerController::HidePauseMenu()
{
    if (PauseMenu)
    {
        bGamePaused = false;
        FInputModeGameOnly InputModeGameOnly;
        SetInputMode(InputModeGameOnly);
        bShowMouseCursor = false;
        PauseMenu->SetVisibility(ESlateVisibility::Hidden);
    }
}

void AMainPlayerController::TogglePause()
{
    if (!bGamePaused)
    {
        ShowPauseMenu();
    }
    else
    {
        HidePauseMenu();
    }
}

void AMainPlayerController::ShowGameOverMenu()
{
    if (GameOverMenu)
    {
        GameOverMenu->SetVisibility(ESlateVisibility::Visible);
        FInputModeGameAndUI InputModeGameAndUI;
        SetInputMode(InputModeGameAndUI);
        bShowMouseCursor = true;
    }
}


void AMainPlayerController::ShowMemoryInput()
{
    if (MemoryInput)
    {
        MemoryInput->SetVisibility(ESlateVisibility::Visible);
        
        FInputModeUIOnly InputModeUIOnly;
        SetInputMode(InputModeUIOnly);
        bShowMouseCursor = true;
        
        AWolf* Wolf = Cast<AWolf>(GetCharacter());
        if (Wolf) Wolf->bFinalChoice = true;
    }
}

void AMainPlayerController::HideMemoryInput()
{
    if (MemoryInput)
    {
        MemoryInput->SetVisibility(ESlateVisibility::Hidden);
        
        FInputModeGameOnly InputModeGameOnly;
        SetInputMode(InputModeGameOnly);
        bShowMouseCursor = false;
        
        AWolf* Wolf = Cast<AWolf>(GetCharacter());
        if (Wolf) Wolf->bFinalChoice = false;
    }
}

void AMainPlayerController::ShowFinalChoice()
{
    if (FinalChoice)
    {
        FinalChoice->SetVisibility(ESlateVisibility::Visible);
        
        FInputModeUIOnly InputModeUIOnly;
        SetInputMode(InputModeUIOnly);
        bShowMouseCursor = true;
        
        AWolf* Wolf = Cast<AWolf>(GetCharacter());
        if (Wolf) Wolf->bFinalChoice = true;
    }
}

void AMainPlayerController::HideFinalChoice()
{
    if (FinalChoice)
    {
        FinalChoice->SetVisibility(ESlateVisibility::Hidden);
        
        FInputModeGameOnly InputModeGameOnly;
        SetInputMode(InputModeGameOnly);
        bShowMouseCursor = false;
        
        AWolf* Wolf = Cast<AWolf>(GetCharacter());
        if (Wolf) Wolf->bFinalChoice = false;
    }
}


void AMainPlayerController::ShowFinishGame()
{
    if (FinishGame)
    {
        FinishGame->SetVisibility(ESlateVisibility::Visible);
        
        FInputModeUIOnly InputModeUIOnly;
        SetInputMode(InputModeUIOnly);
        bShowMouseCursor = true;

    }
}


void AMainPlayerController::HideHealthBar()
{
    if (HealthBar) HealthBar->SetVisibility(ESlateVisibility::Hidden);
}
