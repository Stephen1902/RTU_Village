// Copyright 2026 DME Games

#include "PlayerPawn.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"

// Sets default values
ARTUV_PlayerPawn::ARTUV_PlayerPawn()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	RootComp = CreateDefaultSubobject<USceneComponent>("Root Comp");
	SetRootComponent(RootComp);

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("Mesh Comp");
	MeshComponent->SetupAttachment(RootComp);
	MeshComponent->SetRelativeLocation(FVector(0.f, 0.f, 100.f));
	MeshComponent->SetRelativeRotation(FRotator(-70.f, 0.f, 0.f));

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>("Spring Arm Comp");
	SpringArmComponent->SetupAttachment(MeshComponent);
	SpringArmComponent->TargetArmLength = 1500.f;

	CameraComponent = CreateDefaultSubobject<UCameraComponent>("Camera Comp");
	CameraComponent->SetupAttachment(SpringArmComponent);
}

// Called when the game starts or when spawned
void ARTUV_PlayerPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

