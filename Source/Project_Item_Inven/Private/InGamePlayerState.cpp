// Fill out your copyright notice in the Description page of Project Settings.


#include "InGamePlayerState.h"
#include "Item/BaseItem.h"

void AInGamePlayerState::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	// Inventory container √ ±‚»≠
	m_arrInventory.Init(FInventoryStruct{}, m_nMaxInventorySize);
}

bool AInGamePlayerState::addItem(UClass* itemClass, FText name, FText description, UTexture2D* thumbnail)
{
	auto ptrItem = Cast<ABaseItem>(itemClass->GetDefaultObject());
	if (ptrItem == nullptr) return false;

	switch (ptrItem->GetItemType())
	{
		case EItemType::Consumable:
		{
			bool isSuccess = addConsumableItem(itemClass, name, description, thumbnail);
			if (isSuccess) OnAddItem.Broadcast();
			return isSuccess;
		}
		case EItemType::Equipable:
		{
			bool isSuccess = addEquipableItem(itemClass, name, description, thumbnail);
			if (isSuccess) OnAddItem.Broadcast();
			return isSuccess;
		}
	}
	
	return false;
}

bool AInGamePlayerState::addConsumableItem(UClass* itemClass, FText name, FText description, UTexture2D* thumbnail)
{
	int nPosNull = -1;
	for (int i = 0; i < m_nMaxInventorySize; ++i)
	{
		if (m_arrInventory[i].itemClass == itemClass)
		{
			m_arrInventory[i].count += 1;
			return true;
		}
		else if (nPosNull == -1 && m_arrInventory[i].itemClass == nullptr)
		{
			nPosNull = i;
		}
	}

	if (nPosNull != -1)
	{
		FInventoryStruct& tempInv = m_arrInventory[nPosNull];
		tempInv.itemClass = itemClass;
		tempInv.description = description;
		tempInv.name = name;
		tempInv.texture = thumbnail;
		tempInv.count += 1;

		return true;
	}

	return false;
}

bool AInGamePlayerState::addEquipableItem(UClass* itemClass, FText name, FText description, UTexture2D* thumbnail)
{
	for (int i = 0; i < m_nMaxInventorySize; ++i)
	{
		if (m_arrInventory[i].itemClass == nullptr)
		{
			FInventoryStruct& tempInv = m_arrInventory[i];
			tempInv.itemClass = itemClass;
			tempInv.description = description;
			tempInv.name = name;
			tempInv.texture = thumbnail;
			tempInv.count += 1;

			return true;
		}
	}

	return false;
}

bool AInGamePlayerState::swapItem(int nFirstIndex, int nSecondIndex)
{
	if (nFirstIndex > m_nMaxInventorySize || nSecondIndex > m_nMaxInventorySize)
		return false;

	m_arrInventory.SwapMemory(nFirstIndex, nSecondIndex);
	OnAddItem.Broadcast();
	return true;
}

bool AInGamePlayerState::removeItemAt(int pos)
{
	if (pos < m_nMaxInventorySize)
	{
		m_arrInventory[pos] = FInventoryStruct {};
		OnAddItem.Broadcast();
		return true;
	}

	return false;
}
