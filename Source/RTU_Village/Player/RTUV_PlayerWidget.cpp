// Copyright 2026 DME Games

#include "RTUV_PlayerWidget.h"
#include "../Framework/RTUV_GameState.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Components/WidgetSwitcher.h"
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

	BtnDayReview->OnClicked.AddDynamic(this, &URTUV_PlayerWidget::OnBtnDayReviewClicked);

	BtnNotAssignedNo->OnClicked.AddDynamic(this, &URTUV_PlayerWidget::OnBtnNotAssignedNoClicked);
	BtnNotAssignedYes->OnClicked.AddDynamic(this, &URTUV_PlayerWidget::OnBtnNotAssignedYesClicked);
}

void URTUV_PlayerWidget::NewDayStart(int32 CurrentDay, int32 TotalDays, int32 TotalPeople, int32 AvailablePeople, float DefenceComplete, float TreesStored, int32 RawFoodStored, int32 CookedFoodStored,
	int32 HousesAvailable, int32 DefenceLastTurn, int32 TreesLastTurn, int32 HuntLastTurn, int32 CookLastTurn, int32 HousesLastTurn)
{
	UnassignedPeople = AvailablePeople;
	DealWithAvailablePeople(UnassignedPeople > 0);

	// Update values in the text boxes with values that don't need a button
	UpdateAssigned(AvailablePeople, *TbAvailablePeople);
	UpdateAssigned(TotalPeople, *TbTotalPeople);
	UpdateAssigned(TreesStored, *TbTreeStore);
	UpdateAssigned(RawFoodStored, *TbRawFoodStore);
	UpdateAssigned(CookedFoodStored, *TbCookedFoodStore);
	UpdateAssigned(HousesAvailable, *TbHousingAvailable);
	
	const FText Days = FText::FromString(FString::FromInt(CurrentDay) + "/" + FString::FromInt(TotalDays));
	TbDay->SetText((Days));

	const FText Defence = FText::FromString(FString::SanitizeFloat(DefenceComplete) + "%");
	TbDefenceComplete->SetText(Defence);

	// Update  values in the text boxes that can be changed by a button 
	UpdateAssignedButton(DefenceLastTurn, *TbDefenceAssigned, *BtnDefenceReduce);
	UpdateAssignedButton(TreesLastTurn, *TbTreeAssigned, *BtnTreeReduce);
	UpdateAssignedButton(HuntLastTurn, *TbHuntAssigned, *BtnHuntReduce);
	UpdateAssignedButton(CookLastTurn, *TbCookAssigned, *BtnCookReduce);
	UpdateAssignedButton(HousesLastTurn, *TbHousingAssigned, *BtnHousingReduce);
}

void URTUV_PlayerWidget::OnDayEnd(const FText& TextIn)
{
	// Set the widget to the day review and display the text
	WSPlayerWidget->SetActiveWidgetIndex(1);

	TbDayReview->SetText(TextIn);
}

void URTUV_PlayerWidget::UpdateAssigned(int32 AssignedValue, UTextBlock& TextBlock)
{
	UE_LOG(LogTemp, Warning, TEXT("TextBox: %s, Assigned: %i"), *TextBlock.GetName(), AssignedValue);
	const FText IntAsText = FText::FromString(FString::FromInt(AssignedValue));
	TextBlock.SetText(IntAsText);
}

void URTUV_PlayerWidget::UpdateAssignedButton(int32 AssignedValue,UTextBlock& TextBlock, UButton& Button)
{
	const FText IntAsText = FText::FromString(FString::FromInt(AssignedValue));
	TextBlock.SetText(IntAsText);
	if (AssignedValue == 0)
	{
		Button.SetIsEnabled(false);
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
		WSPlayerWidget->SetActiveWidgetIndex(2);	
	}
	else if (GameStateRef)
	{
		GameStateRef->OnStartDayClicked(TreeAssigned, DefenceAssigned, HuntAssigned, CookAssigned, HousingAssigned);
	}
}

void URTUV_PlayerWidget::OnBtnNotAssignedYesClicked()
{
	if (GameStateRef)
	{
		GameStateRef->OnStartDayClicked(TreeAssigned, DefenceAssigned, HuntAssigned, CookAssigned, HousingAssigned);
	}
}

void URTUV_PlayerWidget::OnBtnNotAssignedNoClicked()
{
	WSPlayerWidget->SetActiveWidgetIndex(0);
}

void URTUV_PlayerWidget::OnBtnDayReviewClicked()
{
	WSPlayerWidget->SetActiveWidgetIndex(0);
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

void URTUV_PlayerWidget::StartDay()
{
	
}
