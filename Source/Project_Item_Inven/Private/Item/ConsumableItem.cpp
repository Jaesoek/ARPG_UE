// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/ConsumableItem.h"
#include "GameFramework/Character.h"
#include "Component/CharacterStatComp.h"

AConsumableItem::AConsumableItem()
{
	PrimaryActorTick.bCanEverTick = true;

	m_eItemType = EItemType::Consumable;
}

bool AConsumableItem::UseItem(ACharacter* character)
{
	auto statComp = character->GetComponentByClass(UCharacterStatComp::StaticClass());

	return true;
}