// Copyright 2026 DME Games

#include "RTUV_PlayerController.h"

#include "RTUV_PlayerPawn.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/KismetMathLibrary.h"

ARTUV_PlayerController::ARTUV_PlayerController()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PlayerPawnRef = nullptr;
}

void ARTUV_PlayerController::BeginPlay()
{
	Super::BeginPlay();

	PlayerPawnRef = Cast<ARTUV_PlayerPawn>(GetPawn());

	if (!PlayerPawnRef)
	{
		UE_LOG(LogTemp, Warning, TEXT("Failed to get player pawn reference in VVPlayerController"));
	}

	// Call to ensure we're not trying to pan on game start
	PanCameraReleased();
}

void ARTUV_PlayerController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (bIsPanning)
	{
		DealWithPanning();
	}
	else
	{
		CheckForEdgeMovement();
	}
}

void ARTUV_PlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	// Movement actions
	InputComponent->BindAxis("Forward", this, &ARTUV_PlayerController::MoveForward);
	InputComponent->BindAxis("Right", this, &ARTUV_PlayerController::MoveRight);
	InputComponent->BindAction("Pan", IE_Pressed, this, &ARTUV_PlayerController::PanCameraPressed);
	InputComponent->BindAction("Pan", IE_Released, this, &ARTUV_PlayerController::PanCameraReleased);
	
	InputComponent->BindAction("ToggleFastMove", IE_Pressed, this, &ARTUV_PlayerController::FastMoveMultiplierPressed);
	InputComponent->BindAction("ToggleFastMove", IE_Released, this, &ARTUV_PlayerController::FastMoveMultiplierReleased);

	InputComponent->BindAxis("Zoom", this, &ARTUV_PlayerController::Zoom);

	InputComponent->BindAxis("MOUSEX");
	InputComponent->BindAxis("MOUSEY");
}

float ARTUV_PlayerController::MovementSpeedCalculation() const
{
	if (PlayerPawnRef)
	{
		const float CurrentArmLength = PlayerPawnRef->GetSpringArmCompRef()->TargetArmLength / 100.f;
		return FMath::ClampAngle(CurrentArmLength, 5.0f, 20.f);
	}

	return 10.f;
}

void ARTUV_PlayerController::MoveForward(float Value)
{
	if (Value != 0.f && !bDisableCamNav && PlayerPawnRef)
	{
		// Calculate how much to move this time, based on zoom level and whether player is asking for fast move
		const float MoveThisTime = (MovementSpeedCalculation() * FastMoveMultiplier) * Value;
		// Create a vector that only allows forward and backward movement
		const FVector NewVector = FVector(MoveThisTime, 0.f, 0.f);
		// Get the player location and rotation, set the relative forward movement
		const FTransform PlayerTransform = PlayerPawnRef->GetActorTransform();
		const FVector ForwardTransform = UKismetMathLibrary::TransformDirection(PlayerTransform, NewVector);
		// Add the new location to the existing location
		const FVector NewLocation = PlayerTransform.GetLocation() + ForwardTransform;
		// Make a new transform based on calculated and existing values
		const FTransform NewTransform = FTransform(PlayerTransform.GetRotation(), NewLocation, PlayerTransform.GetScale3D());
		// Set the player to the new location
		PlayerPawnRef->SetActorTransform(NewTransform);

		// When rotating, Z can be altered.  Correct this
		PlayerPawnRef->SetActorLocation(FVector(PlayerPawnRef->GetActorLocation().X, PlayerPawnRef->GetActorLocation().Y, 100.f));
	}
}

void ARTUV_PlayerController::MoveRight(float Value)
{
	if (Value != 0.f && !bDisableCamNav && PlayerPawnRef)
	{
		// Calculate how much to move this time, based on zoom level and whether player is asking for fast move
		const float MoveThisTime = (MovementSpeedCalculation() * FastMoveMultiplier) * Value;
		// Create a vector that only allows forward and backward movement
		const FVector NewVector = FVector(0.f, MoveThisTime, 0.f);
		// Get the player location and rotation, set the relative forward movement
		const FTransform PlayerTransform = PlayerPawnRef->GetActorTransform();
		const FVector ForwardTransform = UKismetMathLibrary::TransformDirection(PlayerTransform, NewVector);
		// Add the new location to the existing location
		const FVector NewLocation = PlayerTransform.GetLocation() + ForwardTransform;
		// Make a new transform based on calculated and existing values
		const FTransform NewTransform = FTransform(PlayerTransform.GetRotation(), NewLocation, PlayerTransform.GetScale3D());
		// Set the player to the new location
		PlayerPawnRef->SetActorTransform(NewTransform);

		// When rotating, Z can be altered.  Correct this
		PlayerPawnRef->SetActorLocation(FVector(PlayerPawnRef->GetActorLocation().X, PlayerPawnRef->GetActorLocation().Y, 100.f));
	}
}

