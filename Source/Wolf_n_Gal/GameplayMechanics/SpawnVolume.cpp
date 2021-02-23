// Fill out your copyright notice in the Description page of Project Settings.


#include "SpawnVolume.h"
#include "Components/BoxComponent.h"
#include "Coin.h"
#include "PlayerMemory.h"
#include "Kismet/KismetMathLibrary.h"
#include "Coin.h"
#include "Potion.h"
#include "Portal.h"

// Sets default values
ASpawnVolume::ASpawnVolume()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
    
    ExtentBox = CreateDefaultSubobject<UBoxComponent>(TEXT("ExtentBox"));
    RootComponent = ExtentBox;

    FirstQuarterBox = CreateDefaultSubobject<UBoxComponent>(TEXT("FirstQuarterBox"));
    FirstQuarterBox->SetupAttachment(GetRootComponent());
    
    SecondQuarterBox = CreateDefaultSubobject<UBoxComponent>(TEXT("SecondQuarterBox"));
    SecondQuarterBox->SetupAttachment(GetRootComponent());
    
    ThirdQuarterBox = CreateDefaultSubobject<UBoxComponent>(TEXT("ThirdQuarterBox"));
    ThirdQuarterBox->SetupAttachment(GetRootComponent());
    
    FourthQuarterBox = CreateDefaultSubobject<UBoxComponent>(TEXT("FourthQuarterBox"));
    FourthQuarterBox->SetupAttachment(GetRootComponent());
    
    PortalLocation = FVector(34857.f, 32750.f, -1617.f);
}

// Called when the game starts or when spawned
void ASpawnVolume::BeginPlay()
{
	Super::BeginPlay();
	
    BoxArray.Add(FirstQuarterBox);
    BoxArray.Add(SecondQuarterBox);
    BoxArray.Add(ThirdQuarterBox);
    BoxArray.Add(FourthQuarterBox);
    
    ExtentBox->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);
}

// Called every frame
void ASpawnVolume::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

FVector ASpawnVolume::GetSpawnPoint(UBoxComponent* TargetBox)
{
    FVector Extent = TargetBox->GetScaledBoxExtent();
    FVector Origin = TargetBox->GetComponentLocation();
    
    return UKismetMathLibrary::RandomPointInBoundingBox(Origin, Extent);
}

void ASpawnVolume::SpawnCoinsAfterFirstEncounter()
{
    for (auto Box : BoxArray)
    {
        FActorSpawnParameters SpawnParams;
        FVector Location = GetSpawnPoint(Box);
        GetWorld()->SpawnActor<ACoin>(Coin, Location, FRotator(0.f), SpawnParams);
    }
}

void ASpawnVolume::SpawnMemoryRecorder()
{
    int32 RandomIndex = FMath::RandRange(0, 3);
    UBoxComponent* Box = BoxArray[RandomIndex];
    
    FActorSpawnParameters SpawnParams;
    FVector Location = GetSpawnPoint(Box);
    GetWorld()->SpawnActor<APlayerMemory>(MemoryRecorder, Location, FRotator(0.f), SpawnParams);
}

void ASpawnVolume::SpawnPotion()
{
    for (auto Box : BoxArray)
    {
        FActorSpawnParameters SpawnParams;
        FVector Location = GetSpawnPoint(Box);
        GetWorld()->SpawnActor<APotion>(Potion, Location, FRotator(0.f), SpawnParams);
    }
}

void ASpawnVolume::SpawnPortal()
{
    FActorSpawnParameters SpawnParams;
    FVector Location = PortalLocation;
    GetWorld()->SpawnActor<APortal>(Portal, Location, FRotator(0.f), SpawnParams);
}
