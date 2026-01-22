// Copyright 2026 DME Games

#include "RTUV_PlayerWidget.h"
#include "../Framework/RTUV_GameState.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"

void URTUV_PlayerWidget::NativeConstruct()
{
	Super::NativeConstruct();

	GameStateRef = Cast<ARTUV_GameState>(UGameplayStatics::GetGameState(GetWorld()));

	BtnTreeReduce->OnClicked.AddDynamic(this, &URTUV_PlayerWidget::OnBtnTreeReduceClicked);
	BtnTreeIncrease->OnClicked.AddDynamic(this, &URTUV_PlayerWidget::OnBtnTreeIncreaseClicked);

	BtnDefenceReduce->OnClicked.AddDynamic(this, &URTUV_PlayerWidget::OnBtnDefenceReduceClicked);
	BtnDefenceIncrease->OnClicked.AddDynamic(this, &URTUV_PlayerWidget::OnBtnDefenceIncreaseClicked);

	BtnHuntReduce->OnClicked.AddDynamic(this, &URTUV_PlayerWidget::OnBtnHuntReduceClicked);
	BtnHuntIncrease->OnClicked.AddDynamic(this, &URTUV_PlayerWidget::OnBtnHuntIncreaseClicked);

	BtnCookReduce->OnClicked.AddDynamic(this, &URTUV_PlayerWidget::OnBtnCookReduceClicked);
	BtnCookIncrease->OnClicked.AddDynamic(this, &URTUV_PlayerWidget::OnBtnCookIncreaseClicked);

	BtnHousingReduce->OnClicked.AddDynamic(this, &URTUV_PlayerWidget::OnBtnHousingReduceClicked);
	BtnHousingIncrease->OnClicked.AddDynamic(this, &URTUV_PlayerWidget::OnBtnHousingIncreaseClicked);

	BtnBeginDay->OnClicked.AddDynamic(this, &URTUV_PlayerWidget::OnBtnBeginDayClicked);
}

void URTUV_PlayerWidget::NewDayStart(int32 CurrentDay, int32 TotalDays, int32 AvailablePeople, float DefenceComplete, int32 TreesStored, int32 RawFoodStored, int32 CookedFoodStored, int32 HousesBuilt, int32 DefenceLastTurn, int32 TreesLastTurn, int32 HuntLastTurn, int32 CookLastTurn, int32 HousesLastTurn)
{
	UnassignedPeople = AvailablePeople;
	DealWithAvailablePeople(UnassignedPeople > 0);
	const FText People = FText::FromString(FString::FromInt(AvailablePeople));
	TbAvailablePeople->SetText(People);

	const FText Days = FText::FromString(FString::FromInt(CurrentDay) + "/" + FString::FromInt(TotalDays));
	TbDay->SetText((Days));

	const FText Defence = FText::FromString(FString::SanitizeFloat(DefenceComplete) + "%");
	TbDefenceComplete->SetText(Defence);

	
}

void URTUV_PlayerWidget::OnDayEnd()
{
	
}

void URTUV_PlayerWidget::DealWithAvailablePeople(bool Available)
{
	// Enable or disable the buttons
	BtnDefenceIncrease->SetIsEnabled(Available);
	BtnHuntIncrease->SetIsEnabled(Available);
	BtnCookIncrease->SetIsEnabled(Available);
	BtnTreeIncrease->SetIsEnabled(Available);
	BtnHousingIncrease->SetIsEnabled(Available);
}

void URTUV_PlayerWidget::OnBtnTreeReduceClicked()
{
	UnassignedPeople += 1;
	if (UnassignedPeople == 1)
	{
		DealWithAvailablePeople(true);
	}
	
	TreeAssigned -= 1;
	if (TreeAssigned == 0)
	{
		BtnTreeReduce->SetIsEnabled(false);
	}
}

void URTUV_PlayerWidget::OnBtnTreeIncreaseClicked()
{
	UnassignedPeople -= 1;
	if (UnassignedPeople == 0)
	{
		DealWithAvailablePeople(false);
	}
	
	TreeAssigned += 1;
	if (!BtnTreeReduce->GetIsEnabled())
	{
		BtnTreeReduce->SetIsEnabled(true);
	}
}

void URTUV_PlayerWidget::OnBtnHuntReduceClicked()
{
	UnassignedPeople += 1;
	if (UnassignedPeople == 1)
	{
		DealWithAvailablePeople(true);
	}
	
	HuntAssigned -= 1;
	if (HuntAssigned == 0)
	{
		BtnHuntReduce->SetIsEnabled(false);
	}
}

void URTUV_PlayerWidget::OnBtnHuntIncreaseClicked()
{
	UnassignedPeople -= 1;
	if (UnassignedPeople == 0)
	{
		DealWithAvailablePeople(false);
	}
	
	HuntAssigned += 1;
	if (!BtnHuntReduce->GetIsEnabled())
	{
		BtnHuntReduce->SetIsEnabled(true);
	}
}

void URTUV_PlayerWidget::OnBtnCookReduceClicked()
{
	UnassignedPeople += 1;
	if (UnassignedPeople == 1)
	{
		DealWithAvailablePeople(true);
	}
	
	CookAssigned -= 1;
	if (CookAssigned == 0)
	{
		BtnCookReduce->SetIsEnabled(false);
	}
}

void URTUV_PlayerWidget::OnBtnCookIncreaseClicked()
{
	UnassignedPeople -= 1;
	if (UnassignedPeople == 0)
	{
		DealWithAvailablePeople(false);
	}
	
	CookAssigned += 1;
	if (!BtnCookReduce->GetIsEnabled())
	{
		BtnCookReduce->SetIsEnabled(true);
	}
}

void URTUV_PlayerWidget::OnBtnDefenceReduceClicked()
{
	UnassignedPeople += 1;
	if (UnassignedPeople == 1)
	{
		DealWithAvailablePeople(true);
	}
	
	DefenceAssigned -= 1;
	if (DefenceAssigned == 0)
	{
		BtnDefenceReduce->SetIsEnabled(false);
	}
}

void URTUV_PlayerWidget::OnBtnDefenceIncreaseClicked()
{
	UnassignedPeople -= 1;
	if (UnassignedPeople == 0)
	{
		DealWithAvailablePeople(false);
	}
	
	TreeAssigned += 1;
	if (!BtnTreeReduce->GetIsEnabled())
	{
		BtnTreeReduce->SetIsEnabled(true);
	}
}

void URTUV_PlayerWidget::OnBtnHousingReduceClicked()
{
	UnassignedPeople += 1;
	if (UnassignedPeople == 1)
	{
		DealWithAvailablePeople(true);
	}
	
	HousingAssigned -= 1;
	if (HousingAssigned == 0)
	{
		BtnHousingReduce->SetIsEnabled(false);
	}
}

void URTUV_PlayerWidget::OnBtnHousingIncreaseClicked()
{
	UnassignedPeople -= 1;
	if (UnassignedPeople == 0)
	{
		DealWithAvailablePeople(false);
	}
	
	HousingAssigned += 1;
	if (!BtnHousingReduce->GetIsEnabled())
	{
		BtnHousingReduce->SetIsEnabled(true);
	}
}

void URTUV_PlayerWidget::OnBtnBeginDayClicked()
{
	if (UnassignedPeople > 0)
	{
		// Show a box that not all people have been assigned	
	}
	else if (GameStateRef)
	{
		GameStateRef->OnStartDayClicked(TreeAssigned, DefenceAssigned, HuntAssigned, CookAssigned, HousingAssigned);
	}
}
