// Fill out your copyright notice in the Description page of Project Settings.


#include "Wolf.h"
#include "Components/SkeletalMeshComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "../HarmlessAI/HarmlessAI.h"
#include "../GameplayMechanics/UnderwaterMask.h"
#include "../GameplayMechanics/InfoVolume.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AWolf::AWolf()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
    
    SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
    SpringArm->SetupAttachment(GetRootComponent());
    SpringArm->TargetArmLength = 600.f;
    SpringArm->bUsePawnControlRotation = true;
    
    Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
    Camera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);
    Camera->bUsePawnControlRotation = false;
    
    /** Don't rotate when controller rotates */
    bUseControllerRotationYaw = false;
    bUseControllerRotationPitch = false;
    bUseControllerRotationRoll = false;
    
    if (GetCharacterMovement())
    {
        GetCharacterMovement()->bOrientRotationToMovement = true;
        GetCharacterMovement()->JumpZVelocity = 450.f;
        GetCharacterMovement()->AirControl = 0.3f;
    }
    
    MaxHealth = 100.f;
    Health = 90.f;
    
    Coins = 0;

    MaskOn = false;
}

// Called when the game starts or when spawned
void AWolf::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AWolf::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AWolf::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
    
    PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
    PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);
    
    PlayerInputComponent->BindAction("Interact", IE_Pressed, this, &AWolf::Interact);
    PlayerInputComponent->BindAction("WearMask", IE_Pressed, this, &AWolf::WearMask);
    
    PlayerInputComponent->BindAxis("Turn", this, &AWolf::Turn);
    PlayerInputComponent->BindAxis("LookUp", this, &AWolf::LookUp);
    PlayerInputComponent->BindAxis("MoveForward", this, &AWolf::MoveForward);
    PlayerInputComponent->BindAxis("MoveRight", this, &AWolf::MoveRight);

}

void AWolf::Turn(float Value)
{
    AddControllerYawInput(Value);
}

void AWolf::LookUp(float Value)
{
    AddControllerPitchInput(Value);
}

void AWolf::MoveForward(float Value)
{
    /** Find out which way is forward */
    const FRotator Rotation = Controller->GetControlRotation();
    const FRotator YawRotation(0.f, Rotation.Yaw, 0.f);
    
    /** Getting forward vector based of particular rotator */
    const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
    
    AddMovementInput(Direction, Value);
}

void AWolf::MoveRight(float Value)
{
    const FRotator Rotation = Controller->GetControlRotation();
    const FRotator YawRotation(0.f, Rotation.Yaw, 0.f);
    
    const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
    AddMovementInput(Direction, Value);
}


void AWolf::DecrementHealth(float Amount)
{
    if (Health > 0)
    {
        Health -= Amount;
    }
    else
    {
        Health = 0;
    }
}

void AWolf::IncrementHealth(float Amount)
{
    if (Health < MaxHealth)
    {
        Health += Amount;
    }
    else
    {
        Health = MaxHealth;
    }
}

void AWolf::AddCoins(int32 Amount)
{
    Coins += Amount;
}

void AWolf::Interact()
{
    if (AIToInteract)
    {
        HideInfo();
        int32 Index = AIToInteract->DialogLineNum++;
        
        if (Index < AIToInteract->DialogLinesArray.Num())
        {
            AIToInteract->Interact(this, AIToInteract->DialogLinesArray[Index]);
        }
        else
        {
            AIToInteract->DialogLineNum = 0;
            AIToInteract->StopInteracting(this);
        }
    }
}

void AWolf::WearMask()
{
    if (MaskToPutOn && !MaskOn)
    {
        HideInfo();
        MaskToPutOn->PutOn(this);
        MaskOn = true;
    }
    else if (MaskToPutOn && MaskOn)
    {
        MaskToPutOn->PutOff(this);
        MaskOn = false;
    }
}


void AWolf::HideInfo()
{
    if (OverlappingInfoVolume)
    {
        OverlappingInfoVolume->StopInteracting(this);
        OverlappingInfoVolume->Destroy();
        SetOverlappingInfoVolume(nullptr);
    }
}

void AWolf::TransitionLevel()
{
    UGameplayStatics::OpenLevel(GetWorld(), FName(TEXT("Game")));
}
