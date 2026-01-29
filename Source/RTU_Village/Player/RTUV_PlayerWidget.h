// Copyright 2026 DME Games

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "RTUV_PlayerWidget.generated.h"

class UTextBlock;
class UButton;
class UWidgetSwitcher;

/**
 * 
 */
UCLASS()
class RTU_VILLAGE_API URTUV_PlayerWidget : public UUserWidget
{
	GENERATED_BODY()

	virtual void NativeConstruct() override;
protected:
	UPROPERTY(BlueprintReadOnly, Category = "Player Widget", meta=(BindWidget))
	UWidgetSwitcher* WSPlayerWidget;
	
	UPROPERTY(BlueprintReadOnly, Category = "Player Widget", meta=(BindWidget))
	UTextBlock* TbDay;

	UPROPERTY(BlueprintReadOnly, Category = "Player Widget", meta=(BindWidget))
	UTextBlock* TbTotalPeople;
	
	UPROPERTY(BlueprintReadOnly, Category = "Player Widget", meta=(BindWidget))
	UTextBlock* TbAvailablePeople;

	UPROPERTY(BlueprintReadOnly, Category = "Player Widget", meta=(BindWidget))
	UTextBlock* TbDefenceComplete;

	UPROPERTY(BlueprintReadOnly, Category = "Player Widget", meta=(BindWidget))
	UTextBlock* TbTreeStore;

	UPROPERTY(BlueprintReadOnly, Category = "Player Widget", meta=(BindWidget))
	UTextBlock* TbRawFoodStore;

	UPROPERTY(BlueprintReadOnly, Category = "Player Widget", meta=(BindWidget))
	UTextBlock* TbCookedFoodStore;

	UPROPERTY(BlueprintReadOnly, Category = "Player Widget", meta=(BindWidget))
	UTextBlock* TbHousingAvailable;
	
	UPROPERTY(BlueprintReadOnly, Category = "Player Widget", meta=(BindWidget))
	UButton* BtnTreeReduce;

	UPROPERTY(BlueprintReadOnly, Category = "Player Widget", meta=(BindWidget))
	UTextBlock* TbTreeAssigned;

	UPROPERTY(BlueprintReadOnly, Category = "Player Widget", meta=(BindWidget))
	UButton* BtnTreeIncrease;

	UPROPERTY(BlueprintReadOnly, Category = "Player Widget", meta=(BindWidget))
	UButton* BtnHuntReduce;

	UPROPERTY(BlueprintReadOnly, Category = "Player Widget", meta=(BindWidget))
	UTextBlock* TbHuntAssigned;

	UPROPERTY(BlueprintReadOnly, Category = "Player Widget", meta=(BindWidget))
	UButton* BtnHuntIncrease;

	UPROPERTY(BlueprintReadOnly, Category = "Player Widget", meta=(BindWidget))
	UButton* BtnCookReduce;

	UPROPERTY(BlueprintReadOnly, Category = "Player Widget", meta=(BindWidget))
	UTextBlock* TbCookAssigned;

	UPROPERTY(BlueprintReadOnly, Category = "Player Widget", meta=(BindWidget))
	UButton* BtnCookIncrease;

	UPROPERTY(BlueprintReadOnly, Category = "Player Widget", meta=(BindWidget))
	UButton* BtnDefenceReduce;

	UPROPERTY(BlueprintReadOnly, Category = "Player Widget", meta=(BindWidget))
	UTextBlock* TbDefenceAssigned;

	UPROPERTY(BlueprintReadOnly, Category = "Player Widget", meta=(BindWidget))
	UButton* BtnDefenceIncrease;

	UPROPERTY(BlueprintReadOnly, Category = "Player Widget", meta=(BindWidget))
	UButton* BtnHousingReduce;

	UPROPERTY(BlueprintReadOnly, Category = "Player Widget", meta=(BindWidget))
	UTextBlock* TbHousingAssigned;

	UPROPERTY(BlueprintReadOnly, Category = "Player Widget", meta=(BindWidget))
	UButton* BtnHousingIncrease;

	UPROPERTY(BlueprintReadOnly, Category = "Player Widget", meta=(BindWidget))
	UButton* BtnBeginDay;

	UPROPERTY(BlueprintReadOnly, Category = "Player Widget", meta=(BindWidget))
	UButton* BtnNotAssignedYes;

	UPROPERTY(BlueprintReadOnly, Category = "Player Widget", meta=(BindWidget))
	UButton* BtnNotAssignedNo;

	UPROPERTY(BlueprintReadOnly, Category = "Player Widget", meta=(BindWidget))
	UTextBlock* TbDayReview;
	
	UPROPERTY(BlueprintReadOnly, Category = "Player Widget", meta=(BindWidget))
	UButton* BtnDayReview;

public:
	void NewDayStart(int32 CurrentDay, int32 TotalDays, int32 TotalPeople, int32 AvailablePeople, float DefenceComplete, int32 TreesStored, int32 RawFoodStored, int32 CookedFoodStored, int32 HousesAvailable, int32 DefenceLastTurn, int32 TreesLastTurn, int32 HuntLastTurn, int32 CookLastTurn, int32 HousesLastTurn);
	void OnDayEnd(const FText& TextIn);
private:
	UPROPERTY()
	class ARTUV_GameState* GameStateRef;

	int32 UnassignedPeople;
	int32 TreeAssigned;
	int32 DefenceAssigned;
	int32 HuntAssigned;
	int32 CookAssigned;
	int32 HousingAssigned;
	void DealWithAvailablePeople(bool Available);

	UFUNCTION()
	void OnBtnTreeReduceClicked();
	UFUNCTION()
	void OnBtnTreeIncreaseClicked();

	UFUNCTION()
	void OnBtnHuntReduceClicked();
	UFUNCTION()
	void OnBtnHuntIncreaseClicked();

	UFUNCTION()
	void OnBtnCookReduceClicked();
	UFUNCTION()
	void OnBtnCookIncreaseClicked();

	UFUNCTION()
	void OnBtnDefenceReduceClicked();
	UFUNCTION()
	void OnBtnDefenceIncreaseClicked();

	UFUNCTION()
	void OnBtnHousingReduceClicked();
	UFUNCTION()
	void OnBtnHousingIncreaseClicked();

	UFUNCTION()
	void OnBtnBeginDayClicked();

	UFUNCTION()
	void OnBtnNotAssignedYesClicked();
	UFUNCTION()
	void OnBtnNotAssignedNoClicked();

	UFUNCTION()
	void OnBtnDayReviewClicked();

	void AdjustValue(bool Increase, int32& Value, UTextBlock& TextBlock, UButton& Button);
	static void UpdateAssigned(int32 AssignedValue, UTextBlock& TextBlock);
	static void UpdateAssignedButton(int32 AssignedValue, UTextBlock& TextBlock, UButton& Button);

	void StartDay();
};
