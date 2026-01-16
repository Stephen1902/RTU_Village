// Copyright 2026 DME Games

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "RTUV_PlayerWidget.generated.h"

class UTextBlock;
class UButton;

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
	UTextBlock* TbDay;
	
	UPROPERTY(BlueprintReadOnly, Category = "Player Widget", meta=(BindWidget))
	UTextBlock* TbAvailablePeople;

	UPROPERTY(BlueprintReadOnly, Category = "Player Widget", meta=(BindWidget))
	UTextBlock* TbDefenceComplete;

	UPROPERTY(BlueprintReadOnly, Category = "Player Widget", meta=(BindWidget))
	UTextBlock* TbTreeStore;

	UPROPERTY(BlueprintReadOnly, Category = "Player Widget", meta=(BindWidget))
	UTextBlock* TbFoodStore;

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

public:
	void NewDayStart(int32 CurrentDay, int32 TotalDays, int32 AvailablePeople, float DefenceComplete, int32 TreesStored, int32 RawFoodStored, int32 CookedFoodStored, int32 HousesBuilt);
	void OnDayEnd();
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
};
