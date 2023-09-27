// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/InventoryUI.h"
#include "UI/InventorySlot.h"
#include "UI/EquipmentSlot.h"

#include "InGamePlayerState.h"

#include "Item/EquipItem.h"

#include "Components/UniformGridPanel.h"
#include "Components/UniformGridSlot.h"

#include "Blueprint/UserWidget.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "Blueprint/WidgetTree.h"

void UInventoryUI::NativeOnInitialized()
{
	// PlayerState 초기화
	m_playerState = GetOwningPlayer()->GetPlayerState<AInGamePlayerState>();

	// Observing edited inventory, equipment container
	m_playerState->OnInventoryEdited.AddDynamic(this, &UInventoryUI::RefreshInventoryUI);
	m_playerState->OnEquipEdited.AddDynamic(this, &UInventoryUI::RefreshEquipmentUI);

	// UI Equipment slot 설정
	m_mapSlotEquip.Add(EEquipType::Weapon, WeaponEquipSlot);
	WeaponEquipSlot->setEquipType(EEquipType::Weapon);
	m_mapSlotEquip.Add(EEquipType::Helmet, HelmetEquipSlot);
	WeaponEquipSlot->setEquipType(EEquipType::Helmet);
	m_mapSlotEquip.Add(EEquipType::Breast, BreastEquipSlot);
	WeaponEquipSlot->setEquipType(EEquipType::Breast);

	// UI Inventory size 초기화 및 Slot UI 할당
	m_nInventorySize = m_playerState->getInventory().Max();
	m_arrSlotInventory.Init(nullptr, m_nInventorySize);

	for (int i = 0; i < 60; i++)
	{
		auto InvenSlot = CreateWidget(this, m_InventorySlot_Class);
		auto gridSlot = GridPanel->AddChildToUniformGrid(InvenSlot, i / 6, i % 6);
		gridSlot->SetVerticalAlignment(EVerticalAlignment::VAlign_Fill);
		gridSlot->SetHorizontalAlignment(EHorizontalAlignment::HAlign_Fill);

		if (i < m_nInventorySize)
		{
			m_arrSlotInventory[i] = Cast<UInventorySlot>(InvenSlot);
			m_arrSlotInventory[i]->setSlotIndex(i);

			InvenSlot->SetVisibility(ESlateVisibility::Visible);
		}
		else
		{
			InvenSlot->SetVisibility(ESlateVisibility::Hidden);
		}
	}
}

void UInventoryUI::RefreshInventoryUI()
{
	auto arrInventory = m_playerState->getInventory().GetData();

	for (int i = 0; i < m_nInventorySize; ++i)
	{
		if (arrInventory[i].itemClass != nullptr)
		{
			auto ptrItem = Cast<ABaseItem>(arrInventory[i].itemClass->GetDefaultObject());
			m_arrSlotInventory[i]->setTexture(ptrItem->GetItemThumbnail());
			m_arrSlotInventory[i]->setItemType(ptrItem->GetItemType());
		}
		else
		{
			m_arrSlotInventory[i]->setTexture(nullptr);
			m_arrSlotInventory[i]->setItemType(EItemType::None);
		}

		m_arrSlotInventory[i]->setItemCount(arrInventory[i].count);
	}
}

void UInventoryUI::RefreshEquipmentUI()
{
	auto mapEquipment = m_playerState->getEquipment();

	TSet<EEquipType> setKeys{};
	mapEquipment.GetKeys(setKeys);
	for (auto key : setKeys)
	{
		if (!IsValid(mapEquipment[key]))
		{
			m_mapSlotEquip[key]->setTexture(nullptr);
		}
		else
		{
			auto ptrItem = Cast<AEquipItem>(mapEquipment[key]->GetDefaultObject());
			m_mapSlotEquip[key]->setTexture(ptrItem->GetItemThumbnail());
		}
		m_mapSlotEquip[key]->setEquipType(key);
	}

}

void UInventoryUI::AddItemInUI()
{
	// Queue에 저장하고 돌린다든가 하는것들을 추가합시다
}

