// Copyright 2026 DME Games

#include "RTUV_GameState.h"
#include "../Player/RTUV_PlayerWidget.h"
#include "RTU_Village/Player/RTUV_PlayerPawn.h"

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
	PeoplePerHouse = 2;

	PlayerRef = nullptr;
	PlayerWidgetRef = nullptr;

	TreeFellersThisTurn = 0;
	DefenceBuildersThisTurn = 0;
	HouseBuildersThisTurn = 0;
	HuntersThisTurn = 0;
	CooksThisTurn = 0;

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
		FString TextToSend = "The AI uprising has taken place";
		if (CurrentDay > 1)
		{
			TextToSend = "Day review goes here.";				
		}
		PlayerWidgetRef->OnDayEnd(FText::FromString(TextToSend));
	}

	OnNewDayStarted();
}

void ARTUV_GameState::OnStartDayClicked(int32 TreeFellers, int32 DefenceBuilders, int32 HouseBuilders, int32 Hunters, int32 Cooks)
{
	if (!PlayerWidgetRef) return;

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
