// Fill out your copyright notice in the Description page of Project Settings.


#include "Wolf.h"
#include "Components/SkeletalMeshComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/CapsuleComponent.h"

// Sets default values
AWolf::AWolf()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
    
    SkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMeshComponent"));
    SkeletalMesh->SetupAttachment(GetRootComponent());
    
    SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
    SpringArm->SetupAttachment(GetRootComponent());
    SpringArm->TargetArmLength = 400.f;
    SpringArm->bUsePawnControlRotation = true;
    
    Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
    Camera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);
    Camera->bUsePawnControlRotation = false;
    
    /** Don't rotate when controller rotates */
    bUseControllerRotationYaw = false;
    bUseControllerRotationPitch = false;
    bUseControllerRotationRoll = false;

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
    
    PlayerInputComponent->BindAxis("Turn", this, &AWolf::Turn);
    PlayerInputComponent->BindAxis("LookUp", this, &AWolf::LookUp);

}

void AWolf::Turn(float Value)
{
    AddControllerYawInput(Value);
}

void AWolf::LookUp(float Value)
{
    AddControllerPitchInput(Value);
}
