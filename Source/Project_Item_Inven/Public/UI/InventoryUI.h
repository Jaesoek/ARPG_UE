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
	// Widgets
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UBorder* Inventory;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UUniformGridPanel* GridPanel;

private:
	UPROPERTY(EditAnywhere, Category = CustomUISlot)
	TSubclassOf<UInventorySlot> m_InventorySlot_Class;

private:
	AInGamePlayerState* m_playerState;

	UPROPERTY(BlueprintReadWrite, Category = Inventory, Meta = (AllowPrivateAccess = true))
	TArray<UInventorySlot*> m_arrSlotInventory;

	UPROPERTY(BlueprintReadOnly, Category = Inventory, Meta = (AllowPrivateAccess = true))
	int m_nInventorySize;

public:
	virtual void NativeOnInitialized() override;

private:
	UFUNCTION()
	void RefreshInventoryUI();

	UFUNCTION()
	void AddItemInUI();
};
