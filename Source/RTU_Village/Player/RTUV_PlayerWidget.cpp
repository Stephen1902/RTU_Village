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

void URTUV_PlayerWidget::NewDayStart(int32 CurrentDay, int32 TotalDays, int32 TotalPeople, int32 AvailablePeople, float DefenceComplete, int32 TreesStored, int32 RawFoodStored, int32 CookedFoodStored,
	int32 HousesAvailable, int32 DefenceLastTurn, int32 TreesLastTurn, int32 HuntLastTurn, int32 CookLastTurn, int32 HousesLastTurn)
{
	UnassignedPeople = AvailablePeople;
	DealWithAvailablePeople(UnassignedPeople > 0);
	
	const FText PeopleAvailable = FText::FromString(FString::FromInt(AvailablePeople));
	TbAvailablePeople->SetText(PeopleAvailable);

	const FText PeopleTotal = FText::FromString(FString::FromInt(TotalPeople));
	TbTotalPeople->SetText(PeopleTotal);
	
	const FText Days = FText::FromString(FString::FromInt(CurrentDay) + "/" + FString::FromInt(TotalDays));
	TbDay->SetText((Days));

	const FText Defence = FText::FromString(FString::SanitizeFloat(DefenceComplete) + "%");
	TbDefenceComplete->SetText(Defence);

	const FText Trees = FText::FromString(FString::FromInt(TreesStored));
	TbTreeStore->SetText(Trees);

	const FText RawFood = FText::FromString(FString::FromInt(RawFoodStored));
	TbRawFoodStore->SetText(RawFood);
	
	const FText CookedFood = FText::FromString(FString::FromInt(CookedFoodStored));
	TbCookedFoodStore->SetText(CookedFood);

	const FText Houses = FText::FromString(FString::FromInt(HousesAvailable));
	TbHousingAvailable->SetText(Houses);

	const FText DefenceLT = FText::FromString(FString::FromInt(DefenceLastTurn));
	TbDefenceAssigned->SetText(DefenceLT);
	if (DefenceLastTurn == 0)
	{
		BtnDefenceReduce->SetIsEnabled(false);
	}

	const FText TreesLT = FText::FromString(FString::FromInt(TreesLastTurn));
	TbTreeAssigned->SetText(TreesLT);
	if (TreesLastTurn == 0)
	{
		BtnTreeReduce->SetIsEnabled(false);
	}

	const FText HuntLT = FText::FromString(FString::FromInt(HuntLastTurn));
	TbHuntAssigned->SetText(HuntLT);
	if (HuntLastTurn == 0)
	{
		BtnHuntReduce->SetIsEnabled(false);
	}

	const FText CookLT = FText::FromString(FString::FromInt(CookLastTurn));
	TbCookAssigned->SetText(CookLT);
	if (CookLastTurn == 0)
	{
		BtnCookReduce->SetIsEnabled(false);
	}

	const FText HousesLT = FText::FromString(FString::FromInt(HousesLastTurn));
	TbHousingAssigned->SetText(HousesLT);
	if (HousesLastTurn == 0)
	{
		BtnHousingReduce->SetIsEnabled(false);
	}
}


void URTUV_PlayerWidget::OnBtnTreeReduceClicked()
{
	AdjustValue(false, TreeAssigned, *TbTreeAssigned, *BtnTreeReduce);
}

void URTUV_PlayerWidget::OnBtnTreeIncreaseClicked()
{
	AdjustValue(true, TreeAssigned, *TbTreeAssigned, *BtnTreeReduce);
}

void URTUV_PlayerWidget::OnBtnHuntReduceClicked()
{
	AdjustValue(false, HuntAssigned, *TbHuntAssigned, *BtnHuntReduce);
}

void URTUV_PlayerWidget::OnBtnHuntIncreaseClicked()
{
	AdjustValue(true, HuntAssigned, *TbHuntAssigned, *BtnHuntReduce);
}

void URTUV_PlayerWidget::OnBtnCookReduceClicked()
{
	AdjustValue(false, CookAssigned, *TbCookAssigned, *BtnCookReduce);
}

void URTUV_PlayerWidget::OnBtnCookIncreaseClicked()
{
	AdjustValue(true, CookAssigned, *TbCookAssigned, *BtnCookReduce);
}

void URTUV_PlayerWidget::OnBtnDefenceReduceClicked()
{
	AdjustValue(false, DefenceAssigned, *TbDefenceAssigned, *BtnDefenceReduce);
}

void URTUV_PlayerWidget::OnBtnDefenceIncreaseClicked()
{
	AdjustValue(true, DefenceAssigned, *TbDefenceAssigned, *BtnDefenceReduce);
}

void URTUV_PlayerWidget::OnBtnHousingReduceClicked()
{
	AdjustValue(false, HousingAssigned, *TbHousingAssigned, *BtnHousingReduce);
}

void URTUV_PlayerWidget::OnBtnHousingIncreaseClicked()
{
	AdjustValue(true, HousingAssigned, *TbHousingAssigned, *BtnHousingReduce);
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

void URTUV_PlayerWidget::AdjustValue(bool Increase, int32& Value, UTextBlock& TextBlock, UButton& Button)
{
	if (Increase)
	{
		UnassignedPeople -= 1;
		if (UnassignedPeople == 0)	DealWithAvailablePeople(false);

		Value += 1;
		if (Value == 1)	Button.SetIsEnabled(true);
	}
	else
	{
		UnassignedPeople += 1;
		if (UnassignedPeople == 1) DealWithAvailablePeople(true);

		Value -= 1;
		if (Value == 0) Button.SetIsEnabled(false);
	}

	const FText Unassigned = FText::FromString(FString::FromInt(UnassignedPeople));
	TbAvailablePeople->SetText(Unassigned);

	const FText Assigned = FText::FromString(FString::FromInt(Value));
	TextBlock.SetText(Assigned);
}