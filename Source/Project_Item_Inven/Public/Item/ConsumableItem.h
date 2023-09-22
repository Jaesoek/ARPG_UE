// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item/BaseItem.h"
#include "ConsumableItem.generated.h"

/**
 * 
 */
UCLASS(Abstract)
class PROJECT_ITEM_INVEN_API AConsumableItem : public ABaseItem
{
	GENERATED_BODY()

public:
	AConsumableItem();

public:
	virtual bool UseItem(ACharacter* character) override;
};
