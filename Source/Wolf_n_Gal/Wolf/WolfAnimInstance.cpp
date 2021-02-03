// Fill out your copyright notice in the Description page of Project Settings.


#include "WolfAnimInstance.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Wolf.h"


void UWolfAnimInstance::NativeInitializeAnimation()
{
    if (Pawn == nullptr)
    {
        Pawn = TryGetPawnOwner();
        Wolf = Cast<AWolf>(Pawn);
    }
}

void UWolfAnimInstance::UpdateAnimationProperties()
{
    if (Pawn == nullptr)
    {
        Pawn = TryGetPawnOwner();
    }
    
    if (Pawn)
    {
        FVector Speed = Pawn->GetVelocity();
        FVector LateralSpeed = FVector(Speed.X, Speed.Y, 0.f);
        MovementSpeed = LateralSpeed.Size();
        
        bIsInAir = Pawn->GetMovementComponent()->IsFalling();
        
        if (!Wolf)
        {
            Wolf = Cast<AWolf>(Pawn);
        }
    }
}
