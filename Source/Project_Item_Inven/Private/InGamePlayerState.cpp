// Fill out your copyright notice in the Description page of Project Settings.


#include "InGamePlayerState.h"
#include "Item/EquipItem.h"
#include "Item/ConsumableItem.h"

#include "Player/TpsCharacter.h"

#include "Kismet/GameplayStatics.h"


void AInGamePlayerState::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	// Init inventory, equipment container
	m_arrInventory.Init(FInventoryStruct{}, m_nMaxInventorySize);

	m_mapEquipment.Add(EEquipType::Weapon, nullptr);
	m_mapEquipment.Add(EEquipType::Helmet, nullptr);
	m_mapEquipment.Add(EEquipType::Breast, nullptr);
}

bool AInGamePlayerState::addItem(TSubclassOf<ABaseItem> itemClass)
{
	if (!IsValid(itemClass)) return false;

	auto ptrItem = Cast<ABaseItem>(itemClass->GetDefaultObject());
	if (ptrItem == nullptr) return false;

	switch (ptrItem->GetItemType())
	{
		case EItemType::Consumable:
		{
			bool isSuccess = addConsumableItem(itemClass);
			if (isSuccess) OnInventoryEdited.Broadcast();
			return isSuccess;
		}
		case EItemType::Equipable:
		{
			bool isSuccess = addEquipableItem(itemClass);
			if (isSuccess) OnInventoryEdited.Broadcast();
			return isSuccess;
		}
	}

	return false;
}

bool AInGamePlayerState::addConsumableItem(TSubclassOf<ABaseItem> itemClass)
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
		tempInv.count += 1;

		return true;
	}

	return false;
}

bool AInGamePlayerState::addEquipableItem(TSubclassOf<ABaseItem> itemClass)
{
	for (int i = 0; i < m_nMaxInventorySize; ++i)
	{
		if (m_arrInventory[i].itemClass == nullptr)
		{
			FInventoryStruct& tempInv = m_arrInventory[i];
			tempInv.itemClass = itemClass;
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
	OnInventoryEdited.Broadcast();
	return true;
}

bool AInGamePlayerState::clearSlot(int inventoryIndex)
{
	if (inventoryIndex < m_nMaxInventorySize)
	{
		m_arrInventory[inventoryIndex] = FInventoryStruct{};
		OnInventoryEdited.Broadcast();
		return true;
	}

	return false;
}

bool AInGamePlayerState::removeItemAt(int inventoryIndex)
{
	if (inventoryIndex < m_nMaxInventorySize)
	{
		if (m_arrInventory[inventoryIndex].count == 1)
		{
			return clearSlot(inventoryIndex);
		}
		else
		{
			m_arrInventory[inventoryIndex].count -= 1;
			OnInventoryEdited.Broadcast();
			return true;
		}
	}

	return false;
}

void AInGamePlayerState::MoveToEquip(int inventoryIndex, const AEquipItem& equipItemObj)
{
	m_mapEquipment.Emplace(equipItemObj.GetEquipType(), equipItemObj.GetClass());
	OnEquipEdited.Broadcast();

	clearSlot(inventoryIndex);
}

void AInGamePlayerState::SwapEquip(int inventoryIndex, EEquipType equipType)
{
	auto tempItemClass = m_mapEquipment[equipType];
	m_mapEquipment[equipType] = m_arrInventory[inventoryIndex].itemClass;
	m_arrInventory[inventoryIndex].itemClass = tempItemClass;

	OnEquipEdited.Broadcast();
	OnInventoryEdited.Broadcast();
}


bool AInGamePlayerState::useItem(int inventoryIndex)
{
	auto inventoryItemClass = m_arrInventory[inventoryIndex].itemClass;
	if (!IsValid(inventoryItemClass)) return false;

	auto character = Cast<ACharacter>(GetWorld()->GetFirstPlayerController()->GetPawn());
	auto ptrItem = Cast<ABaseItem>(inventoryItemClass->GetDefaultObject());
	switch (ptrItem->GetItemType())
	{
		case EItemType::Consumable:
		{
			bool isSuccess = ptrItem->UseItem(character);
			if (isSuccess)
				return removeItemAt(inventoryIndex);
		}
		case EItemType::Equipable:
		{
			bool isSuccess = ptrItem->UseItem(character);
			if (!isSuccess) return false;

			auto itemEquip= Cast<AEquipItem>(ptrItem);
			auto equipType = itemEquip->GetEquipType();
			if (m_mapEquipment[equipType] == nullptr)
				MoveToEquip(inventoryIndex, *itemEquip);
			else
				SwapEquip(inventoryIndex, equipType);
		}
	}

	return false;
}

bool AInGamePlayerState::unEquip(EEquipType eEquipType)
{
	bool isSuccess = addItem(m_mapEquipment[eEquipType]);
	if (!isSuccess)
	{
		// TODO: 노티파이 출력
		return false;
	}

	auto character = Cast<ATpsCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn());
	character->UnEquip(eEquipType);

	m_mapEquipment[eEquipType] = nullptr;
	OnEquipEdited.Broadcast();

	return true;
}
