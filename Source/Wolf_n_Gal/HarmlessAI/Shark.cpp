// Fill out your copyright notice in the Description page of Project Settings.


#include "Shark.h"
#include "../Wolf/Wolf.h"
#include "Components/BoxComponent.h"
#include "../PlayerController/MainPlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystem.h"

// Sets default values
AShark::AShark()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
    
    InteractionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("InteractionBox"));
    InteractionBox->SetupAttachment(GetRootComponent());

    Price = 1;
    
    bPaid = false;
    
    StoryStatus = EStoryStatus::ESS_Untold;
    CurrentConversation = 0;
    
    bFirstInteraction = false;
    bHasMoreToSay = false;
}

// Called when the game starts or when spawned
void AShark::BeginPlay()
{
	Super::BeginPlay();
    
    InteractionBox->OnComponentBeginOverlap.AddDynamic(this, &AShark::OnOverlapBegin);
    InteractionBox->OnComponentEndOverlap.AddDynamic(this, &AShark::OnOverlapEnd);
}

// Called every frame
void AShark::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AShark::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AShark::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult)
{
    if (OtherActor)
    {
        AWolf* Wolf = Cast<AWolf>(OtherActor);
        
        if (Wolf && !bFirstInteraction)
        {
            bFirstInteraction = true;
            Price = Wolf->Coins + 1;
            UE_LOG(LogTemp, Warning, TEXT("1) price: %f, wolf coins: %f"), Price, Wolf->Coins);
        }
        
        if (Wolf && Wolf->Coins >= Price && !bPaid)
        {
            UE_LOG(LogTemp, Warning, TEXT("2) price: %f, wolf coins: %f"), Price, Wolf->Coins);
            bPaid = true;
            Wolf->Coins = 0;
            
            if (GetGoldParticles)
            {
                FVector Location = GetActorLocation() + GoldParticlesSpot;
                UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), GetGoldParticles, Location, FRotator(0.f), true);
            }
            
            if (DialogLineNum == 0) Interact(Wolf, "Press E to talk to Shark");
            SetStoryStatus(EStoryStatus::ESS_Intro);
        }
        
        if (Wolf && bPaid)
        {
            if (DialogLineNum == DialogLinesArray.Num()) DialogLineNum = 0;
            Wolf->SetAIToInteract(this);
        }
        
        if (Wolf && Wolf->MemoryCount != 0)
        {
            if (!Wolf->bMadeToMemoryResponseArray)
            {
                Wolf->bMadeToMemoryResponseArray = true;
                MakeDialogLineArray();
            }
               
            Wolf->MemoryCount = 0;
            Wolf->Interact();
            Wolf->MainPlayerController->ShowFinalChoice();
        }
    }
}
 
 void AShark::OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
    if (OtherActor)
    {
        AWolf* Wolf = Cast<AWolf>(OtherActor);
        
        if (Wolf)
        {
            StopInteracting(Wolf);
            Wolf->SetAIToInteract(nullptr);
        }
    }
}

void AShark::MakeDialogLineArray()
{
    DialogLinesArray.Empty();
    CurrentConversation++;
    
    if (DialogLinesTable)
    {
        TArray<FName> RowNames = DialogLinesTable->GetRowNames();
        
        for (auto Name : RowNames)
        {
            static const FString ContextString(TEXT("Context String"));
            FDialogLinesTable* Row = DialogLinesTable->FindRow<FDialogLinesTable>(Name, ContextString, true);
            
            if (Row->NPC_ID == Id && Row->Conversation_ID == CurrentConversation)
            {
                DialogLinesArray.Add(Row->Dialog);
            }
        }
    }
}
