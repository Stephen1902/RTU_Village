// Copyright 2026 DME Games

#include "RTUV_GameState.h"
#include "../Player/RTUV_PlayerWidget.h"
#include "RTU_Village/Player/RTUV_PlayerPawn.h"

ARTUV_GameState::ARTUV_GameState()
{
	// Game start items
	CurrentDay = 1;
	TreesStored = 5;
	RawFoodStored = 5;
	CookFoodStored = 5;
	HousesBuilt = 2;

	// Gameplay items
	DefenceComplete = 0.f;
	TreesPerPerson = 2;
	TreesNeededForDefence = 1.0f;
	DefencePerPerson = 2.0f;
	RawFoodPerPerson = 5.0f;
	RawFoodForCookedFood = 1.0f;
	CookedFoodPerPerson = 2;
	CookedFoodConsumed = 0.5f;
	TreesNeededPerHouse = 6;
	HouseBuiltPerPerson = 0.33f;

	DaysBeforeUprising = 30;

	Population = 4;
	PeoplePerHouse = 2;

	PlayerRef = nullptr;
	PlayerWidgetRef = nullptr;

	TreeFellersThisTurn = 0;
	DefenceBuildersThisTurn = 0;
	HouseBuildersThisTurn = 0;
	HuntersThisTurn = 0;
	CooksThisTurn = 0;

	ChanceOfRandom = 0.f;
	bNPCDiedThisTurn = false;

	static ConstructorHelpers::FObjectFinder<UDataTable> DT(TEXT("/Game/Framework/DT_GameTools"));
	if (DT.Succeeded())
	{
		ToolsDataTable = DT.Object;
	}
}

void ARTUV_GameState::BeginPlay()
{
	Super::BeginPlay();
	
}

void ARTUV_GameState::OnNewDayStarted()
{
	if (!PlayerRef || !PlayerWidgetRef) return;

	if (PlayerWidgetRef)
	{
		int32 AvailablePopulation = Population - (TreeFellersThisTurn + DefenceBuildersThisTurn + HouseBuildersThisTurn + HuntersThisTurn + CooksThisTurn);
		if (AvailablePopulation < 0 || bNPCDiedThisTurn)
		{
			AvailablePopulation = Population;
			TreesNeededPerHouse = 0;
			DefenceBuildersThisTurn = 0;
			HouseBuildersThisTurn = 0;
			HuntersThisTurn = 0;
			CooksThisTurn = 0;

			bNPCDiedThisTurn = false;
		}
		
		PlayerWidgetRef->NewDayStart(CurrentDay, DaysBeforeUprising, Population, AvailablePopulation, DefenceComplete, TreesStored, RawFoodStored, CookFoodStored, (HousesBuilt * PeoplePerHouse) - Population, DefenceBuildersThisTurn, TreeFellersThisTurn, HuntersThisTurn, CooksThisTurn, HouseBuildersThisTurn);
	}
	
	if (PlayerRef)
	{
		PlayerRef->NewDayStarted();
	}
}

void ARTUV_GameState::OnDayEnded()
{
	if (PlayerWidgetRef)
	{
		const float DefenceBuilt = BuildDefence();
		const int32 AnimalsHunted = HuntAnimals();
		const int32 FoodCooked = CookFood();
		const float HousingBuilt = BuildHousing();
		const int32 TreesChopped = ChopTrees();

		float RandomNumber = FMath::FRandRange(0.f, 100.f);
		if (RandomNumber > ChanceOfRandom)
		{
			HandleRandomEvent();
		}
		else
		{
			ChanceOfRandom += 20.f;
		}
		
		FString TextToSend = "The AI uprising has taken place.  AI controlled machines roam the land to end human life.\n\nYou and your small community have stayed out of the way but you have heard that a group of robots are heading in your direction.\n\nYou have "
		+ FString::FromInt(DaysBeforeUprising) + " days to build your defences, and to make sure your community is fed and housed.\n\nGood luck.";
		if (CurrentDay > 1)
		{
			TextToSend = "Nothing happened.";
			if (DefenceBuilt > 0.f)
			{
				TextToSend = FString::SanitizeFloat(DefenceBuilt) + "% of defence was built.\n\n";		
			}

			if (AnimalsHunted > 0)
			{
				TextToSend += FString::FromInt(AnimalsHunted) + "raw meat was added.\n\n";
			}

			
		}
		PlayerWidgetRef->OnDayEnd(FText::FromString(TextToSend));
	}

	OnNewDayStarted();
}

void ARTUV_GameState::OnStartDayClicked(int32 TreeFellers, int32 DefenceBuilders, int32 HouseBuilders, int32 Hunters, int32 Cooks)
{
	TreeFellersThisTurn = TreeFellers;
	DefenceBuildersThisTurn = DefenceBuilders;
	HouseBuildersThisTurn = HouseBuilders;
	HuntersThisTurn = Hunters;
	CooksThisTurn = Cooks;

	CurrentDay += 1;
	OnDayEnded();
}

void ARTUV_GameState::SetPlayerReferences(ARTUV_PlayerPawn* PlayerRefIn, URTUV_PlayerWidget* WidgetRefIn)
{
	if (PlayerRef == nullptr)
	{
		PlayerWidgetRef = WidgetRefIn;

		PlayerRef = PlayerRefIn;
		OnDayEnded();
	}
}

float ARTUV_GameState::BuildDefence()
{
	float AmountToReturn = 0.f;

	// Check if any builders have been assigned and if there are trees stored to use
	if (DefenceBuildersThisTurn > 0 && TreesStored > 0)
	{
		// Check if there is enough wood for the builders that are assigned
		if ((DefenceBuildersThisTurn * TreesNeededForDefence) <= TreesStored)
		{
			AmountToReturn = DefenceBuildersThisTurn * DefencePerPerson;
			TreesStored -= DefenceBuildersThisTurn * TreesNeededForDefence;
		}
		else
		{
			// There is not enough wood for the assigned builders
			AmountToReturn = TreesStored * DefencePerPerson;
			TreesStored = 0.f;
		}
	}
	DefenceComplete += AmountToReturn;
	return AmountToReturn;
}

int32 ARTUV_GameState::HuntAnimals()
{
	return HuntersThisTurn * RawFoodPerPerson;
}

int32 ARTUV_GameState::CookFood()
{
	int32 AmountToReturn = 0;

	// Check if there are any people assigned to cooking and if there is raw food available
	if (CooksThisTurn > 0 && RawFoodStored > 0)
	{
		// Check there is enough raw food for the cooks assigned
		if ((CooksThisTurn * RawFoodForCookedFood) <= RawFoodStored)
		{
			AmountToReturn = CooksThisTurn * CookedFoodPerPerson;
			RawFoodStored -= CooksThisTurn * RawFoodForCookedFood; 
		}
		else
		{
			// There are not enough raw food for the number assigned
			AmountToReturn = RawFoodStored * RawFoodForCookedFood;
			RawFoodStored = 0;
		}
	}

	CookFoodStored += AmountToReturn;
	return AmountToReturn;
}

float ARTUV_GameState::BuildHousing()
{
	
	return 0.f;
}

int32 ARTUV_GameState::ChopTrees()
{
	
	return 0;
}

void ARTUV_GameState::HandleRandomEvent()
{
	ChanceOfRandom = 20.f;
}
