// Copyright 2026 DME Games

#include "RTUV_PlayerPawn.h"
#include "RTUV_PlayerController.h"
#include "RTUV_PlayerWidget.h"
#include "Blueprint/UserWidget.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"
#include "RTU_Village/Framework/RTUV_GameState.h"

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

void ARTUV_PlayerPawn::NewDayStarted()
{
	if (PlayerWidgetRef && ControllerRef)
	{
		PlayerWidgetRef->AddToViewport();
		ControllerRef->SetWidgetOnScreen(true);
	}
}

// Called when the game starts or when spawned
void ARTUV_PlayerPawn::BeginPlay()
{
	Super::BeginPlay();
	
	ControllerRef = Cast<ARTUV_PlayerController>(GetController());
	if (PlayerWidget && ControllerRef)
	{
		PlayerWidgetRef = CreateWidget<URTUV_PlayerWidget>(ControllerRef, PlayerWidget);

		ARTUV_GameState* GS = Cast<ARTUV_GameState>(UGameplayStatics::GetGameState(GetWorld()));
		if (GS)
		{
			GS->SetPlayerReferences(this, PlayerWidgetRef);
		}
	}
}

