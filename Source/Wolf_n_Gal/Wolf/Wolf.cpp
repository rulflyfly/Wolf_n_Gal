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
#include "../PlayerController/MainPlayerController.h"
#include "Animation/AnimMontage.h"
#include "Animation/AnimInstance.h"
#include "../GameplayMechanics/SaveSpot.h"
#include "../GameplayMechanics/PlayerMemory.h"
#include "../HarmlessAI/Shark.h"
#include "../GameplayMechanics/SpawnVolume.h"
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

    bMaskOn = false;
    
    MemoryCount = 0;
    
    bRepeat = false;
    
    bMadeStoryIntroArray = false;
    
    MemoryCount = 0;
    
    bMadeToMemoryResponseArray = false;
    
    bFinalChoice = false;
    
    bPotionSpawned = false;
    
    MemoryRecordersAmountToSpawn = 7;
    
    bGoingToPortal = false;
    
    bInWater = false;
}

// Called when the game starts or when spawned
void AWolf::BeginPlay()
{
	Super::BeginPlay();
	
    MainPlayerController = Cast<AMainPlayerController>(GetController());
    
    TArray<AActor*> OverlappingActors;
    GetOverlappingActors(OverlappingActors, SpawnVolumeClass);
    
    for (auto Actor : OverlappingActors)
    {
        ASpawnVolume* NewSpawnVolume = Cast<ASpawnVolume>(Actor);
        if (NewSpawnVolume) SpawnVolume = NewSpawnVolume;
    }
}

// Called every frame
void AWolf::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

    if (bBeingDamaged && SaveSpotThatWasLeft)
    {
        DecrementHealth(SaveSpotThatWasLeft->DamageIfLeft * DeltaTime);
    }
    
    if (Health < 30 && !bPotionSpawned)
    {
        bPotionSpawned = true;
        SpawnVolume->SpawnPotion();
    }
}

// Called to bind functionality to input
void AWolf::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
    
    PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AWolf::Jump);
    PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);
    
    PlayerInputComponent->BindAction("Interact", IE_Pressed, this, &AWolf::Interact);
    PlayerInputComponent->BindAction("WearMask", IE_Pressed, this, &AWolf::WearMask);
    PlayerInputComponent->BindAction("TogglePause", IE_Pressed, this, &AWolf::TogglePause);
    PlayerInputComponent->BindAction("RecordMemory", IE_Pressed, this, &AWolf::RecordMemory);
    
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
    if (GamePaused() || bIsDead || bFinalChoice) return;
    /** Find out which way is forward */
    const FRotator Rotation = Controller->GetControlRotation();
    const FRotator YawRotation(0.f, Rotation.Yaw, 0.f);
    
    /** Getting forward vector based of particular rotator */
    const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
    
    AddMovementInput(Direction, Value);
}

void AWolf::MoveRight(float Value)
{
    if (GamePaused() || bIsDead || bFinalChoice) return;
    const FRotator Rotation = Controller->GetControlRotation();
    const FRotator YawRotation(0.f, Rotation.Yaw, 0.f);
    
    const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
    AddMovementInput(Direction, Value);
}


