// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/InventoryUI.h"
#include "InGamePlayerState.h"
#include "UI/InventorySlot.h"

#include "Blueprint/UserWidget.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "Blueprint/WidgetTree.h"


void UInventoryUI::NativeConstruct()
{
	// PlayerState �ʱ�ȭ
	m_playerState = GetOwningPlayer()->GetPlayerState<AInGamePlayerState>();

	// Observing Inventory's add item
	m_playerState->OnAddItem.AddDynamic(this, &UInventoryUI::RefreshInventoryUI);

	// UI Inventory size �ʱ�ȭ
	m_nInventorySize = m_playerState->getInventory()->Max();
	m_arrSlotInventory.Init(nullptr, m_nInventorySize);

	// BP���� �̸� �׷����� Slot�� m_arrSlotInventory�� ����
	{
		TArray<UWidget*> arrAllWidget;
		WidgetTree->GetAllWidgets(arrAllWidget);

		int nPosInventorySlot{};
		for (auto widget : arrAllWidget)
		{
			if (widget->GetClass()->IsChildOf(UInventorySlot::StaticClass()))
			{
				if (nPosInventorySlot < m_nInventorySize)
				{
					m_arrSlotInventory[nPosInventorySlot] = Cast<UInventorySlot>(widget);
					m_arrSlotInventory[nPosInventorySlot]->setSlotIndex(nPosInventorySlot);

					widget->SetVisibility(ESlateVisibility::Visible);
				}
				else
				{
					widget->SetVisibility(ESlateVisibility::Hidden);
				}

				nPosInventorySlot++;
			}
		}
	}


	Super::NativeConstruct();
}

void UInventoryUI::RefreshInventoryUI()
{
	auto arrInventory = m_playerState->getInventory()->GetData();

	// TODO: ���� Event Driven ������� ���� �ʿ�(����� Property Bind)
	for (int i = 0; i < m_nInventorySize; ++i)
	{
		m_arrSlotInventory[i]->setTexture(arrInventory[i].texture);
		m_arrSlotInventory[i]->setItemCount(arrInventory[i].count);
	}
}

void UInventoryUI::AddItemInUI()
{

}

