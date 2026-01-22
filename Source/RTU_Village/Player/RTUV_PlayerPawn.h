// Copyright 2026 DME Games

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "RTUV_PlayerPawn.generated.h"

class USpringArmComponent;
class URTUV_PlayerWidget;
class ARTUV_PlayerController;

UCLASS()
class RTU_VILLAGE_API ARTUV_PlayerPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ARTUV_PlayerPawn();

	USpringArmComponent* GetSpringArmCompRef() const { return SpringArmComponent; }

	void NewDayStarted();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Player Pawn")
	USceneComponent* RootComp;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Player Pawn")
	UStaticMeshComponent* MeshComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Player Pawn")
	USpringArmComponent* SpringArmComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Player Pawn")
	class UCameraComponent* CameraComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Player Pawn")
	TSubclassOf<URTUV_PlayerWidget> PlayerWidget;

private:
	UPROPERTY()
	URTUV_PlayerWidget* PlayerWidgetRef;

	UPROPERTY()
	ARTUV_PlayerController* ControllerRef;
};
