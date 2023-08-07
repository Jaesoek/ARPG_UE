// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InventoryUI.generated.h"

class AInGamePlayerState;
class UInventorySlot;

/**
 * 
 */
UCLASS(Abstract)
class PROJECT_ITEM_INVEN_API UInventoryUI : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void NativeConstruct() override;

private:
	UPROPERTY(BlueprintReadWrite, Category = Inventory, Meta = (AllowPrivateAccess = true))
	TArray<UInventorySlot*> m_arrSlotInventory;

	UPROPERTY(BlueprintReadOnly, Category = Inventory, Meta = (AllowPrivateAccess = true))
	int m_nInventorySize;

private:
	AInGamePlayerState* m_playerState;

private:
	UFUNCTION()
	void RefreshInventoryUI();

	UFUNCTION()
	void AddItemInUI();
};
