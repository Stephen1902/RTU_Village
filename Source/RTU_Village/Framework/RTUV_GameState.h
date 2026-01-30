// Copyright 2026 DME Games

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "GameFramework/GameStateBase.h"
#include "RTUV_GameState.generated.h"

class URTUV_PlayerWidget;
class ARTUV_PlayerPawn;
/**
 * 
 */

UENUM() 
enum class EToolEnum : uint8
{
	EAxe	UMETA(DisplayName="Axe"),
	EShovel UMETA(DisplayName="Shovel"),
	EHammer UMETA(DisplayName="Hammer"),
	EBow	UMETA(DisplayName="Bow"),
	EKnife	UMETA(DisplayName="Knife")
};

USTRUCT()
struct FTools : public FTableRowBase
{
	GENERATED_BODY()
	
	UPROPERTY(EditDefaultsOnly, Category="Tools")
	FText ToolName;

	UPROPERTY(EditDefaultsOnly, Category="Tools")
	FText ToolDescription;

	UPROPERTY(EditDefaultsOnly, Category="Tools")
	EToolEnum ToolType;
	
	UPROPERTY(EditDefaultsOnly, Category="Tools")
	float IncreaseMultiplier;

	FTools()
	{
		ToolName = FText::FromString("Tool Name.");
		ToolDescription = FText::FromString("Text of what this tool does goes here.");
		ToolType = EToolEnum::EAxe;
		IncreaseMultiplier = 0.5f;
	}
};

UCLASS()
class RTU_VILLAGE_API ARTUV_GameState : public AGameStateBase
{
	GENERATED_BODY()

	ARTUV_GameState();
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// The number of days before end game happens
	UPROPERTY(EditDefaultsOnly, Category = "Game Start")
	int32 DaysBeforeUprising;

	// How many trees are in storage at Begin Play
	UPROPERTY(EditDefaultsOnly, Category = "Game Start")
	float TreesStored;

	// How much raw food is stored at Begin Play
	UPROPERTY(EditDefaultsOnly, Category = "Game Start")
	int32 RawFoodStored;

	// How much cooked food is stored at Begin Play
	UPROPERTY(EditDefaultsOnly, Category = "Game Start")
	int32 CookFoodStored;

	// How many houses have been built at Begin Play
	UPROPERTY(EditDefaultsOnly, Category = "Game Start")
	float HousesBuilt;

	// How many people each house can hold
	UPROPERTY(EditDefaultsOnly, Category = "Game Start")
	int32 PeoplePerHouse;

	// Tools available at Begin Play
	UPROPERTY(EditDefaultsOnly, Category = "Game Start")
	TMap<EToolEnum, int32> AvailableTools;
	
	// The amount of defence completed
	UPROPERTY(VisibleAnywhere, Category = "Gameplay")
	float DefenceComplete;

	// The number of people needed to collect one tree;
	UPROPERTY(EditDefaultsOnly, Category = "Gameplay")
	int32 TreesPerPerson;
	
	// The number of trees needed for 1% of defence
	UPROPERTY(EditDefaultsOnly, Category = "Gameplay")
	float TreesNeededForDefence;

	// The number of people for 1% of defence
	UPROPERTY(EditDefaultsOnly, Category = "Gameplay")
	float DefencePerPerson;

	// The number of raw food gathered by 1 person
	UPROPERTY(EditDefaultsOnly, Category = "Gameplay")
	int32 RawFoodPerPerson;
	
	// The number of raw food needed to make 1 cooked food
	UPROPERTY(EditDefaultsOnly, Category = "Gameplay")
	float RawFoodForCookedFood;

	// The number of cooked food made by 1 person
	UPROPERTY(EditDefaultsOnly, Category = "Gameplay")
	int32 CookedFoodPerPerson;

	// The amount of trees needed for 1 house
	UPROPERTY(EditDefaultsOnly, Category = "Gameplay")
	int32 TreesNeededPerHouse;
	
	// The amount of a house built by 1 person
	UPROPERTY(EditDefaultsOnly, Category = "Gameplay")
	float HouseBuiltPerPerson;
	
	// How much food each person eats
	UPROPERTY(EditDefaultsOnly, Category = "Gameplay")
	float CookedFoodConsumed;
	
private:
	int32 CurrentDay;
	int32 Population;
	int32 TreeFellersThisTurn;
	int32 DefenceBuildersThisTurn;
	int32 HouseBuildersThisTurn;
	int32 HuntersThisTurn;
	int32 CooksThisTurn;

	UPROPERTY()
	UDataTable* ToolsDataTable;

	UPROPERTY()
	ARTUV_PlayerPawn* PlayerRef;

	UPROPERTY()
	URTUV_PlayerWidget* PlayerWidgetRef;

	bool bNPCDiedThisTurn;
public:
	void OnStartDayClicked(int32 TreeFellers, int32 DefenceBuilders, int32 HouseBuilders, int32 Hunters, int32 Cooks);
	
	void SetPlayerReferences(ARTUV_PlayerPawn* PlayerRefIn, URTUV_PlayerWidget* WidgetRefIn);

	void OnNewDayStarted();
	void OnDayEnded();
	int32 GetCurrentDay() const { return CurrentDay; }

private:
	float BuildDefence();
	int32 HuntAnimals();
	int32 CookFood();
	float BuildHousing();
	int32 ChopTrees();

	float ChanceOfRandom;
	void HandleRandomEvent();
};
