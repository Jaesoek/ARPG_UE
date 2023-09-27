// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Project_Item_Inven.h"
#include "Blueprint/UserWidget.h"
#include "InventoryUI.generated.h"

class AInGamePlayerState;
class UInventorySlot;
class UEquipmentSlot;

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

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UEquipmentSlot* WeaponEquipSlot;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UEquipmentSlot* HelmetEquipSlot;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UEquipmentSlot* BreastEquipSlot;

private:
	UPROPERTY(EditAnywhere, Category = CustomUISlot)
	TSubclassOf<UInventorySlot> m_InventorySlot_Class;

private:
	UPROPERTY(BlueprintReadWrite, Category = Inventory, Meta = (AllowPrivateAccess = true))
	TArray<UInventorySlot*> m_arrSlotInventory;

	UPROPERTY(BlueprintReadOnly, Category = Inventory, Meta = (AllowPrivateAccess = true))
	int m_nInventorySize;

	UPROPERTY(BlueprintReadWrite, Category = Equip, Meta = (AllowPrivateAccess = true))
	TMap<EEquipType, UEquipmentSlot*> m_mapSlotEquip;

private:
	AInGamePlayerState* m_playerState;


public:
	virtual void NativeOnInitialized() override;

private:
	UFUNCTION()
	void RefreshInventoryUI();

	UFUNCTION()
	void RefreshEquipmentUI();


	UFUNCTION()
	void AddItemInUI();
};
