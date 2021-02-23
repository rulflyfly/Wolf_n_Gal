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
    
    AMainPlayerController();
    
    /** Reference to the UMG asset in editor */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Widgets)
    TSubclassOf<class UUserWidget> HealthBarAsset;
    
    /** Variable to hold the widget after creating it */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Widgets)
    UUserWidget* HealthBar;
    
    /** Reference to the UMG asset in editor */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Widgets)
    TSubclassOf<class UUserWidget> DialogBoxAsset;
    
    /** Variable to hold the widget after creating it */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Widgets)
    UUserWidget* DialogBox;
    
    /** Reference to the UMG asset in editor */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Widgets)
    TSubclassOf<class UUserWidget> PauseMenuAsset;
    
    /** Variable to hold the widget after creating it */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Widgets)
    UUserWidget* PauseMenu;
    
    /** Reference to the UMG asset in editor */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Widgets)
    TSubclassOf<class UUserWidget> GameOverMenuAsset;
    
    /** Variable to hold the widget after creating it */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Widgets)
    UUserWidget* GameOverMenu;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Widgets)
    TSubclassOf<class UUserWidget> MemoryInputAsset;
    
    /** Variable to hold the widget after creating it */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Widgets)
    UUserWidget* MemoryInput;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Widgets)
    TSubclassOf<class UUserWidget> FinalChoiceAsset;
    
    /** Variable to hold the widget after creating it */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Widgets)
    UUserWidget* FinalChoice;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Widgets)
    TSubclassOf<class UUserWidget> FinishGameAsset;
    
    /** Variable to hold the widget after creating it */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Widgets)
    UUserWidget* FinishGame;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Widgets)
    bool bGamePaused;
    
    UFUNCTION(BlueprintNativeEvent)
    void ShowDialogBox(const FString& Text);
    
    void HideDialogBox();
    
    void ShowPauseMenu();
    
    UFUNCTION(BlueprintCallable)
    void HidePauseMenu();
    
    void TogglePause();
    
    void ShowGameOverMenu();
    
    void ShowMemoryInput();
    
    void HideMemoryInput();
    
    void ShowFinalChoice();
    
    void ShowFinishGame();
    
    void HideHealthBar();
    
    UFUNCTION(BlueprintCallable)
    void HideFinalChoice();
    
protected:
    virtual void BeginPlay() override;
        
};
