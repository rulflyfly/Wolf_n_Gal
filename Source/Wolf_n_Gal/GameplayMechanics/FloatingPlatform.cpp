// Fill out your copyright notice in the Description page of Project Settings.


#include "FloatingPlatform.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "../Wolf/Wolf.h"

// Sets default values
AFloatingPlatform::AFloatingPlatform()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
    
    Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
    RootComponent = Mesh;
    
    Box = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
    Box->SetupAttachment(GetRootComponent());
    
    StartPoint = FVector(0.f);
    EndPoint = FVector(0.f);
    
    InterpSpeed = 1.f;
    InterpTime = 1.f;
    
    bInterping = true;
    
    ColorNum = 1;

}

// Called when the game starts or when spawned
void AFloatingPlatform::BeginPlay()
{
	Super::BeginPlay();
    
    StartPoint = GetActorLocation();
    
    EndPoint += StartPoint;
    Distance = (EndPoint - StartPoint).Size();
    
    Box->OnComponentBeginOverlap.AddDynamic(this, &AFloatingPlatform::OnOverlapBegin);
    Box->OnComponentEndOverlap.AddDynamic(this, &AFloatingPlatform::OnOverlapEnd);
    
    Box->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
    Box->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);
	
}

// Called every frame
void AFloatingPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

    if (bInterping)
    {
        FVector CurrentLocation = GetActorLocation();
        
        FVector Interp = FMath::VInterpTo(CurrentLocation, EndPoint, DeltaTime, InterpSpeed);
        SetActorLocation(Interp);
        
        float DistanceTraveled = (GetActorLocation() - StartPoint).Size();
        if (Distance - DistanceTraveled <= 1.f)
        {
            ToggleInterping();
            GetWorldTimerManager().SetTimer(InterpTimer, this, &AFloatingPlatform::ToggleInterping, InterpTime);
            SwapVectors(StartPoint, EndPoint);
        }
    }
}

void AFloatingPlatform::ToggleInterping()
{
    bInterping = !bInterping;
}

void AFloatingPlatform::SwapVectors(FVector& VectorOne, FVector& VectorTwo)
{
    FVector Temp = VectorOne;
    VectorOne = VectorTwo;
    VectorTwo = Temp;
}


void AFloatingPlatform::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult)
{
    if (OtherActor)
    {
        AWolf* Wolf = Cast<AWolf>(OtherActor);
        
        if (Wolf)
        {
            ColorNum = FMath::RandRange(1, 3);
            bPressed = true;
        }
    }
}

void AFloatingPlatform::OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
    if (OtherActor)
    {
        AWolf* LeavingWolf = Cast<AWolf>(OtherActor);
        
        if (LeavingWolf)
        {
            bPressed = false;
        }
    }
}
