// Copyright 2026 DME Games

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "RTUV_PlayerController.generated.h"

/**
 * 
 */
UCLASS()
class RTU_VILLAGE_API ARTUV_PlayerController : public APlayerController
{
	GENERATED_BODY()

	ARTUV_PlayerController();
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Player Controller")
	class ARTUV_PlayerPawn* PlayerPawnRef;
	
	// Multiplier for the Mouse Axis when panning.  Higher is faster.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Player Controller")
	float PanSensitivity = 5.0f; 

	// The amount per mouse wheel roll camera zooms in or out
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Player Controller")
	float ZoomStep = 50.f;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Player Controller")
	float MinZoomDistance = 500.f;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Player Controller")
	float MaxZoomDistance = 2500.f;
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaSeconds) override;
	
	// Sets up the player input
	virtual void SetupInputComponent() override;

private:
	// function to adjust movement speed, depending on how far the camera is zoomed
	float MovementSpeedCalculation() const;
	
	void MoveForward(float Value);
	void MoveRight(float Value);
	void FastMoveMultiplierPressed();
	void FastMoveMultiplierReleased();

	void PanCameraPressed();
	void PanCameraReleased();
	bool bIsPanning = false;
	void DealWithPanning();

	void Zoom(float Value);
	void CheckForEdgeMovement();
	float EdgeMoveSpeedX = 0.f;
	float EdgeMoveSpeedY = 0.f;
	
	bool bDisableCamNav = false;
	// Value that can be changed to move faster in the world
	float FastMoveMultiplier = 1.0f;

};