void ARTUV_PlayerController::FastMoveMultiplierPressed()
{
	FastMoveMultiplier = 2.0f;
}

void ARTUV_PlayerController::FastMoveMultiplierReleased()
{
	FastMoveMultiplier = 1.0f;
}

void ARTUV_PlayerController::PanCameraPressed()
{
	bDisableCamNav = true;
	bIsPanning = true;
}

void ARTUV_PlayerController::PanCameraReleased()
{
	bDisableCamNav = false;
	bIsPanning = false;
}

void ARTUV_PlayerController::DealWithPanning()
{
	if (PlayerPawnRef)
	{
		// Get the value the Mouse Axis and multiply by the pan sensitivity set in BP
		const float MouseXFloat = InputComponent->GetAxisValue(TEXT("MOUSEX")) * PanSensitivity;
		const float MouseYFloat = InputComponent->GetAxisValue(TEXT("MOUSEY")) * PanSensitivity;
		// Get the current player rotation
		FRotator PlayerRot = PlayerPawnRef->GetActorRotation();
		// X runs on the Yaw.  Adjust this one only
		const float NewYaw = PlayerRot.Yaw + MouseXFloat;
		// Y runs on the Pitch.  Adjust this, but clamp it to avoid issues with clipping through the scenery
		const float NewPitch = FMath::Clamp(PlayerRot.Pitch + MouseYFloat, -15.f, 45.f);
		
		// Set the new actor Transform, based on the calculations above
		PlayerPawnRef->SetActorRotation(FRotator(NewPitch, NewYaw, PlayerRot.Roll));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("No PlayerPawnRef in VVPlayerController."));
	}
}

void ARTUV_PlayerController::Zoom(float Value)
{
	if (Value != 0.f && PlayerPawnRef)
	{
		// Get the current arm length
		float NewTargetLength = PlayerPawnRef->GetSpringArmCompRef()->TargetArmLength;
		// Adjust the length depending on which way the mouse wheel has been moved
		if (Value > 0.f)
		{
			NewTargetLength -= ZoomStep;
		}
		else
		{
			NewTargetLength += ZoomStep;
		}
		// Clamp the value, based on the min and max zoom distances
		NewTargetLength = FMath::Clamp(NewTargetLength, MinZoomDistance, MaxZoomDistance);
		// Set the arm length
		PlayerPawnRef->GetSpringArmCompRef()->TargetArmLength = NewTargetLength;
	}
}

void ARTUV_PlayerController::CheckForEdgeMovement()
{
	if (PlayerPawnRef)
	{
		float MouseXFloat, MouseYFloat;
		GetMousePosition(MouseXFloat, MouseYFloat);
			
		if (MouseXFloat != 0.f || MouseYFloat != 0.f)
		{
			int32 ViewportX, ViewportY;
			GetViewportSize(ViewportX, ViewportY);
			float MouseLocX, MouseLocY;
			GetMousePosition(MouseLocX, MouseLocY);

			if (MouseXFloat != 0.f)
			{
				if ((MouseLocX / ViewportX) > .975f)
				{
					EdgeMoveSpeedX = 5.0f * FastMoveMultiplier;
				}
				else if ((MouseLocX / ViewportX) < .025f)
				{
					EdgeMoveSpeedX = -5.0f * FastMoveMultiplier;
				}
				else
				{
					EdgeMoveSpeedX = 0.f;
				}
			}

			if (MouseYFloat != 0.f)
			{
				if ((MouseLocY / ViewportY) > .975f)
				{
					EdgeMoveSpeedY = -5.0f * FastMoveMultiplier;
				}
				else if ((MouseLocY / ViewportY) < .025f)
				{
					EdgeMoveSpeedY = 5.0f * FastMoveMultiplier;
				}
				else
				{
					EdgeMoveSpeedY = 0.f;
				}
			}
		}

		PlayerPawnRef->AddActorLocalOffset(FVector(EdgeMoveSpeedY, EdgeMoveSpeedX, 0.f));
	}
}
