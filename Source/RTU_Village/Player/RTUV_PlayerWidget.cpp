// Copyright 2026 DME Games

#include "RTUV_PlayerWidget.h"
#include "../Framework/RTUV_GameState.h"
#include "Components/Button.h"
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

	BtnFoodReduce->OnClicked.AddDynamic(this, &URTUV_PlayerWidget::OnBtnFoodReduceClicked);
	BtnFoodIncrease->OnClicked.AddDynamic(this, &URTUV_PlayerWidget::OnBtnFoodIncreaseClicked);

	BtnHousingReduce->OnClicked.AddDynamic(this, &URTUV_PlayerWidget::OnBtnHousingReduceClicked);
	BtnHousingIncrease->OnClicked.AddDynamic(this, &URTUV_PlayerWidget::OnBtnHousingIncreaseClicked);
	
}

void URTUV_PlayerWidget::NewDayStart(int32 CurrentDay, int32 TotalDays, int32 AvailablePeople, float DefenceComplete, int32 TreesStored, int32 RawFoodStored, int32 CookedFoodStored, int32 HousesBuilt)
{
	
}

void URTUV_PlayerWidget::NoAvailablePeople()
{
	BtnDefenceIncrease->SetIsEnabled(false);
	BtnHuntIncrease->SetIsEnabled(false);
	BtnFoodIncrease->SetIsEnabled(false);
	BtnTreeIncrease->SetIsEnabled(false);
	BtnHousingIncrease->SetIsEnabled(false);
}

void URTUV_PlayerWidget::OnBtnTreeReduceClicked()
{
}

void URTUV_PlayerWidget::OnBtnTreeIncreaseClicked()
{
}

void URTUV_PlayerWidget::OnBtnHuntReduceClicked()
{
}

void URTUV_PlayerWidget::OnBtnHuntIncreaseClicked()
{
}

void URTUV_PlayerWidget::OnBtnFoodReduceClicked()
{
}

void URTUV_PlayerWidget::OnBtnFoodIncreaseClicked()
{
}

void URTUV_PlayerWidget::OnBtnDefenceReduceClicked()
{
}

void URTUV_PlayerWidget::OnBtnDefenceIncreaseClicked()
{
}

void URTUV_PlayerWidget::OnBtnHousingReduceClicked()
{
}

void URTUV_PlayerWidget::OnBtnHousingIncreaseClicked()
{
}
