// Fill out your copyright notice in the Description page of Project Settings.


#include "HarmlessAI.h"
#include "AIController.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/BoxComponent.h"
#include "../Wolf/Wolf.h"

// Sets default values
AHarmlessAI::AHarmlessAI()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    Moving = true;
    
    GetCapsuleComponent()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Camera, ECollisionResponse::ECR_Ignore);
    GetMesh()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Camera, ECollisionResponse::ECR_Ignore);
    
    InteractionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("InteractionBox"));
    InteractionBox->SetupAttachment(GetRootComponent());
    
    if (GetCharacterMovement())
    {
        GetCharacterMovement()->bOrientRotationToMovement = true;
    }
}

// Called when the game starts or when spawned
void AHarmlessAI::BeginPlay()
{
	Super::BeginPlay();
	
    InteractionBox->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
    InteractionBox->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);
    
    InteractionBox->OnComponentBeginOverlap.AddDynamic(this, &AHarmlessAI::OnOverlapBegin);
    InteractionBox->OnComponentEndOverlap.AddDynamic(this, &AHarmlessAI::OnOverlapEnd);
    
    if (DialogLinesTable)
    {
        TArray<FName> RowNames = DialogLinesTable->GetRowNames();
        
        for (auto Name : RowNames)
        {
            static const FString ContextString(TEXT("Context String"));
            FDialogLinesTable* Row = DialogLinesTable->FindRow<FDialogLinesTable>(Name, ContextString, true);
            
            if (Row->NPC_ID == Id)
            {
                DialogLinesArray.Add(Row->Dialog);
            }
        }
    }
}

// Called every frame
void AHarmlessAI::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AHarmlessAI::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AHarmlessAI::Move(FVector Location)
{
    AIController = Cast<AAIController>(GetController());
    
    if (AIController && Moving)
    {
        Moving = false;
        FAIMoveRequest MoveRequest;
        MoveRequest.SetGoalLocation(Location);
        MoveRequest.SetAcceptanceRadius(5.f);
        
        FNavPathSharedPtr NavPath;
        
        AIController->MoveTo(MoveRequest, &NavPath);
    }
}


void AHarmlessAI::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult)
{
    if (OtherActor && Interactive)
    {
        AWolf* Wolf = Cast<AWolf>(OtherActor);
        
        if (Wolf)
        {
            Wolf->SetAIToInteract(this);
        }
    }
}

void AHarmlessAI::OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
    if (OtherActor && Interactive)
    {
        AWolf* Wolf = Cast<AWolf>(OtherActor);
        
        if (Wolf)
        {
            Wolf->SetAIToInteract(nullptr);
        }
    }
}
