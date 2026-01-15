// Copyright 2026 DME Games

#include "RTUV_GameState.h"

ARTUV_GameState::ARTUV_GameState()
{
	// Game start items
	CurrentDay = 1;
	TreesStored = 0;
	RawFoodStored = 5;
	CookFoodStored = 5;
	HousesBuilt = 2;

	// Gameplay items
	DefenceComplete = 0.f;
	TreesPerPerson = 2;
	TreesNeededForDefence = 0.5f;
	DefencePerPerson = 2.0f;
	RawFoodPerPerson = 5.0f;
	RawFoodForCookedFood = 1.0f;
	CookedFoodPerPerson = 4;
	CookedFoodConsumed = 0.5f;
	TreesNeededPerHouse = 8;
	HouseBuiltPerPerson = 0.33f;

	DaysBeforeUprising = 30;

	Population = 4;

	static ConstructorHelpers::FObjectFinder<UDataTable> DT(TEXT("/Game/Framework/DT_GameTools"));
	if (DT.Succeeded())
	{
		ToolsDataTable = DT.Object;
	}
}
