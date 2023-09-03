// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/InventoryUI.h"
#include "InGamePlayerState.h"
#include "UI/InventorySlot.h"

#include "Components/UniformGridPanel.h"
#include "Components/UniformGridSlot.h"

#include "Blueprint/UserWidget.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "Blueprint/WidgetTree.h"

void UInventoryUI::NativeOnInitialized()
{
	// PlayerState 초기화
	m_playerState = GetOwningPlayer()->GetPlayerState<AInGamePlayerState>();

	// Observing Inventory's add item
	m_playerState->OnAddItem.AddDynamic(this, &UInventoryUI::RefreshInventoryUI);

	// UI Inventory size 초기화
	m_nInventorySize = m_playerState->getInventory()->Max();
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
	auto arrInventory = m_playerState->getInventory()->GetData();

	for (int i = 0; i < m_nInventorySize; ++i)
	{
		m_arrSlotInventory[i]->setTexture(arrInventory[i].texture);
		m_arrSlotInventory[i]->setItemCount(arrInventory[i].count);
	}
}

void UInventoryUI::AddItemInUI()
{

}

