// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "DialogInterface.generated.h"

/**
 * 
 */

USTRUCT(BlueprintType)
struct FDialogLinesTable : public FTableRowBase
{
    GENERATED_BODY()
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Dialog)
    int32 NPC_ID;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Dialog)
    int32 Conversation_ID;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Dialog)
    int32 Line_ID;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Dialog)
    FString Dialog;
};

UINTERFACE(MinimalAPI, Blueprintable)
class WOLF_N_GAL_API UDialogInterface : public UInterface
{
    GENERATED_BODY()
};

class IDialogInterface
{
    GENERATED_BODY()
    
public:
    
    class AMainPlayerController* InfoPlayerController;

    virtual void Interact(class AWolf* Wolf, const FString& Text);
    virtual void StopInteracting(AWolf* Wolf);
};
