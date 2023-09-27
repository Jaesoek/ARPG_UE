// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Project_Item_Inven.h"
#include "Blueprint/UserWidget.h"
#include "InventorySlot.generated.h"

/**
 * 
 */
UCLASS(Abstract)
class PROJECT_ITEM_INVEN_API UInventorySlot : public UUserWidget
{
	GENERATED_BODY()

private:
	UPROPERTY(BlueprintReadOnly, Category = Inventory, Meta = (AllowPrivateAccess = true))
	int m_nSlotIndex;

	UPROPERTY(BlueprintReadOnly, Category = Inventory, Meta = (AllowPrivateAccess = true))
	int m_nItemCount;

	UPROPERTY(BlueprintReadOnly, Category = Inventory, Meta = (AllowPrivateAccess = true))
	EItemType m_eItemType;

	UPROPERTY(BlueprintReadOnly, Category = Inventory, Meta = (AllowPrivateAccess = true))
	UTexture2D* m_ptrTexture;

public:
	FORCEINLINE void setSlotIndex(int slotIndex) { m_nSlotIndex = slotIndex; };
	FORCEINLINE int getSlotIndex() const { return m_nSlotIndex; };

	FORCEINLINE void setItemCount(int itemCount) { m_nItemCount = itemCount; };
	FORCEINLINE int getItemCount() const { return m_nItemCount; };

	FORCEINLINE void setItemType(EItemType itemType) { m_eItemType = itemType; };
	FORCEINLINE EItemType getItemType() const { return m_eItemType; };

	FORCEINLINE void setTexture(UTexture2D* texture) { m_ptrTexture = texture; };
	FORCEINLINE const UTexture2D* getTexture() const { return m_ptrTexture; };
};