void AWolf::DecrementHealth(float Amount)
{
    if (GamePaused() || bIsDead) return;
    if (Health > 0)
    {
        Health -= Amount;
    }
    else
    {
        Health = 0;
        Die();
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
    AHarmlessAI* Fishes = Cast<AHarmlessAI>(AIToInteract);
    AShark* Shark = Cast<AShark>(AIToInteract);
                                 
    if (Fishes)
    {
        HideInfo();
        int32 Index = Fishes->DialogLineNum++;
        Fishes->bHasMoreToSay = true;
        
        if (Index < Fishes->DialogLinesArray.Num())
        {
            Fishes->Interact(this, Fishes->DialogLinesArray[Index]);
        }
        else
        {
            Fishes->bHasMoreToSay = false;
            Fishes->DialogLineNum = 0;
            Fishes->StopInteracting(this);
        }
    }
    else if (Shark)
    {
        if (Shark->StoryStatus == EStoryStatus::ESS_Intro)
        {
            HideInfo();
            if (!bMadeStoryIntroArray)
            {
                bMadeStoryIntroArray = true;
                Shark->MakeDialogLineArray();
            }
            
            Shark->bHasMoreToSay = true;
            int32 Index = Shark->DialogLineNum++;
            
            if (Index < Shark->DialogLinesArray.Num())
            {
                Shark->Interact(this, Shark->DialogLinesArray[Index]);
            }
            else
            {
                Shark->bHasMoreToSay = false;
                Shark->SetStoryStatus(EStoryStatus::ESS_WaitingForMemories);
                Shark->DialogLineNum = 0;
                Shark->StopInteracting(this);
                SpawnVolume->SpawnMemoryRecorder();
            }
        } else if (Shark->StoryStatus == EStoryStatus::ESS_WaitingForMemories)
        {
            HideInfo();
            if (!bRepeat)
            {
                bRepeat = true;
                Shark->MakeDialogLineArray();
            }
            
            int32 Index = Shark->DialogLineNum++;
            
            if (Index < Shark->DialogLinesArray.Num())
            {
                Shark->Interact(this, Shark->DialogLinesArray[Index]);
            }
            else
            {
                Shark->bHasMoreToSay = false;
                Shark->DialogLineNum = 0;
                Shark->StopInteracting(this);
                
            }
            
        } else if (Shark->StoryStatus == EStoryStatus::ESS_FinalWords)
        {
            int32 Index = Shark->DialogLineNum++;
            Shark->bHasMoreToSay = true;
            if (Index < Shark->DialogLinesArray.Num())
            {
                Shark->Interact(this, Shark->DialogLinesArray[Index]);
            }
            else
            {
                MainPlayerController->HideHealthBar();
                bGoingToPortal = true;
                if (Shark->DestroyParticles) UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), Shark->DestroyParticles, Shark->GetActorLocation(), FRotator(0.f), true);
                Shark->Destroy();
                SetAIToInteract(nullptr);
                SpawnVolume->SpawnPortal();
            }
        }
    }
}

void AWolf::WearMask()
{
    if (GamePaused() || bIsDead) return;
    if (MaskToPutOn && !bMaskOn)
    {
        HideInfo();
        MaskToPutOn->PutOn(this);
        
    }
    else if (MaskToPutOn && bMaskOn)
    {
        MaskToPutOn->PutOff(this);
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

void AWolf::TogglePause()
{
    if (MainPlayerController)
    {
        MainPlayerController->TogglePause();
    }
}

bool AWolf::GamePaused()
{
    if (MainPlayerController) return MainPlayerController->bGamePaused;
    else return false;
}

void AWolf::Jump()
{
    if (GamePaused() || bIsDead) return;
    Super::Jump();
}

void AWolf::Die()
{
    bIsDead = true;
    UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
    if (AnimInstance && DeathMontage && MainPlayerController)
    {
        MainPlayerController->HideDialogBox();
        MainPlayerController->ShowGameOverMenu();
        AnimInstance->Montage_Play(DeathMontage, 0.5f);
        AnimInstance->Montage_JumpToSection(FName("Death"), DeathMontage);
    }
}

void AWolf::DeathEnd()
{
    GetMesh()->bPauseAnims = true;
    GetMesh()->bNoSkeletonUpdate = true;
}

void AWolf::RecordMemory()
{
    if (MainPlayerController && MemoryRecorder)
    {
        bRecordingMemory = true;
        MemoryRecorder->StopInteracting(this);
        MainPlayerController->ShowMemoryInput();
    }
}

void AWolf::SaveMemory(FString Memory)
{
    if (MainPlayerController && MemoryRecorder)
    {
        MainPlayerController->HideMemoryInput();
        Memories.Add(Memory);
        MemoryRecorder->PlayDeathEffect();
        MemoryRecorder->Destroy();
        SetMemoryRecorder(nullptr);
        MemoryCount++;
    }
}

void AWolf::FinishStory()
{
    if (AIToInteract)
    {
        AShark* Shark = Cast<AShark>(AIToInteract);
        
        if (Shark)
        {
            Shark->SetStoryStatus(EStoryStatus::ESS_FinalWords);
            Shark->MakeDialogLineArray();
            Shark->DialogLineNum = 0;
            Interact();
        }
    }
}

void AWolf::ContinuePlaying()
{
    if (SpawnVolume)
    {
        for (int32 i = 0; i < MemoryRecordersAmountToSpawn; i++)
        {
            SpawnVolume->SpawnMemoryRecorder();
        }
    }
}

void AWolf::EndGame()
{
    if (MainPlayerController)
    {
        MainPlayerController->ShowFinishGame();
    }
}
