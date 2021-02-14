// Fill out your copyright notice in the Description page of Project Settings.


#include "DialogInterface.h"
#include "../Wolf/Wolf.h"
#include "../PlayerController/MainPlayerController.h"
#include "Engine/World.h"
#include "UObject/ConstructorHelpers.h"


void IDialogInterface::Interact(AWolf* Wolf, const FString& Text)
{
    InfoPlayerController = Cast<AMainPlayerController>(Wolf->GetController());
    
    if (InfoPlayerController)
    {
        InfoPlayerController->ShowDialogBox(Text);
    }
}


void IDialogInterface::StopInteracting(AWolf* Wolf)
{
    InfoPlayerController = Cast<AMainPlayerController>(Wolf->GetController());
    
    if (InfoPlayerController)
    {
        InfoPlayerController->HideDialogBox();
    }
}
